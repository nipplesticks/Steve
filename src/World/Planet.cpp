#include "Planet.h"
#include "../Noise/PerlinNoise.h"
#include "../renderer/camera/Camera.h"
#include "../renderer/d3d12/Renderer.h"
#include "../renderer/textureLoader/TextureLoader.h"
#include "../utility/Timer.h"
#include <iostream>
#include <map>
#include <unordered_map>

//https://mft-dev.dk/uv-mapping-sphere/
Planet::Planet()
    : Drawable()
{ }

Planet::~Planet() { }

void pushIndices(uint a, uint b, uint c, std::vector<uint>& vec)
{
  vec.push_back(a);
  vec.push_back(b);
  vec.push_back(c);
}

void Planet::Create(float size, uint div, float uvTiles, GenerationType genType)
{
  DM::Vec4f waterLevel(genType.waterLevel);

  myWaterLevel.Init(sizeof(waterLevel));
  myWaterLevel.Update(&waterLevel, sizeof(waterLevel));

  if (fabs(uvTiles) < FLT_EPSILON)
    uvTiles = 1.0f;

  std::vector<DM::Vec3f> points;
  std::vector<uint>      indices;
  std::vector<Vertex>    verts;
  std::vector<uint>      wrappedIndices;

  _createIcosahedronAndSubdivide(indices, points, div);

  _createVertices(verts, points);

  //_detectWrappedUVCoords(indices, verts, wrappedIndices);

  //_fixWrappedUVCoords(wrappedIndices, indices, verts);

  //_fixSharedPoleVertices(indices, verts);

  //_scaleUVs(verts, uvTiles);

  _calcTangent(indices, verts);


  std::cout << "nrOfVerts: \t" << verts.size() << std::endl;
  std::cout << "nrOfTris: \t" << indices.size() / 3 << std::endl;
  std::cout << "nrOfIdx: \t" << indices.size() << std::endl;

  TextureLoader::Image H, D, B;
  H.width = D.width = B.width = genType.texWidth;
  H.height = D.height = B.height = genType.texHeight;
  H.pixels.resize(genType.texWidth * genType.texHeight * 4);
  D.pixels.resize(genType.texWidth * genType.texHeight * 4);

  myMesh.SetMesh(std::move(verts));
  myMesh.SetIndices(std::move(indices));
  myMesh.CreateBuffers();

  uint w, h;
  myMesh.SetImages(std::move(D));
  uint8*                 img_p = myMesh.GetRawImage(0, &w, &h);
  std::vector<DM::Vec4f> dummy(w * h);
  myTextureBuffer.Init(w, h);
  myTextureBuffer.Update(Renderer::GetInstance(), img_p);
  myHeightMapBuffer.Init(H.width, H.height, DXGI_FORMAT_R32G32B32A32_FLOAT);
  myHeightMapBuffer.Update(Renderer::GetInstance(), dummy.data());
  myBumpMapBuffer.Init(B.width, B.height, DXGI_FORMAT_R32G32B32A32_FLOAT);
  myBumpMapBuffer.Update(Renderer::GetInstance(), dummy.data());

  SetTexture(&myTextureBuffer);
  SetMesh(&myMesh);
}

void Planet::UpdateGeneration(GenerationType genType)
{
  TextureLoader::Image H, D;
  _generateHeightMapAndTexture(&H, &D, genType);
  myHeightMapBuffer.Update(Renderer::GetInstance(), H.pixels.data());
  myTextureBuffer.Update(Renderer::GetInstance(), D.pixels.data());
  DM::Vec4f waterLevel((float)genType.waterLevel);
  myWaterLevel.Update(&waterLevel, sizeof(waterLevel));
}

void Planet::SetWaterLevel(float wl)
{
  DM::Vec4f waterLevel(wl);
  myWaterLevel.Update(&waterLevel, sizeof(waterLevel));
}

const Mesh& Planet::GetMesh() const
{
  return myMesh;
}

void Planet::Bind()
{
  myResourceDescHeap.Create({&Camera::VIEW_PROJECTION_CB, &myWorldConstantBuffer, &myWaterLevel},
                            {myTextureBuffer_p},
                            {});
  myIsBinded = true;
}

void Planet::BindForOffsetGpu()
{
  myResourceDescHeap.Create({&Camera::VIEW_PROJECTION_CB, &myWorldConstantBuffer, &myWaterLevel},
                            {&myHeightMapBuffer, &myBumpMapBuffer, &myTextureBuffer},
                            {});

  myIsBinded = true;
}

