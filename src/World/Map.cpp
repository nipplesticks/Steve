#include "Map.h"
#include "../renderer/d3d12/myRenderer.h"
#include "../renderer/textureLoader/TextureLoader.h"
#include "Star.h"
#include <unordered_map>

float Map::LOD_MAX_DISTANCE = 10.0f;

struct alignas(256) WaterUVoffset
{
  float waterUV = 0.0f;
};

Map::Map()
    : Transform()
{ }

void Map::SetRotationSpeed(float rotationSpeed) { }

void Map::Create(uint maxSubdivisions, float waterTiles, const DM::Vec2u& textureResulotion)
{
  maxSubdivisions += 1;
  myTextureSize = textureResulotion;
  myHeightMapGenInput.Create(sizeof(GPUGenerationInput));
  myDiffuseMapGenInput.Create(sizeof(GPUGenerationInput));
  myTotalDetailLevels = maxSubdivisions;
  myWorldMatrix.Create(sizeof(DefaultWorldMatrix));
  myLights.Create(sizeof(Light), MAX_LIGHTS);

  uint waterDetailLevel = myTotalDetailLevels / 2;

  Icosahedron icosahedron;
  {
    IcosahedronSideDuringCreation icosahedronSides[ICOSAHEDRON_SIDES];
    _CreateIcosahedronAndSubdivide(icosahedronSides, maxSubdivisions);
    _CreateVertices(icosahedron, icosahedronSides);
    _CreateWater(icosahedron, waterDetailLevel, waterTiles);
  }
  _SetupTextures(textureResulotion);
  _SetupDetailLevels(icosahedron, maxSubdivisions);
  _SetupGraphicPipelineState();
  _SetupComputePipelineState();
}

void Map::SetWaterLevel(float waterLevel)
{
  myWaterLevel = waterLevel;
}

void Map::Update(float dt, Camera* camera_p)
{
  /*Rotate(0, dt * myRotationSpeed, 0);
  myWaterDrawable.Rotate(0, dt * myRotationSpeed, 0);*/

  std::vector<Light> lightVector(Star::Active_Stars.size());

  for (uint i = 0; i < Star::Active_Stars.size(); i++)
  {
    lightVector[i] = Star::Active_Stars[i]->GetLight();
  }
  myLights.UpdateNow(lightVector.data(),
                     D3D12_RESOURCE_STATE_GENERIC_READ,
                     sizeof(Light) * (uint64)lightVector.size());

  _CalcDetailLevel(camera_p);
  myWaterOffset += dt * 0.01f;
  myWaterDrawable.SetScale(GetScale() + (GetScale() * myWaterLevel));
  myWaterDrawable.SetLights(lightVector);
  WaterUVoffset wo;
  wo.waterUV = myWaterOffset;

  myWaterDrawable.UpdateWorldMatrixConstantBuffer();
  DM::Mat4x4f        worldMat = GetWorldMatrix();
  DefaultWorldMatrix wm       = {};
  wm.worldMatrix              = worldMat.AsXmFloat4x4A();
  wm.worldMatrixInverse       = worldMat.Inverse().AsXmFloat4x4A();
  wm.numberOfLights           = (uint)Star::Active_Stars.size();
  myWorldMatrix.UpdateNow(&wm, D3D12_RESOURCE_STATE_GENERIC_READ);
  myWaterOffsetBuffer.UpdateNow(&wo, D3D12_RESOURCE_STATE_GENERIC_READ);
}

