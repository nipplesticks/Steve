#include "Generation.h"
#include <unordered_map>

DM::Vec3f myTopLevelNormals[ICOSAHEDRON_SIDES];

static inline void _Subdivide(DetailLevelDuringCreation& detail)
{
  uint32 numTri    = (uint32)detail.triangles.size();
  uint32 lastTri   = numTri;
  uint32 numTriNew = numTri;
  detail.triangles.resize(numTri + numTri * 3u);
  std::unordered_map<DM::Vec3f, uint32> pointTriMap;

  for (uint32 triIdx = 0; triIdx < numTri; triIdx++)
  {
    DM::Vec3f a = detail.points[detail.triangles[triIdx].A];
    DM::Vec3f b = detail.points[detail.triangles[triIdx].B];
    DM::Vec3f c = detail.points[detail.triangles[triIdx].C];

    DM::Vec3f ab = a + (b - a) * 0.5f;
    DM::Vec3f bc = b + (c - b) * 0.5f;
    DM::Vec3f ca = c + (a - c) * 0.5f;

    uint32 abIdx = 0;
    uint32 bcIdx = 0;
    uint32 caIdx = 0;

    if (pointTriMap.find(ab) == pointTriMap.end())
    {
      detail.points.push_back(ab);
      abIdx           = (uint32)detail.points.size() - 1;
      pointTriMap[ab] = abIdx;
    }
    else
    {
      abIdx = pointTriMap[ab];
    }
    if (pointTriMap.find(bc) == pointTriMap.end())
    {
      detail.points.push_back(bc);
      bcIdx           = (uint32)detail.points.size() - 1;
      pointTriMap[bc] = bcIdx;
    }
    else
    {
      bcIdx = pointTriMap[bc];
    }
    if (pointTriMap.find(ca) == pointTriMap.end())
    {
      detail.points.push_back(ca);
      caIdx           = (uint32)detail.points.size() - 1;
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

static inline void
_CreateIcosahedronAndSubdivide(IcosahedronSide icosahedronSide[ICOSAHEDRON_SIDES],
                               uint32          subdivisions)
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

  uint32 indices[] = {1, 2,  0,  2, 1, 3, 4, 5, 3, 8,  4, 3,  6, 7, 0,  9,  6, 0, 10, 11,
                      4, 11, 10, 6, 5, 9, 2, 9, 5, 11, 7, 8,  1, 8, 7,  10, 5, 2, 3,  1,
                      8, 3,  2,  9, 0, 7, 1, 0, 9, 11, 6, 10, 7, 6, 11, 5,  4, 8, 10, 4};

  uint32 it = 0;
  for (uint32 side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    icosahedronSide[side].detailLevels.resize(subdivisions);
    icosahedronSide[side].detailLevels[0].detailLevel = 0;
    icosahedronSide[side].detailLevels[0].points.resize(3);
    icosahedronSide[side].detailLevels[0].triangles.resize(1);
    icosahedronSide[side].detailLevels[0].triangles[0] = Triangle(0, 1, 2);
    for (uint32 i = 0; i < 3; i++)
    {
      icosahedronSide[side].detailLevels[0].points[i] = icosahedron[indices[it++]];
    }

    for (uint32 subDiv = 1; subDiv < subdivisions; subDiv++)
    {
      icosahedronSide[side].detailLevels[subDiv] = icosahedronSide[side].detailLevels[subDiv - 1];
      _Subdivide(icosahedronSide[side].detailLevels[subDiv]);
    }
  }
}

static inline void FixWrappedUVCoords(std::vector<uint32>& indices, std::vector<Vertex>& vertices)
{
  uint32                             numIndices  = (uint32)indices.size();
  uint32                             vertexIndex = (uint32)vertices.size() - 1;
  std::unordered_map<uint32, uint32> visited;
  Vertex                             v = {};

  for (uint32 i = 0; i < numIndices; i += 3)
  {
    uint32 a = indices[i + 0];
    uint32 b = indices[i + 1];
    uint32 c = indices[i + 2];

    DM::Vec3f uvA(vertices[a].uv);
    DM::Vec3f uvB(vertices[b].uv);
    DM::Vec3f uvC(vertices[c].uv);
    DM::Vec3f n = (uvC - uvA).Cross(uvB - uvA);
    if (n.z < 0.0f)
    {
      Vertex A = vertices[a];
      Vertex B = vertices[b];
      Vertex C = vertices[c];
      if (A.uv.x < 0.25f)
      {
        uint32 tempA = a;
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
        uint32 tempB = b;
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
        uint32 tempC = c;
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

static inline void FixSharedPoleVertices(std::vector<uint32>& indices,
                                         std::vector<Vertex>& vertices)
{
  uint32 northIdx = UINT_MAX;
  for (uint32 i = 0; i < vertices.size(); i++)
  {
    if (northIdx != UINT_MAX /* && southIdx != UINT_MAX*/)
      break;

    if (vertices[i].position.y == 1.0f)
      northIdx = i;
  }

  for (uint32 i = 0; i < indices.size(); i += 3)
  {
    if (indices[i] == northIdx)
    {
      uint32 startIdx = i;
      Vertex A        = vertices[indices[startIdx + 0]];
      Vertex B        = vertices[indices[startIdx + 1]];
      Vertex C        = vertices[indices[startIdx + 2]];
      Vertex newNorth = vertices[northIdx];
      newNorth.uv.y   = (B.uv.y + C.uv.y) * 0.5f;
      if (A.position.y == 1.0f)
        vertices[indices[startIdx + 0]].uv = newNorth.uv;
      else if (B.position.y == 1.0f)
        vertices[indices[startIdx + 1]].uv = newNorth.uv;
      else if (C.position.y == 1.0f)
        vertices[indices[startIdx + 2]].uv = newNorth.uv;
    }
  }
}

static inline Sphere CreateSphereFromIcosahedron(IcosahedronSide sides[ICOSAHEDRON_SIDES])
{
  static const float PI = DM::PI;

  Sphere icosahedron;

  for (uint32 side = 0; side < ICOSAHEDRON_SIDES; side++)
  {
    uint32 detailLevels = (uint32)sides[side].detailLevels.size();
    icosahedron.sides[side].detailLevel.resize(detailLevels);

    for (uint32 level = 0; level < detailLevels; level++)
    {
      uint32 numVerts = (uint32)sides[side].detailLevels[level].points.size();
      uint32 numTris  = (uint32)sides[side].detailLevels[level].triangles.size();
      icosahedron.sides[side].detailLevel[level].vertices.resize(numVerts);
      icosahedron.sides[side].detailLevel[level].indices.resize(numTris * 3);
      for (uint32 v = 0; v < numVerts; v++)
      {
        DM::Vec4f position =
            sides[side].detailLevels[level].points[v].Normalize().AsXmAsXmFloat4A(1.0f);
        icosahedron.sides[side].detailLevel[level].vertices[v].position = position;
        icosahedron.sides[side].detailLevel[level].vertices[v].normal   = position;
        icosahedron.sides[side].detailLevel[level].vertices[v].normal.w = 0.0f;
        icosahedron.sides[side].detailLevel[level].vertices[v].uv.x =
            0.5f + (std::atan2(position.z, position.x) / (2.0f * PI));
        icosahedron.sides[side].detailLevel[level].vertices[v].uv.y =
            0.5f - (std::asin(position.y) / PI);
      }
      uint32 idxCounter = 0;
      for (uint32 triIdx = 0; triIdx < numTris; triIdx++)
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
      FixWrappedUVCoords(icosahedron.sides[side].detailLevel[level].indices,
                         icosahedron.sides[side].detailLevel[level].vertices);
      FixSharedPoleVertices(icosahedron.sides[side].detailLevel[level].indices,
                            icosahedron.sides[side].detailLevel[level].vertices);
    }
  }
  return icosahedron;
}

static inline void StoreWorld(const Sphere& sphere, uint32 dl, const std::string& path)
{
  std::string _p = path;
  if (!_p.empty())
  {
    if (_p[_p.size() - 1] != '/')
      _p += '/';
  }

  std::ofstream outfile;
  outfile.open(_p + "world_level_" + std::to_string(dl) + ".wrld", std::ios::binary);
  ASSERT(outfile);

  for (uint32 i = 0; i < ICOSAHEDRON_SIDES; i++)
  {
    const DetailLevel* target_p   = &sphere.sides[i].detailLevel[dl];
    size_t             numVerts   = target_p->vertices.size();
    size_t             numIndices = target_p->indices.size();
    outfile.write(static_cast<char*>((void*)&numVerts), sizeof(size_t));
    outfile.write(static_cast<char*>((void*)&numIndices), sizeof(size_t));
    outfile.write(static_cast<char*>((void*)&myTopLevelNormals[i]), sizeof(DM::Vec3f));
    outfile.write(static_cast<char*>((void*)target_p->vertices.data()), sizeof(Vertex) * numVerts);
    outfile.write(static_cast<char*>((void*)target_p->indices.data()), sizeof(uint32) * numIndices);
  }
  outfile.close();
}

void Generation::Create(const std::string&         path,
                        uint32                     qualityLevel,
                        const std::vector<uint32>& qualityLevels)
{
  qualityLevel += 1u;
  IcosahedronSide icosahedronSide[ICOSAHEDRON_SIDES];
  _CreateIcosahedronAndSubdivide(icosahedronSide, qualityLevel);
  Sphere sphere = CreateSphereFromIcosahedron(icosahedronSide);

  for (uint32 i = 0; i < qualityLevel; i++)
  {
    bool targetQualityLevel = qualityLevels.empty();
    for (uint32 ql = 0; ql < qualityLevels.size(); ql++)
    {
      if (i == qualityLevels[ql])
      {
        targetQualityLevel = true;
        break;
      }
    }
    if (targetQualityLevel)
    {
      StoreWorld(sphere, i, path);
    }
  }
}