TextureBuffer* Planet::GetHeightMap()
{
  return &myHeightMapBuffer;
}

TextureBuffer* Planet::GetDiffuse()
{
  return &myTextureBuffer;
}

TextureBuffer* Planet::GetBump()
{
  return &myBumpMapBuffer;
}

ConstantBuffer* Planet::GetWaterLevelCb()
{
  return &myWaterLevel;
}

void Planet::_createIcosahedronAndSubdivide(std::vector<uint>&      indices,
                                            std::vector<DM::Vec3f>& vertices,
                                            uint                    divitions)
{
  Timer t;
  t.Start();
  _createIcosahedron(indices, vertices);
  {
    std::vector<Triangle> tri(indices.size() / 3u);
    uint                  triCounter = 0;
    for (uint i = 0; i < indices.size(); i += 3)
    {
      tri[triCounter].A   = indices[i];
      tri[triCounter].B   = indices[i + 1];
      tri[triCounter++].C = indices[i + 2];
    }
    indices.clear();
    for (uint i = 0; i < divitions; i++)
    {
      _subdivideIcosahedron(tri, vertices);
    }
    indices.resize(tri.size() * 3u);
    uint indCounter = 0;
    for (uint i = 0; i < tri.size(); i++)
    {
      indices[indCounter++] = tri[i].A;
      indices[indCounter++] = tri[i].B;
      indices[indCounter++] = tri[i].C;
    }
  }
  double divTime = t.Stop();
  std::cout << "Created and subdivided icosahedron in: " << divTime << " seconds\n";
}

void Planet::_createIcosahedron(std::vector<uint>& indices, std::vector<DM::Vec3f>& vertices)
{
  float phi = (1.0f + sqrt(5.0f)) * 0.5f; // Golder Ratio
  float a   = 1.0f;
  float b   = 1.0f / phi;
  vertices.resize(12);
  indices.clear();

  uint idx        = 0;
  vertices[idx++] = DM::Vec3f(0, b, -a);
  vertices[idx++] = DM::Vec3f(b, a, 0);
  vertices[idx++] = DM::Vec3f(-b, a, 0);
  vertices[idx++] = DM::Vec3f(0, b, a);
  vertices[idx++] = DM::Vec3f(0, -b, a);
  vertices[idx++] = DM::Vec3f(-a, 0, b);
  vertices[idx++] = DM::Vec3f(0, -b, -a);
  vertices[idx++] = DM::Vec3f(a, 0, -b);
  vertices[idx++] = DM::Vec3f(a, 0, b);
  vertices[idx++] = DM::Vec3f(-a, 0, -b);
  vertices[idx++] = DM::Vec3f(b, -a, 0);
  vertices[idx++] = DM::Vec3f(-b, -a, 0);

  pushIndices(1, 2, 0, indices);
  pushIndices(2, 1, 3, indices);
  pushIndices(4, 5, 3, indices);
  pushIndices(8, 4, 3, indices);
  pushIndices(6, 7, 0, indices);
  pushIndices(9, 6, 0, indices);
  pushIndices(10, 11, 4, indices);
  pushIndices(11, 10, 6, indices);
  pushIndices(5, 9, 2, indices);
  pushIndices(9, 5, 11, indices);
  pushIndices(7, 8, 1, indices);
  pushIndices(8, 7, 10, indices);
  pushIndices(5, 2, 3, indices);
  pushIndices(1, 8, 3, indices);
  pushIndices(2, 9, 0, indices);
  pushIndices(7, 1, 0, indices);
  pushIndices(9, 11, 6, indices);
  pushIndices(10, 7, 6, indices);
  pushIndices(11, 5, 4, indices);
  pushIndices(8, 10, 4, indices);
}