void Map::GenerateMap(const Noise& heightMap, const Noise& diffuseMap)
{
  GPUGenerationInput hm;
  GPUGenerationInput dm;
  {
    PerlinNoise      pn(heightMap.seed);
    std::vector<int> permutation = pn.GetPermutaion();
    hm.exponent                  = heightMap.expnoent;
    hm.frequency                 = heightMap.frequency;
    hm.fudgeFactor               = heightMap.fudgeFactor;
    hm.iterations                = heightMap.iterations;
    memcpy(&hm.permutationVector[0], permutation.data(), sizeof(int) * permutation.size());
    hm.textureSize = myTextureSize.AsXmAsXmFloat2A();
    hm.waterLevel  = myWaterLevel;
  }
  {
    PerlinNoise      pn(diffuseMap.seed);
    std::vector<int> permutation = pn.GetPermutaion();
    dm.exponent                  = diffuseMap.expnoent;
    dm.frequency                 = diffuseMap.frequency;
    dm.fudgeFactor               = diffuseMap.fudgeFactor;
    dm.iterations                = diffuseMap.iterations;
    memcpy(&dm.permutationVector[0], permutation.data(), sizeof(int) * permutation.size());
    dm.textureSize = myTextureSize.AsXmAsXmFloat2A();
    dm.waterLevel  = myWaterLevel;
  }
  myHeightMapGenInput.UpdateNow(&hm, D3D12_RESOURCE_STATE_GENERIC_READ, sizeof(hm));
  myDiffuseMapGenInput.UpdateNow(&dm, D3D12_RESOURCE_STATE_GENERIC_READ, sizeof(dm));

  myBumpMap.SetState(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
  myHeightMap.SetState(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
  myDiffuseMap.SetState(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

  MyRenderer* ren_p = MyRenderer::GetInstance();
  ren_p->BeginCompute();
  ren_p->Compute(&myHeightGenPipeline,
                 &myHeightGenDescHeap,
                 DM::Vec3u(myTextureSize.x / 32, myTextureSize.y / 32, 1));
  ren_p->EndCompute();
  ren_p->BeginCompute();
  ren_p->Compute(&myDiffuseGenPipeline,
                 &myDiffuseGenDescHeap,
                 DM::Vec3u(myTextureSize.x / 32, myTextureSize.y / 32, 1));
  ren_p->EndCompute();
  ren_p->BeginCompute();
  ren_p->Compute(
      &myBumpGenPipeline, &myBumpGenDescHeap, DM::Vec3u(myTextureSize.x, myTextureSize.y, 1));
  ren_p->EndCompute();

  myBumpMap.SetState(D3D12_RESOURCE_STATE_GENERIC_READ);
  myHeightMap.SetState(D3D12_RESOURCE_STATE_GENERIC_READ);
  myDiffuseMap.SetState(D3D12_RESOURCE_STATE_GENERIC_READ);
}

void Map::Draw()
{
  MeshPerDetailLevel* dl_p = &myDetailLevels[myCurrentDetailLevel];

  for (uint i = 0; i < ICOSAHEDRON_SIDES; i++)
  {
    mySides[i].SetMesh(&dl_p->sides[i]);
    if (myTopLevelNormals[i].Dot(myLocalCameraDirection) < 0.3f)
      mySides[i].Draw();
  }
  myWaterDrawable.Draw();
}

void Map::_CreateIcosahedronAndSubdivide(
    IcosahedronSideDuringCreation icosahedronSide[ICOSAHEDRON_SIDES], uint subdivisions)
{
  float     phi                            = (1.0f + sqrt(5.0f)) * 0.5f;
  float     a                              = 1.0f;
  float     b                              = 1.0f / phi;
  DM::Vec3f icosahedron[ICOSAHEDRON_SIDES] = {DM::Vec3f(0.0f, b, -a),
                                              DM::Vec3f(b, a, 0.0f),
                                              DM::Vec3f(-b, a, 0.0f),
                                              DM::Vec3f(0.0f, b, a),
                                              DM::Vec3f(0.0f, -b, a),
                                              DM::Vec3f(-a, 0.0f, b),
                                              DM::Vec3f(0.0f, -b, -a),
                                              DM::Vec3f(a, 0.0f, -b),
                                              DM::Vec3f(a, 0.0f, b),
                                              DM::Vec3f(-a, 0.0f, -b),
                                              DM::Vec3f(b, -a, 0.0f),
                                              DM::Vec3f(-b, -a, 0.0f)};

  uint indices[] = {1, 2,  0,  2, 1, 3, 4, 5, 3, 8,  4, 3,  6, 7, 0,  9,  6, 0, 10, 11,
                    4, 11, 10, 6, 5, 9, 2, 9, 5, 11, 7, 8,  1, 8, 7,  10, 5, 2, 3,  1,
                    8, 3,  2,  9, 0, 7, 1, 0, 9, 11, 6, 10, 7, 6, 11, 5,  4, 8, 10, 4};
  uint it        = 0;

  for (uint side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    icosahedronSide[side].detailLevels.resize(subdivisions);
    icosahedronSide[side].detailLevels[0].detailLevel = 0;
    icosahedronSide[side].detailLevels[0].points.resize(3);
    icosahedronSide[side].detailLevels[0].triangles.resize(1);
    icosahedronSide[side].detailLevels[0].triangles[0] = Triangle(0, 1, 2);
    for (uint i = 0; i < 3; i++)
    {
      icosahedronSide[side].detailLevels[0].points[i] = icosahedron[indices[it++]];
    }

    for (uint subDiv = 1; subDiv < subdivisions; subDiv++)
    {
      icosahedronSide[side].detailLevels[subDiv] = icosahedronSide[side].detailLevels[subDiv - 1];
      icosahedronSide[side].detailLevels[subDiv].detailLevel = subDiv;
      _Subdivide(icosahedronSide[side].detailLevels[subDiv]);
    }
  }
}

void Map::_Subdivide(DetailLevelDuringCreation& detail)
{
  uint numTri    = (uint)detail.triangles.size();
  uint lastTri   = numTri;
  uint numTriNew = numTri;
  detail.triangles.resize(numTri + numTri * 3u);
  std::unordered_map<DM::Vec3f, uint> pointTriMap;

  for (uint triIdx = 0; triIdx < numTri; triIdx++)
  {
    DM::Vec3f a = detail.points[detail.triangles[triIdx].A];
    DM::Vec3f b = detail.points[detail.triangles[triIdx].B];
    DM::Vec3f c = detail.points[detail.triangles[triIdx].C];

    DM::Vec3f ab = a + (b - a) * 0.5f;
    DM::Vec3f bc = b + (c - b) * 0.5f;
    DM::Vec3f ca = c + (a - c) * 0.5f;

    uint abIdx = 0;
    uint bcIdx = 0;
    uint caIdx = 0;

    if (pointTriMap.find(ab) == pointTriMap.end())
    {
      detail.points.push_back(ab);
      abIdx           = (uint)detail.points.size() - 1;
      pointTriMap[ab] = abIdx;
    }
    else
    {
      abIdx = pointTriMap[ab];
    }
    if (pointTriMap.find(bc) == pointTriMap.end())
    {
      detail.points.push_back(bc);
      bcIdx           = (uint)detail.points.size() - 1;
      pointTriMap[bc] = bcIdx;
    }
    else
    {
      bcIdx = pointTriMap[bc];
    }
    if (pointTriMap.find(ca) == pointTriMap.end())
    {
      detail.points.push_back(ca);
      caIdx           = (uint)detail.points.size() - 1;
      pointTriMap[ca] = caIdx;
    }
    else
    {
      caIdx = pointTriMap[ca];
    }
    Triangle temp = detail.triangles[triIdx];

    detail.triangles[triIdx]    = Triangle(temp.A, abIdx, caIdx);
    detail.triangles[lastTri++] = Triangle(temp.B, bcIdx, abIdx);
    detail.triangles[lastTri++] = Triangle(temp.C, caIdx, bcIdx);
    detail.triangles[lastTri++] = Triangle(caIdx, abIdx, bcIdx);
  }
}

void Map::_CreateVertices(Icosahedron&                  icosahedron,
                          IcosahedronSideDuringCreation sides[ICOSAHEDRON_SIDES])
{
  static const float PI = DirectX::XM_PI;
  for (uint side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    uint detailLevels = (uint)sides[side].detailLevels.size();
    icosahedron.sides[side].detailLevel.resize(detailLevels);

    for (uint level = 0; level < detailLevels; level++)
    {
      uint numVerts = (uint)sides[side].detailLevels[level].points.size();
      uint numTris  = (uint)sides[side].detailLevels[level].triangles.size();
      icosahedron.sides[side].detailLevel[level].vertices.resize(numVerts);
      icosahedron.sides[side].detailLevel[level].indices.resize(numTris * 3);
      for (uint v = 0; v < numVerts; v++)
      {
        DirectX::XMFLOAT4A position =
            sides[side].detailLevels[level].points[v].Normalize().AsXmAsXmFloat4A(1.0f);
        icosahedron.sides[side].detailLevel[level].vertices[v].vertexBasic.position = position;
        icosahedron.sides[side].detailLevel[level].vertices[v].vertexBasic.normal   = position;
        icosahedron.sides[side].detailLevel[level].vertices[v].vertexBasic.normal.w = 0.0f;
        icosahedron.sides[side].detailLevel[level].vertices[v].vertexBasic.uv.x =
            0.5f + (std::atan2(position.z, position.x) / (2.0f * PI));
        icosahedron.sides[side].detailLevel[level].vertices[v].vertexBasic.uv.y =
            0.5f - (std::asin(position.y) / PI);
      }
      uint idxCounter = 0;
      for (uint triIdx = 0; triIdx < numTris; triIdx++)
      {
        Triangle triangle = sides[side].detailLevels[level].triangles[triIdx];
        icosahedron.sides[side].detailLevel[level].indices[idxCounter++] = triangle.A;
        icosahedron.sides[side].detailLevel[level].indices[idxCounter++] = triangle.B;
        icosahedron.sides[side].detailLevel[level].indices[idxCounter++] = triangle.C;

        DM::Vec3f v0 =
            icosahedron.sides[side].detailLevel[level].vertices[triangle.A].vertexBasic.position;
        DM::Vec3f v1 =
            icosahedron.sides[side].detailLevel[level].vertices[triangle.B].vertexBasic.position;
        DM::Vec3f v2 =
            icosahedron.sides[side].detailLevel[level].vertices[triangle.C].vertexBasic.position;
        DM::Vec2f uv0 =
            icosahedron.sides[side].detailLevel[level].vertices[triangle.A].vertexBasic.uv;
        DM::Vec2f uv1 =
            icosahedron.sides[side].detailLevel[level].vertices[triangle.B].vertexBasic.uv;
        DM::Vec2f uv2 =
            icosahedron.sides[side].detailLevel[level].vertices[triangle.C].vertexBasic.uv;

        DM::Vec3f e0 = v1 - v0;
        DM::Vec3f e1 = v2 - v0;

        if (level == 0)
        {
          myTopLevelNormals[side] = e1.Cross(e0).Normalize();
        }
      }
    }
  }
}

void Map::_SetupDetailLevels(const Icosahedron& icosahedron, uint divisions)
{
  myDetailLevels.resize(divisions);

  for (uint div = 0; div < divisions; div++)
  {
    for (uint side = 0; side < ICOSAHEDRON_SIDES; side++)
    {
      Mesh* mesh_p = &myDetailLevels[div].sides[side];
      mesh_p->SetMesh(icosahedron.sides[side].detailLevel[div].vertices,
                      icosahedron.sides[side].detailLevel[div].indices,
                      VertexType::VertexBasic);
      mesh_p->CreateBuffers(true);
    }
  }
  myRenderDescHeap.Create(
      {&Camera::VIEW_PROJECTION_CB, &myWorldMatrix, myWaterDrawable.GetWorldMatrixConstantBuffer()},
      {&myHeightMap, &myBumpMap, &myDiffuseMap, &myLights},
      {});
}

void Map::_CalcDetailLevel(Camera* camera_p)
{
  if (camera_p == nullptr)
  {
    myCurrentDetailLevel = 0;
    return;
  }

  DM::Vec3f cameraPos = camera_p->GetPosition();

  DM::Mat4x4f worldMatrixInverse = GetWorldMatrix().Inverse();
  cameraPos                      = cameraPos * worldMatrixInverse;
  float distanceFromPlanet       = cameraPos.Length();
  float t                        = distanceFromPlanet / LOD_MAX_DISTANCE;

  myLocalCameraDirection = (cameraPos * -1.0f).Normalize();

  myCurrentDetailLevel =
      myTotalDetailLevels - std::min((uint)(myTotalDetailLevels * t), myTotalDetailLevels);
  myCurrentDetailLevel = std::min(myCurrentDetailLevel, myTotalDetailLevels - 1);
  myCurrentDetailLevel = std::max(myCurrentDetailLevel, 3u);
}

void Map::_SetupGraphicPipelineState()
{
  myGraphicPipeline.SetVertexShader("assets/shaders/PlanetVertexShader.hlsl");
  myGraphicPipeline.SetPixelShader("assets/shaders/PlanetPixelShader.hlsl");
  myGraphicPipeline.GenerateInputElementDesc();
  myGraphicPipeline.CreatePipelineState();
  for (uint i = 0; i < ICOSAHEDRON_SIDES; i++)
  {
    mySides[i].SetCustomResourceDescriptorHeap(&myRenderDescHeap);
    mySides[i].SetGraphicsPipelineState(&myGraphicPipeline);
  }
}

void Map::_SetupComputePipelineState()
{
  myHeightGenPipeline.SetComputeShader("assets/shaders/GenerateHightmap.hlsl");
  myHeightGenPipeline.CreatePipelineState();
  myDiffuseGenPipeline.SetComputeShader("assets/shaders/GenerateDiffuse.hlsl");
  myDiffuseGenPipeline.CreatePipelineState();
  myBumpGenPipeline.SetComputeShader("assets/shaders/GenerateBump.hlsl");
  myBumpGenPipeline.CreatePipelineState();

  myHeightGenDescHeap.Create({&myHeightMapGenInput}, {}, {&myHeightMap});
  myDiffuseGenDescHeap.Create({&myDiffuseMapGenInput}, {}, {&myHeightMap, &myDiffuseMap});
  myBumpGenDescHeap.Create({}, {}, {&myHeightMap, &myBumpMap});
}

void Map::_SetupTextures(const DM::Vec2u& textureResulotion)
{
  myHeightMap.Create(textureResulotion.x, textureResulotion.y, DXGI_FORMAT_R32_FLOAT);
  myDiffuseMap.Create(textureResulotion.x, textureResulotion.y);
  myBumpMap.Create(textureResulotion.x, textureResulotion.y, DXGI_FORMAT_R32G32B32A32_FLOAT);
}

void Map::_CreateWater(const Icosahedron& icosahedron, uint waterDetailLevel, float waterTiles)
{
  uint numVertsPerSide   = (uint)icosahedron.sides[0].detailLevel[waterDetailLevel].vertices.size();
  uint nrOfWaterVertices = numVertsPerSide * ICOSAHEDRON_SIDES;
  uint nrOfWaterIndices =
      (uint)icosahedron.sides[0].detailLevel[waterDetailLevel].indices.size() * ICOSAHEDRON_SIDES;
  uint                nrOfWaterTangents = nrOfWaterIndices / 3;
  std::vector<Vertex> water(nrOfWaterVertices);

  uint waterVertexCounter = 0;
  for (uint side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    for (uint i = 0; i < numVertsPerSide; i++)
    {
      water[waterVertexCounter].vertexBasic =
          icosahedron.sides[side].detailLevel[waterDetailLevel].vertices[i].vertexBasic;
      water[waterVertexCounter].vertexBasic.uv.x *= waterTiles;
      water[waterVertexCounter].vertexBasic.uv.y *= waterTiles;
      waterVertexCounter++;
    }
  }

  std::vector<TangentBitangent> tan(nrOfWaterTangents);
  std::vector<uint>             idx(nrOfWaterIndices);

  uint waterIndexCounter   = 0;
  uint waterTangentCounter = 0;
  uint idxOffset           = 0;
  for (uint side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    const IcosahedronSide*   side_p    = &icosahedron.sides[side];
    const std::vector<uint>* indices_p = &side_p->detailLevel[waterDetailLevel].indices;
    for (uint i = 0; i < indices_p->size(); i += 3)
    {
      uint      idx1 = indices_p->at(i + 0);
      uint      idx2 = indices_p->at(i + 1);
      uint      idx3 = indices_p->at(i + 2);
      DM::Vec3f v0   = side_p->detailLevel[waterDetailLevel].vertices[idx1].vertexBasic.position;
      DM::Vec3f v1   = side_p->detailLevel[waterDetailLevel].vertices[idx2].vertexBasic.position;
      DM::Vec3f v2   = side_p->detailLevel[waterDetailLevel].vertices[idx3].vertexBasic.position;
      DM::Vec2f uv0  = side_p->detailLevel[waterDetailLevel].vertices[idx1].vertexBasic.uv;
      DM::Vec2f uv1  = side_p->detailLevel[waterDetailLevel].vertices[idx2].vertexBasic.uv;
      DM::Vec2f uv2  = side_p->detailLevel[waterDetailLevel].vertices[idx3].vertexBasic.uv;
      DM::Vec3f e0   = v1 - v0;
      DM::Vec3f e1   = v2 - v0;
      DM::Vec2f dUv0 = uv1 - uv0;
      DM::Vec2f dUv1 = uv2 - uv0;
      float     r    = 1.0f / (dUv0.x * dUv1.y - dUv1.x * dUv0.y);

      DM::Vec3f tangent((dUv1.y * e0.x - dUv0.y * e1.x) * r,
                        (dUv1.y * e0.y - dUv0.y * e1.y) * r,
                        (dUv1.y * e0.z - dUv0.y * e1.z) * r);
      tangent = tangent.Normalize();
      DM::Vec3f bitangent((-dUv1.x * e0.x - dUv0.x * e1.x) * r,
                          (-dUv1.x * e0.y - dUv0.x * e1.y) * r,
                          (-dUv1.x * e0.z - dUv0.x * e1.z) * r);
      bitangent                            = bitangent.Normalize();
      tan[waterTangentCounter].tangent     = tangent.AsXmAsXmFloat4A(0.0f);
      tan[waterTangentCounter++].bitangent = bitangent.AsXmAsXmFloat4A(0.0f);
      idx[waterIndexCounter++]             = idx1 + idxOffset;
      idx[waterIndexCounter++]             = idx2 + idxOffset;
      idx[waterIndexCounter++]             = idx3 + idxOffset;
    }
    idxOffset += numVertsPerSide;
  }
  myWaterMesh.SetMesh(water, idx, VertexType::VertexBasic);
  myWaterMesh.CreateBuffers(true);

  myWaterTangents.Create(sizeof(TangentBitangent), nrOfWaterTangents);
  myWaterTangents.UpdateNow(
      tan.data(), D3D12_RESOURCE_STATE_GENERIC_READ);

  TextureLoader::Image waterNormalMap =
      TextureLoader::LoadImageData("assets/textures/waterBump.jpeg");

  myWaterBumpMap.Create(waterNormalMap.width, waterNormalMap.width);
  myWaterBumpMap.UpdateNow(waterNormalMap.pixels.data(), D3D12_RESOURCE_STATE_GENERIC_READ);

  WaterUVoffset wo;
  wo.waterUV = myWaterOffset;

  myWaterOffsetBuffer.Create(sizeof(WaterUVoffset));
  myWaterOffsetBuffer.UpdateNow(&wo, D3D12_RESOURCE_STATE_GENERIC_READ);

  myWaterResourceDescHeap.Create({&Camera::VIEW_PROJECTION_CB,
                                  myWaterDrawable.GetWorldMatrixConstantBuffer(),
                                  &myWaterOffsetBuffer},
                                 {&myWaterTangents, &myWaterBumpMap, &myLights},
                                 {});

  myWaterGraphicPipeline.SetVertexShader("assets/shaders/WaterVertexShader.hlsl");
  myWaterGraphicPipeline.SetPixelShader("assets/shaders/WaterPixelShader.hlsl");
  myWaterGraphicPipeline.EnableBlending();
  myWaterGraphicPipeline.GenerateInputElementDesc();
  myWaterGraphicPipeline.CreatePipelineState();

  myWaterDrawable.SetMesh(&myWaterMesh);
  myWaterDrawable.SetGraphicsPipelineState(&myWaterGraphicPipeline);
  myWaterDrawable.SetCustomResourceDescriptorHeap(&myWaterResourceDescHeap);
}
