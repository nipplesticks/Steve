#include "Map.h"
#include "../renderer/d3d12/myRenderer.h"
#include "../renderer/textureLoader/TextureLoader.h"
#include "../tools/WorldMeshGen.h"
#include "../utility/UtilityFuncs.h"
#include "Star.h"
#include <unordered_map>

Map::Map()
    : Transform()
{ }

void Map::SetRotationSpeed(float rotationSpeed) { }

float Map::GetHightLevelAt(const DM::Vec3f& position)
{
  DM::Vec3f p = position.Normalize();
  float     x       = 0.5f + (std::atan2(p.z, p.x) / (2.0f * DM::PI));
  float     y       = 0.5f - (std::asin(p.y) / DM::PI);
  DM::Vec2u texSize = myHeightMap.GetDimention();
  DM::Vec2i coord((int)texSize.x * x, (int)texSize.y * y);
  if (coord.x < 0)
    coord.x += texSize.x;
  if (coord.y < 0)
    coord.y += texSize.y;
  if (coord.y > texSize.x - 1)
    coord.x -= texSize.x;
  if (coord.y > texSize.y - 1)
    coord.y -= texSize.y;

  float h = (1.0f + myHeightMap.GetPixel<float>(coord.x, coord.y)) * GetScale().x;
  
  return h;
}

void Map::Create()
{
  std::vector<std::vector<Vertex>> vertices;
  std::vector<std::vector<uint>>   indices;
  std::vector<DM::Vec3f>           sideNormals;
  WorldMeshGen::GetInstance()->Load("assets/world/world.bin", vertices, indices, sideNormals);
  Create(vertices, indices, sideNormals);
}

void Map::Create(const std::vector<std::vector<Vertex>>& vertices,
                 const std::vector<std::vector<uint>>&   indices,
                 const std::vector<DM::Vec3f>&           sideNormals,
                 const DM::Vec2u&                        textureResulotion)
{
  myTextureSize = textureResulotion;
  myHeightMapGenInput.Create(sizeof(GPUGenerationInput));
  myDiffuseMapGenInput.Create(sizeof(GPUGenerationInput));
  myWorldMatrix.Create(sizeof(DefaultConstantBufferContent));
  myLights.Create(sizeof(Light), MAX_LIGHTS);

  ASSERT_STR(vertices.size() == indices.size() && vertices.size() == ICOSAHEDRON_SIDES,
             "verticesSides=%u indicesSides=%u",
             vertices.size(),
             indices.size());

  for (uint side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    myMeshes[side].SetMesh(vertices[side], indices[side], VertexType::VertexBasic);
    myMeshes[side].CreateBuffers(true);
    myTopLevelNormals[side] = sideNormals[side];
  }

  _SetupTextures(textureResulotion);
  _SetupGraphicPipelineState();
  _SetupComputePipelineState();
}

void Map::Update(float dt, Camera* camera_p)
{
  std::vector<Light> lightVector(MAX_LIGHTS);

  for (uint i = 0; i < Star::Active_Stars.size(); i++)
  {
    lightVector[i] = Star::Active_Stars[i]->GetLight();
  }
  myLights.UpdateNow(lightVector.data(), D3D12_RESOURCE_STATE_GENERIC_READ);

  DM::Mat4x4f                  worldMat = GetWorldMatrix();
  DefaultConstantBufferContent wm       = {};
  wm.worldMatrix                        = worldMat.AsXmFloat4x4A();
  wm.worldMatrixInverse                 = worldMat.Inverse().AsXmFloat4x4A();
  wm.pickableId                         = 0;
  wm.numberOfLights                     = (uint)Star::Active_Stars.size();
  myWorldMatrix.UpdateNow(&wm, D3D12_RESOURCE_STATE_GENERIC_READ);
  DM::Vec3f   cameraPos          = camera_p->GetPosition();
  DM::Mat4x4f worldMatrixInverse = GetWorldMatrix().Inverse();
  cameraPos                      = cameraPos * worldMatrixInverse;
  myLocalCameraDirection         = (cameraPos * -1.0f).Normalize();
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
    hm.waterLevel  = 0;
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
    dm.waterLevel  = 0;
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
  for (uint i = 0; i < ICOSAHEDRON_SIDES; i++)
  {
    if (myTopLevelNormals[i].Dot(myLocalCameraDirection) < 0.3f)
      mySides[i].Draw();
  }
}

void Map::_SetupGraphicPipelineState()
{
  myRenderDescHeap.Create({&Camera::VIEW_PROJECTION_CB, &myWorldMatrix},
                          {&myHeightMap, &myBumpMap, &myDiffuseMap, &myLights},
                          {});
  myGraphicPipeline.SetVertexShader("assets/shaders/PlanetVertexShader.hlsl");
  myGraphicPipeline.SetPixelShader("assets/shaders/PlanetPixelShader.hlsl");
  //myGraphicPipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
  myGraphicPipeline.GenerateInputElementDesc();
  myGraphicPipeline.CreatePipelineState();
  for (uint i = 0; i < ICOSAHEDRON_SIDES; i++)
  {
    mySides[i].SetCustomResourceDescriptorHeap(&myRenderDescHeap);
    mySides[i].SetGraphicsPipelineState(&myGraphicPipeline);
    mySides[i].SetMesh(&myMeshes[i]);
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