void Planet::_subdivideIcosahedron(std::vector<Triangle>&  triangles,
                                   std::vector<DM::Vec3f>& vertices)
{
  uint numTri    = (uint)triangles.size();
  uint lastTri   = numTri;
  uint numTriNew = numTri;
  triangles.resize(numTri + numTri * 3u);

  std::unordered_map<DM::Vec3f, uint> vertIdxMap;

  for (uint triIdx = 0; triIdx < numTri; triIdx++)
  {
    DM::Vec3f a = vertices[triangles[triIdx].A];
    DM::Vec3f b = vertices[triangles[triIdx].B];
    DM::Vec3f c = vertices[triangles[triIdx].C];

    DM::Vec3f ab = a + (b - a) * 0.5f;
    DM::Vec3f bc = b + (c - b) * 0.5f;
    DM::Vec3f ca = c + (a - c) * 0.5f;

    uint abIdx = 0;
    uint bcIdx = 0;
    uint caIdx = 0;

    if (vertIdxMap.find(ab) == vertIdxMap.end())
    {
      vertices.push_back(ab);
      abIdx          = (uint)vertices.size() - 1;
      vertIdxMap[ab] = abIdx;
    }
    else
    {
      abIdx = vertIdxMap[ab];
    }
    if (vertIdxMap.find(bc) == vertIdxMap.end())
    {
      vertices.push_back(bc);
      bcIdx          = (uint)vertices.size() - 1;
      vertIdxMap[bc] = bcIdx;
    }
    else
    {
      bcIdx = vertIdxMap[bc];
    }
    if (vertIdxMap.find(ca) == vertIdxMap.end())
    {
      vertices.push_back(ca);
      caIdx          = (uint)vertices.size() - 1;
      vertIdxMap[ca] = caIdx;
    }
    else
    {
      caIdx = vertIdxMap[ca];
    }

    Triangle temp = triangles[triIdx];

    triangles[triIdx]    = Triangle(temp.A, abIdx, caIdx);
    triangles[lastTri++] = Triangle(temp.B, bcIdx, abIdx);
    numTriNew++;
    triangles[lastTri++] = Triangle(temp.C, caIdx, bcIdx);
    numTriNew++;
    triangles[lastTri++] = Triangle(caIdx, abIdx, bcIdx);
    numTriNew++;
  }
}

void Planet::_createVertices(std::vector<Vertex>& verts, const std::vector<DM::Vec3f>& points)
{
  verts.resize(points.size());
  Vertex defaultVert = {};
  defaultVert.color  = DirectX::XMFLOAT4A(1, 1, 1, 1);
  float PI           = DirectX::XM_PI;
  for (uint i = 0; i < points.size(); i++)
  {
    verts[i]          = defaultVert;
    verts[i].position = points[i].Normalize().AsXmFloat4APoint();
    verts[i].normal   = points[i].Normalize().AsXmFloat4AVector();
    verts[i].uv.x     = 0.5f + (std::atan2(verts[i].position.z, verts[i].position.x) / (2.0f * PI));
    verts[i].uv.y     = 0.5f - (std::asin(verts[i].position.y) / PI);
  }
}

void Planet::_detectWrappedUVCoords(std::vector<uint>&   indices,
                                    std::vector<Vertex>& vertices,
                                    std::vector<uint>&   wrappedIndices)
{
  uint nrOfIndices = (uint)indices.size();

  for (uint i = 0; i < nrOfIndices; i += 3)
  {
    uint a = indices[i];
    uint b = indices[i + 1];
    uint c = indices[i + 2];

    DM::Vec3f texA(vertices[a].uv.x, vertices[a].uv.y, 0.0f);
    DM::Vec3f texB(vertices[b].uv.x, vertices[b].uv.y, 0.0f);
    DM::Vec3f texC(vertices[c].uv.x, vertices[c].uv.y, 0.0f);
    DM::Vec3f texNormal = (texC - texA).Cross(texB - texA);
    if (texNormal.z < 0)
      wrappedIndices.push_back(i);
  }
}

void Planet::_fixWrappedUVCoords(std::vector<uint>&   wrapped,
                                 std::vector<uint>&   indices,
                                 std::vector<Vertex>& vertices)
{
  uint                           verticeIndex = (uint)vertices.size() - 1;
  std::unordered_map<uint, uint> visited;

  for (auto& i : wrapped)
  {
    uint   a = indices[i];
    uint   b = indices[i + 1];
    uint   c = indices[i + 2];
    Vertex A = vertices[a];
    Vertex B = vertices[b];
    Vertex C = vertices[c];

    if (A.uv.x < 0.25f)
    {
      uint tempA = a;
      if (visited.find(a) == visited.end())
      {
        A.uv.x += 1.0f;
        vertices.push_back(A);
        verticeIndex++;
        visited.insert(std::make_pair(a, verticeIndex));
        tempA = verticeIndex;
      }
      else
      {
        tempA = visited[a];
      }
      a = tempA;
    }
    if (B.uv.x < 0.25f)
    {
      uint tempB = b;
      if (visited.find(b) == visited.end())
      {
        B.uv.x += 1.0f;
        vertices.push_back(B);
        verticeIndex++;
        visited.insert(std::make_pair(b, verticeIndex));
        tempB = verticeIndex;
      }
      else
      {
        tempB = visited[b];
      }
      b = tempB;
    }
    if (C.uv.x < 0.25f)
    {
      uint tempC = c;
      if (visited.find(c) == visited.end())
      {
        C.uv.x += 1.0f;
        vertices.push_back(C);
        verticeIndex++;
        visited.insert(std::make_pair(c, verticeIndex));
        tempC = verticeIndex;
      }
      else
      {
        tempC = visited[c];
      }
      c = tempC;
    }
    indices[i]     = a;
    indices[i + 1] = b;
    indices[i + 2] = c;
  }
}

