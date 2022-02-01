#include "Planet.h"
#include "../renderer/Camera.h"
#include "../renderer/Renderer.h"
#include "../renderer/TextureLoader.h"
#include "../utility/Timer.h"
#include <iostream>
#include <map>
#include <unordered_map>

//https://mft-dev.dk/uv-mapping-sphere/
Planet::Planet()
    : Drawable()
{ }

Planet::~Planet() { }

//Bitmap CreateTexture(int width, int height)
//{
//  Bitmap       image        = new Bitmap(width, height);
//  double       widthFactor  = 1.0 / width;
//  double       heightFactor = 1.0 / height;
//  Color        baseColor    = Color.FromArgb(255, 127, 35, 7);
//  SimplexNoise generator    = new SimplexNoise(seed : -5000);
//  for (int x = 0; x < width; ++x)
//  {
//    for (int y = 0; y < height; ++y)
//    {
//      double dX = x / (double)width;
//      double dY = y / (double)height;
//      /* noise range is clamped -1 to 1 */
//      double noise =
//          generator.PerlinNoise(dX, dY, octaves : 3, persistence : 3.0f / 4.0f, lacunarity : 3f);
//      int   blueHue  = (int)(baseColor.B * noise) + baseColor.B;
//      int   redHue   = (int)(baseColor.R * noise) + baseColor.R;
//      int   greenHue = (int)(baseColor.G * noise) + baseColor.G;
//      Color col      = Color.FromArgb(baseColor.A, redHue, greenHue, blueHue);
//      image.SetPixel(x, y, col);
//    }
//  }
//  return image;
//}

void pushIndices(uint a, uint b, uint c, std::vector<uint>& vec)
{
  vec.push_back(a);
  vec.push_back(b);
  vec.push_back(c);
}

DM::Mat3x3 FindRotationMatrix(const DM::Vec3f& A, const DM::Vec3f& B)
{
  DM::Vec3f axis = A.Cross(B);

  const float cosA = A.Dot(B);
  const float k    = 1.0f / (1.0f + cosA);

  DM::Mat3x3 result;
  result._11 = (axis.x * axis.x * k) + cosA;
  result._12 = (axis.y * axis.x * k) - axis.z;
  result._13 = (axis.z * axis.x * k) + axis.y;
  result._21 = (axis.x * axis.y * k) + axis.z;
  result._22 = (axis.y * axis.y * k) + cosA;
  result._23 = (axis.z * axis.y * k) - axis.x;
  result._31 = (axis.x * axis.z * k) - axis.y;
  result._32 = (axis.y * axis.z * k) + axis.x;
  result._33 = (axis.z * axis.z * k) + cosA;

  return result;
}

void Planet::Create(float size, uint div, float uvTiles)
{
  if (fabs(uvTiles) < FLT_EPSILON)
  {
    uvTiles = 1.0f;
  }
  std::vector<DM::Vec3f> points;
  std::vector<uint>      indices;
  _createIcosahedron(indices, points);
  Timer t;
  t.Start();

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
    for (uint i = 0; i < div; i++)
    {
      _subdivideIcosahedron(tri, points);
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
  std::cout << "Subdivition time: " << divTime << " seconds\n";

  std::vector<Vertex> verts(points.size());
  Vertex              defaultVert = {};
  defaultVert.color               = DirectX::XMFLOAT4A(1, 1, 1, 1);
  float PI                        = DirectX::XM_PI;
  for (uint i = 0; i < points.size(); i++)
  {
    verts[i]          = defaultVert;
    verts[i].position = (points[i].Normalize()).AsXmFloat4APoint();
    //verts[i].position = points[i].AsXmFloat4APoint();
    verts[i].normal = points[i].Normalize().AsXmFloat4AVector();
    verts[i].uv.x   = 0.5f + (std::atan2(verts[i].position.z, verts[i].position.x) / (2.0f * PI));
    verts[i].uv.y   = 0.5f - (std::asin(verts[i].position.y) / PI);
  }

  std::vector<uint> wrapped = _detectWrappedUVCoords(indices, verts);
  _fixWrappedUVCoords(wrapped, indices, verts);
  _fixSharedPoleVertices(indices, verts);

  TextureLoader::Image heightMap =
      TextureLoader::LoadImageData("assets/textures/earthHeightMap.jpg");

  uint8 maxValue = 0;
  uint8 minValue = UINT8_MAX;

  for (uint i = 0; i < heightMap.width * heightMap.height; i++)
  {
    uint x = i % heightMap.width;
    uint y = i / heightMap.width;

    uint8 r = heightMap.GetPixel(x, y).r;

    minValue = std::min(minValue, r);
    maxValue = std::max(maxValue, r);
  }
  std::cout << "max: " << (int)maxValue << std::endl;
  std::cout << "min: " << (int)minValue << std::endl;
  float asd = 0.0f;

  uint8 range = maxValue - minValue;

  auto GetHeight = [&](uint x, uint y, uint sampleSize, float pw) {
    uint8 hValue   = heightMap.GetAveragePixel(x, y, sampleSize).r;
    hValue         = std::pow(hValue, pw);
    float newValue = ((float)(hValue - minValue)) / (float)range;
    return newValue;
  };

  for (auto& v : verts)
  {
    v.uv.x *= -uvTiles;
    v.uv.y *= uvTiles;

    float _x = (fmodf(v.uv.x, 1.0f));
    float _y = (fmodf(v.uv.y, 1.0f));

    if (v.uv.x < 0)
      _x = 1.0f + _x;
    if (v.uv.y < 0)
      _y = 1.0f + _y;

    uint x = heightMap.width * _x;
    uint y = heightMap.height * _y;

    float height = GetHeight(x, y, 10, 0.5f);

    DM::Vec3f nor = v.normal;
    DM::Vec3f pos = v.position;
    pos           = pos + nor * height;
    v.position    = pos.AsXmFloat4APoint();
  }

  struct TempNor
  {
    DM::Vec3f allNormals = DM::Vec3f(0.0f, 0.0f, 0.0f);
    uint      nrOfNormals = 0;
  };

  std::vector<TempNor> tempNor(verts.size());

  for (uint i = 0; i < indices.size(); i+=3)
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
    DM::Vec3f n = tempNor[i].allNormals / (float)tempNor[i].nrOfNormals;
    n           = n.Normalize();
    verts[i].normal = n.AsXmFloat4AVector();
  }


  std::cout << "nrOfVerts: \t" << verts.size() << std::endl;
  std::cout << "nrOfTris: \t" << indices.size() / 3 << std::endl;
  std::cout << "nrOfIdx: \t" << indices.size() << std::endl;

  myMesh.SetMesh(std::move(verts));
  myMesh.SetIndices(std::move(indices));
  myMesh.CreateBuffers();
  TextureLoader::Image shrek2 = TextureLoader::LoadImageData("assets/textures/testingFesting.jpg");

  uint w, h;
  myMesh.SetImages(std::move(shrek2));
  uint8* img_p = myMesh.GetRawImage(0, &w, &h);
  myTextureBuffer.Init(w, h);
  myTextureBuffer.Update(Renderer::GetInstance(), img_p);

  SetTexture(&myTextureBuffer);
  SetMesh(&myMesh);
}

