#include "WorldMeshGen.h"
#include "../src/renderer/d3d12/myRenderer.h"
#include "../src/renderer/textureLoader/TextureLoader.h"
#include "../src/utility/Timer.h"
#include "../src/utility/UtilityFuncs.h"
#include <fstream>
#include <unordered_map>

WorldMeshGen::WorldMeshGen() { }

WorldMeshGen* WorldMeshGen::GetInstance()
{
  static WorldMeshGen WorldMeshGen;
  return &WorldMeshGen;
}

void WorldMeshGen::Create(const std::string& outPath, uint subdivisions)
{
  subdivisions = std::max(subdivisions, 1u);

  std::ofstream outFile;
  outFile.open(outPath, std::ios::binary);
  ASSERT(outFile);
  Icosahedron icosahedron;
  {
    IcosahedronSideDuringCreation icosahedronSide[ICOSAHEDRON_SIDES];
    _CreateIcosahedronAndSubdivide(icosahedronSide, subdivisions);
    _CreateVertices(icosahedron, icosahedronSide);
  }
  for (uint i = 0; i < ICOSAHEDRON_SIDES; i++)
  {
    WorldMeshGen::DetailLevel* target_p = &icosahedron.sides[i].detailLevel[0];
    size_t                     numVerts = target_p->vertices.size();
    size_t                     numInd   = target_p->indices.size();
    outFile.write(static_cast<char*>((void*)&numVerts), sizeof(size_t));
    outFile.write(static_cast<char*>((void*)&numInd), sizeof(size_t));
    outFile.write(static_cast<char*>((void*)&myTopLevelNormals[i]), sizeof(DM::Vec3f));
    outFile.write(static_cast<char*>((void*)target_p->vertices.data()),
                  sizeof(Vertex_Basic) * numVerts);
    outFile.write(static_cast<char*>((void*)target_p->indices.data()), sizeof(uint) * numInd);
  }
  outFile.close();
}

void WorldMeshGen::Load(const std::string&                inPath,
                        std::vector<std::vector<Vertex>>& vertices,
                        std::vector<std::vector<uint>>&   indices,
                        DM::Vec3f&                        normal)
{
  vertices.clear();
  indices.clear();
  std::ifstream inFile;
  inFile.open(inPath, std::ios::binary);
  ASSERT(inFile);
  size_t numVerts = 0;
  size_t numInd   = 0;

  std::vector<Vertex_Basic> verts;
  for (uint i = 0; i < ICOSAHEDRON_SIDES; i++)
  {
    inFile.read(static_cast<char*>((void*)&numVerts), sizeof(size_t));
    inFile.read(static_cast<char*>((void*)&numInd), sizeof(size_t));
    inFile.read(static_cast<char*>((void*)&normal), sizeof(DM::Vec3f));
    verts.resize(numVerts);
    indices.resize(numInd);
    inFile.read(static_cast<char*>((void*)verts.data()), sizeof(Vertex_Basic) * numVerts);
    inFile.read(static_cast<char*>((void*)indices[i].data()), sizeof(uint) * numInd);
    vertices[i].resize(numVerts);
    for (uint j = 0; j < numVerts; j++)
    {
      vertices[i][j].vertexBasic.normal   = verts[j].normal;
      vertices[i][j].vertexBasic.position = verts[j].position;
      vertices[i][j].vertexBasic.uv       = verts[j].uv;
    }
  }

  inFile.close();
}

void WorldMeshGen::_CreateIcosahedronAndSubdivide(
    IcosahedronSideDuringCreation icosahedronSide[ICOSAHEDRON_SIDES], uint subdivisions)
{
  float     phi             = (1.0f + sqrt(5.0f)) * 0.5f;
  float     a               = 1.0f;
  float     b               = 1.0f / phi;
  DM::Vec3f icosahedron[12] = {DM::Vec3f(0.0f, b, -a), // 0
                               DM::Vec3f(b, a, 0.0f), // 1
                               DM::Vec3f(-b, a, 0.0f), // 2
                               DM::Vec3f(0.0f, b, a), // 3
                               DM::Vec3f(0.0f, -b, a), // 4
                               DM::Vec3f(-a, 0.0f, b), // 5
                               DM::Vec3f(0.0f, -b, -a), // 6
                               DM::Vec3f(a, 0.0f, -b), // 7
                               DM::Vec3f(a, 0.0f, b), // 8
                               DM::Vec3f(-a, 0.0f, -b), // 9
                               DM::Vec3f(b, -a, 0.0f), // 10
                               DM::Vec3f(-b, -a, 0.0f)}; // 11

  uint indices[] = {1, 2,  0,  2, 1, 3, 4, 5, 3, 8,  4, 3,  6, 7, 0,  9,  6, 0, 10, 11,
                    4, 11, 10, 6, 5, 9, 2, 9, 5, 11, 7, 8,  1, 8, 7,  10, 5, 2, 3,  1,
                    8, 3,  2,  9, 0, 7, 1, 0, 9, 11, 6, 10, 7, 6, 11, 5,  4, 8, 10, 4};
  uint it        = 0;

  Timer totalTimer;
  totalTimer.Start();
  double itTime = 0.0;
  for (uint side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    icosahedronSide[side].detailLevels.resize(1);
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
      std::cout << "\r[Side: " << side << "/" << ICOSAHEDRON_SIDES << "] "
                << "[It: " << subDiv << "/" << subdivisions << "] "
                << "[Total time: " << totalTimer.Peek() << "s] "
                << "[Last It Time: " << itTime << "s] "
                << "[it Est: " << std::pow(itTime, 2) << "s]              ";
      Timer t;
      t.Start();
      _Subdivide(icosahedronSide[side].detailLevels[0]);
      itTime = t.Stop();
    }
  }
}