void Planet::_fixSharedPoleVertices(std::vector<uint>& indices, std::vector<Vertex>& vertices)
{
  uint northIdx  = UINT_MAX;
  uint southIdx  = UINT_MAX;
  uint vertexIdx = (uint)vertices.size() - 1;
  for (uint i = 0; i < vertices.size(); i++)
  {
    if (northIdx != UINT_MAX && southIdx != UINT_MAX)
      break;

    if (vertices[i].position.y == 1.0f)
      northIdx = i;
    if (vertices[i].position.y == -1.0f)
      southIdx = i;
  }

  for (uint i = 0; i < indices.size(); i++)
  {
    if (indices[i] == northIdx)
    {
      uint   startIdx = i - (i % 3);
      Vertex A        = vertices[indices[startIdx]];
      Vertex B        = vertices[indices[startIdx + 1]];
      Vertex C        = vertices[indices[startIdx + 2]];
      Vertex newNorth = vertices[northIdx];
      newNorth.uv.x   = (B.uv.x + C.uv.x) * 0.5f;
      vertexIdx++;
      vertices.push_back(newNorth);
      indices[i] = vertexIdx;
    }
    else if (indices[i] == southIdx)
    {
      uint   startIdx = i - (i % 3);
      Vertex A        = vertices[indices[startIdx]];
      Vertex B        = vertices[indices[startIdx + 1]];
      Vertex C        = vertices[indices[startIdx + 2]];
      Vertex newSouth = vertices[southIdx];
      newSouth.uv.x   = (B.uv.x + C.uv.x) * 0.5f;
      vertexIdx++;
      vertices.push_back(newSouth);
      indices[i] = vertexIdx;
    }
  }
}

void Planet::_scaleUVs(std::vector<Vertex>& vertices, float uvTiles)
{
  for (auto& v : vertices)
  {
    v.uv.x *= uvTiles;
    v.uv.y *= uvTiles;
  }
}

void Planet::_offsetBasedOnHeightMap(TextureLoader::Image* heightMap,
                                     std::vector<uint>&    indices,
                                     std::vector<Vertex>&  verts)
{
  uint8 maxValue = 0;
  uint8 minValue = UINT8_MAX;

  for (uint i = 0; i < heightMap->width * heightMap->height; i++)
  {
    uint x = i % heightMap->width;
    uint y = i / heightMap->width;

    uint8 r = heightMap->GetPixel(x, y).r;

    minValue = std::min(minValue, r);
    maxValue = std::max(maxValue, r);
  }
  std::cout << "max: " << (int)maxValue << std::endl;
  std::cout << "min: " << (int)minValue << std::endl;
  float asd = 0.0f;

  uint8 range = maxValue - minValue;

  auto GetHeight = [&](uint x, uint y, uint sampleSize, float pw) {
    uint8 hValue = heightMap->GetAveragePixel(x, y, sampleSize).r;
    return (float)hValue / 255.0f;
  };

  for (auto& v : verts)
  {
    float _x = (fmodf(v.uv.x, 1.0f));
    float _y = (fmodf(v.uv.y, 1.0f));

    if (v.uv.x < 0)
      _x = 1.0f + _x;
    if (v.uv.y < 0)
      _y = 1.0f + _y;

    uint x = (uint)(heightMap->width * _x);
    uint y = (uint)(heightMap->height * _y);

    float height = GetHeight(x, y, 0, 0.5f);

    DM::Vec3f nor = v.normal;
    DM::Vec3f pos = v.position;
    pos           = pos + nor * height;
    v.position    = pos.AsXmFloat4APoint();
  }

  struct TempNor
  {
    DM::Vec3f allNormals  = DM::Vec3f(0.0f, 0.0f, 0.0f);
    uint      nrOfNormals = 0;
  };

  std::vector<TempNor> tempNor(verts.size());

  for (uint i = 0; i < indices.size(); i += 3)
  {
    uint i1 = indices[i];
    uint i2 = indices[i + 1];
    uint i3 = indices[i + 2];

    DM::Vec3f v1 = verts[i1].position;
    DM::Vec3f v2 = verts[i2].position;
    DM::Vec3f v3 = verts[i3].position;
    DM::Vec3f e0 = v2 - v1;
    DM::Vec3f e1 = v3 - v1;
    DM::Vec3f n  = e1.Cross(e0).Normalize();

    tempNor[i1].allNormals = tempNor[i1].allNormals + n;
    tempNor[i1].nrOfNormals++;
    tempNor[i2].allNormals = tempNor[i2].allNormals + n;
    tempNor[i2].nrOfNormals++;
    tempNor[i3].allNormals = tempNor[i3].allNormals + n;
    tempNor[i3].nrOfNormals++;
  }

  for (uint i = 0; i < verts.size(); i++)
  {
    DM::Vec3f n     = tempNor[i].allNormals / (float)tempNor[i].nrOfNormals;
    n               = n.Normalize();
    verts[i].normal = n.AsXmFloat4AVector();
  }
}