const Mesh& Planet::GetMesh() const
{
  return myMesh;
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
  uint numTri    = triangles.size();
  uint lastTri   = numTri;
  uint numTriNew = numTri;
  triangles.resize(numTri + numTri * 3u);

  //std::unordered_map<DM::Vec3f, uint> vertIdxMap;
  //std::map<DM::Vec3f, uint> vertIdxMap;
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
      abIdx          = vertices.size() - 1;
      vertIdxMap[ab] = abIdx;
    }
    else
    {
      abIdx = vertIdxMap[ab];
    }
    if (vertIdxMap.find(bc) == vertIdxMap.end())
    {
      vertices.push_back(bc);
      bcIdx          = vertices.size() - 1;
      vertIdxMap[bc] = bcIdx;
    }
    else
    {
      bcIdx = vertIdxMap[bc];
    }
    if (vertIdxMap.find(ca) == vertIdxMap.end())
    {
      vertices.push_back(ca);
      caIdx          = vertices.size() - 1;
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

std::vector<uint> Planet::_detectWrappedUVCoords(std::vector<uint>&   indices,
                                                 std::vector<Vertex>& vertices)
{
  std::vector<uint> _ind;
  uint              nrOfIndices = indices.size();

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
      _ind.push_back(i);
  }

  return _ind;
}

void Planet::_fixWrappedUVCoords(std::vector<uint>&   wrapped,
                                 std::vector<uint>&   indices,
                                 std::vector<Vertex>& vertices)
{
  uint                           verticeIndex = vertices.size() - 1;
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
  uint vertexIdx = vertices.size() - 1;
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

int correctIdx(uint max, int i)
{
  return i % max;
}

float Planet::_sampleHeight(TextureLoader::Image* img, int x, int y, int steps)
{
  uint w           = img->width;
  uint h           = img->height;
  x                = correctIdx(w, x);
  y                = correctIdx(h, y);
  DM::Vec2i dir[8] = {DM::Vec2i(-1, -1),
                      DM::Vec2i(0, -1),
                      DM::Vec2i(1, -1),
                      DM::Vec2i(-1, 0),
                      DM::Vec2i(1, 0),
                      DM::Vec2i(-1, 1),
                      DM::Vec2i(0, 1),
                      DM::Vec2i(1, 1)};

  float height = ((float)img->pixels[((uint)x * 4u) + (uint)y * w]) / 255.0f;

  for (uint i = 0; i < 8; i++)
  {
    DM::Vec2i currIdx(x, y);
    DM::Vec2i currDir = dir[i];
    for (uint j = 0; j < steps; j++)
    {
      DM::Vec2i idx = currIdx + currDir;
      idx.x         = correctIdx(w, idx.x);
      idx.y         = correctIdx(h, idx.y);
      float lh      = ((float)img->pixels[((uint)idx.x * 4u) + (uint)idx.y * w]) / 255.0f;
      height += lh;
    }
  }

  return height / (8.0f * (float)steps);
}