void WorldMeshGen::_Subdivide(DetailLevelDuringCreation& detail)
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

void WorldMeshGen::_CreateVertices(Icosahedron&                  icosahedron,
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
        icosahedron.sides[side].detailLevel[level].vertices[v].position = position;
        icosahedron.sides[side].detailLevel[level].vertices[v].normal   = position;
        icosahedron.sides[side].detailLevel[level].vertices[v].normal.w = 0.0f;
        icosahedron.sides[side].detailLevel[level].vertices[v].uv.x =
            0.5f + (std::atan2(position.z, position.x) / (2.0f * PI));
        icosahedron.sides[side].detailLevel[level].vertices[v].uv.y =
            0.5f - (std::asin(position.y) / PI);
      }
      uint idxCounter = 0;
      for (uint triIdx = 0; triIdx < numTris; triIdx++)
      {
        Triangle triangle = sides[side].detailLevels[level].triangles[triIdx];
        icosahedron.sides[side].detailLevel[level].indices[idxCounter++] = triangle.A;
        icosahedron.sides[side].detailLevel[level].indices[idxCounter++] = triangle.B;
        icosahedron.sides[side].detailLevel[level].indices[idxCounter++] = triangle.C;
        if (level == 0)
        {
          DM::Vec3f v0  = icosahedron.sides[side].detailLevel[level].vertices[triangle.A].position;
          DM::Vec3f v1  = icosahedron.sides[side].detailLevel[level].vertices[triangle.B].position;
          DM::Vec3f v2  = icosahedron.sides[side].detailLevel[level].vertices[triangle.C].position;
          DM::Vec2f uv0 = icosahedron.sides[side].detailLevel[level].vertices[triangle.A].uv;
          DM::Vec2f uv1 = icosahedron.sides[side].detailLevel[level].vertices[triangle.B].uv;
          DM::Vec2f uv2 = icosahedron.sides[side].detailLevel[level].vertices[triangle.C].uv;

          DM::Vec3f e0 = v1 - v0;
          DM::Vec3f e1 = v2 - v0;

          myTopLevelNormals[side] = e1.Cross(e0).Normalize();
        }
      }
      _FixWrappedUVCoords(icosahedron.sides[side].detailLevel[level].indices,
                          icosahedron.sides[side].detailLevel[level].vertices);
      _FixSharedPoleVertices(icosahedron.sides[side].detailLevel[level].indices,
                             icosahedron.sides[side].detailLevel[level].vertices);
    }
  }
}

void WorldMeshGen::_FixWrappedUVCoords(std::vector<uint>&         indices,
                                       std::vector<Vertex_Basic>& vertices)
{
  uint                           numIndices  = (uint)indices.size();
  uint                           vertexIndex = (uint)vertices.size() - 1;
  std::unordered_map<uint, uint> visited;
  Vertex_Basic                   v = {};

  for (uint i = 0; i < numIndices; i += 3)
  {
    uint a = indices[i + 0];
    uint b = indices[i + 1];
    uint c = indices[i + 2];

    DM::Vec3f uvA(vertices[a].uv);
    DM::Vec3f uvB(vertices[b].uv);
    DM::Vec3f uvC(vertices[c].uv);
    DM::Vec3f n = (uvC - uvA).Cross(uvB - uvA);
    if (n.z < 0.0f)
    {
      Vertex_Basic A = vertices[a];
      Vertex_Basic B = vertices[b];
      Vertex_Basic C = vertices[c];
      if (A.uv.x < 0.25f)
      {
        uint tempA = a;
        if (visited.find(a) == visited.end())
        {
          A.uv.x += 1.0f;
          v = A;
          vertices.push_back(v);
          vertexIndex++;
          visited.insert(std::make_pair(a, vertexIndex));
          tempA = vertexIndex;
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
          v = B;
          vertices.push_back(v);
          vertexIndex++;
          visited.insert(std::make_pair(b, vertexIndex));
          tempB = vertexIndex;
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
          v = C;
          vertices.push_back(v);
          vertexIndex++;
          visited.insert(std::make_pair(c, vertexIndex));
          tempC = vertexIndex;
        }
        else
        {
          tempC = visited[c];
        }
        c = tempC;
      }
      indices[i + 0] = a;
      indices[i + 1] = b;
      indices[i + 2] = c;
    }
  }
}

void WorldMeshGen::_FixSharedPoleVertices(std::vector<uint>&         indices,
                                          std::vector<Vertex_Basic>& vertices)
{
  uint northIdx = UINT_MAX;
  for (uint i = 0; i < vertices.size(); i++)
  {
    if (northIdx != UINT_MAX /* && southIdx != UINT_MAX*/)
      break;

    if (vertices[i].position.y == 1.0f)
      northIdx = i;
  }

  for (uint i = 0; i < indices.size(); i += 3)
  {
    if (indices[i] == northIdx)
    {
      uint         startIdx = i;
      Vertex_Basic A        = vertices[indices[startIdx + 0]];
      Vertex_Basic B        = vertices[indices[startIdx + 1]];
      Vertex_Basic C        = vertices[indices[startIdx + 2]];
      Vertex_Basic newNorth = vertices[northIdx];
      newNorth.uv.y         = (B.uv.y + C.uv.y) * 0.5f;
      if (A.position.y == 1.0f)
        vertices[indices[startIdx + 0]].uv = newNorth.uv;
      else if (B.position.y == 1.0f)
        vertices[indices[startIdx + 1]].uv = newNorth.uv;
      else if (C.position.y == 1.0f)
        vertices[indices[startIdx + 2]].uv = newNorth.uv;
    }
  }
}