void Planet::_getBiomAndColor(double                       elevation,
                              double                       moisture,
                              TextureLoader::Image::Pixel& color,
                              Planet::Biom&                biom,
                              GenerationType               genType)
{
  if (elevation < genType.waterLevel)
    biom = Ocean;
  else if (elevation < genType.waterLevel + 0.02)
    biom = Beach;
  else if (elevation > 0.8)
  {
    if (moisture < 0.1)
      biom = Scorched;
    if (moisture < 0.2)
      biom = Bare;
    if (moisture < 0.5)
      biom = Tundra;
    biom = Snow;
  }
  else if (elevation > 0.6)
  {
    if (moisture < 0.33)
      biom = TemperateDesert;
    else if (moisture < 0.66)
      biom = Shrubland;
    else
      biom = Taiga;
  }
  else if (elevation > 0.3)
  {
    if (moisture < 0.16)
      biom = TemperateDesert;
    else if (moisture < 0.50)
      biom = GrassLand;
    else if (moisture < 0.83)
      biom = TemperateDeciduousForest;
    else
      biom = TemperateRainForest;
  }
  else
  {
    if (moisture < 0.16)
      biom = SubtropicalDesert;
    else if (moisture < 0.33)
      biom = GrassLand;
    else if (moisture < 0.66)
      biom = TropicalSeasonalFoest;
    else
      biom = TropicalRainForest;
  }
  color = _getColor(biom);
}

void Planet::_calcTangent(const std::vector<uint>& indices, std::vector<Vertex>& verts)
{
  for (uint i = 0; i < indices.size(); i += 3)
  {
    DM::Vec3f v0  = verts[indices[i + 0]].position;
    DM::Vec3f v1  = verts[indices[i + 1]].position;
    DM::Vec3f v2  = verts[indices[i + 2]].position;
    DM::Vec2f uv0 = verts[indices[i + 0]].uv;
    DM::Vec2f uv1 = verts[indices[i + 1]].uv;
    DM::Vec2f uv2 = verts[indices[i + 2]].uv;

    DM::Vec3f e0       = v1 - v0;
    DM::Vec3f e1       = v2 - v0;
    DM::Vec2f deltaUV0 = uv1 - uv0;
    DM::Vec2f deltaUV1 = uv2 - uv0;
    float     r        = 1.0f / (deltaUV1.x * deltaUV1.y - deltaUV0.x * deltaUV1.y);

    DM::Vec3f tangent(r * (deltaUV1.y * e0.x - deltaUV0.y * e1.x),
                      r * (deltaUV1.y * e0.y - deltaUV0.y * e1.y),
                      r * (deltaUV1.y * e0.z - deltaUV0.y * e1.z));

    tangent = tangent.Normalize();

    DM::Vec3f bitangent(r * (-deltaUV1.x * e0.x + deltaUV0.x * e1.x),
                        r * (-deltaUV1.x * e0.y + deltaUV0.x * e1.y),
                        r * (-deltaUV1.x * e0.z + deltaUV0.x * e1.z));

    bitangent = bitangent.Normalize();

    verts[indices[i + 0]].tangent   = (tangent).AsXmFloat4AVector();
    verts[indices[i + 1]].tangent   = (tangent).AsXmFloat4AVector();
    verts[indices[i + 2]].tangent   = (tangent).AsXmFloat4AVector();
    verts[indices[i + 0]].bitangent = (bitangent).AsXmFloat4AVector();
    verts[indices[i + 1]].bitangent = (bitangent).AsXmFloat4AVector();
    verts[indices[i + 2]].bitangent = (bitangent).AsXmFloat4AVector();
  }
}

TextureLoader::Image::Pixel Planet::_getColor(Planet::Biom biom)
{
  TextureLoader::Image::Pixel color;

  switch (biom)
  {
  case Planet::Ocean:
    color.SetColor(18, 17, 84);
    break;
  case Planet::Beach:
    color.SetColor(179, 162, 133);
    break;
  case Planet::Scorched:
    color.SetColor(53, 31, 25);
    break;
  case Planet::Bare:
    color.SetColor(142, 106, 80);
    break;
  case Planet::Tundra:
    color.SetColor(213, 90, 59);
    break;
  case Planet::Snow:
    color.SetColor(255, 255, 255);
    break;
  case Planet::TemperateDesert:
    color.SetColor(213, 129, 82);
    break;
  case Planet::Shrubland:
    color.SetColor(166, 165, 121);
    break;
  case Planet::Taiga:
    color.SetColor(18, 47, 16);
    break;
  case Planet::GrassLand:
    color.SetColor(82, 90, 14);
    break;
  case Planet::TemperateDeciduousForest:
    color.SetColor(120, 173, 4);
    break;
  case Planet::TemperateRainForest:
    color.SetColor(64, 80, 40);
    break;
  case Planet::SubtropicalDesert:
    color.SetColor(208, 160, 113);
    break;
  case Planet::TropicalSeasonalFoest:
    color.SetColor(75, 148, 94);
    break;
  case Planet::TropicalRainForest:
    color.SetColor(72, 120, 80);
    break;
  default:
    color.SetColor(0, 0, 0);
    break;
  }

  return color;
}

void Planet::_generateHeightMapAndTexture(TextureLoader::Image* heightMap,
                                          TextureLoader::Image* diffuse,
                                          GenerationType        genType)
{
  uint width  = genType.texWidth;
  uint height = genType.texWidth;

  heightMap->width  = width;
  heightMap->height = height;
  heightMap->pixels.resize(width * height * 4u);

  diffuse->width  = width;
  diffuse->height = height;
  diffuse->pixels.resize(width * height * 4u);

  PerlinNoise pn(genType.seed);

  static double pi = DirectX::XM_PI;
  for (uint y = 0; y < height; y++)
  {
    for (uint x = 0; x < width; x++)
    {
      double _x = (double)x / (double)width;
      double _y = (double)y / (double)height;

      double yCoord = sin(_y * pi - pi / 2);
      double xCoord = cos(_x * 2.0 * pi) * cos(_y * pi - pi / 2.0);
      double zCoord = sin(_x * 2.0 * pi) * cos(_y * pi - pi / 2.0);

      double f   = genType.height.frequency;
      double e   = 0.0;
      double div = 0.0f;
      for (uint i = 0; i < genType.height.iterations; i++)
      {
        double it = genType.height.frequency / f;
        e += it * pn.Sample(xCoord * f, yCoord * f, zCoord * f);
        div += it;
        f *= 2.0;
      }
      if (div > 0.0f)
        e = e / div;
      e = pow(e * genType.height.fudgeFactor, genType.height.exponent);

      TextureLoader::Image::Pixel heightPixel(
          (uint8)(e * 255), (uint8)(e * 255), (uint8)(e * 255), 255);

      heightMap->SetPixel(x, y, heightPixel);

      f        = genType.moisture.frequency;
      double m = 0.0;
      div      = 0.0f;
      for (uint i = 0; i < genType.moisture.iterations; i++)
      {
        double it = genType.moisture.frequency / f;
        m += it * pn.Sample(xCoord * f, yCoord * f, zCoord * f);
        div += it;
        f *= 2.0;
      }
      if (div > 0.0f)
        m = m / div;
      m = pow(m * genType.moisture.fudgeFactor, genType.moisture.exponent);
      Planet::Biom                biom;
      TextureLoader::Image::Pixel color;
      _getBiomAndColor(e, m, color, biom, genType);
      diffuse->SetPixel(x, y, color);
    }
  }
}
