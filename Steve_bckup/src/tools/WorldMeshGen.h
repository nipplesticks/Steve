#pragma once
#include "../src/renderer/mesh/Mesh.h"

class WorldMeshGen
{
private:
  WorldMeshGen();
  ~WorldMeshGen() = default;

public:
  static WorldMeshGen* GetInstance();

public:
  void Create(const std::string& outPath, uint subdivisions);
  void Load(const std::string&                inPath,
            std::vector<std::vector<Vertex>>& vertices,
            std::vector<std::vector<uint>>&   indices,
            std::vector<DM::Vec3f>&           sideNormals);

private:
  struct Triangle
  {
    Triangle(uint a = 0u, uint b = 0u, uint c = 0u)
    {
      A = a;
      B = b;
      C = c;
    }
    uint& operator[](uint idx)
    {
      return *(&A + idx);
    }
    uint A, B, C;
  };
  struct DetailLevelDuringCreation
  {
    std::vector<DM::Vec3f> points;
    std::vector<Triangle>  triangles;
    uint                   detailLevel;
  };
  struct IcosahedronSideDuringCreation
  {
    std::vector<DetailLevelDuringCreation> detailLevels;
  };
  struct DetailLevel
  {
    std::vector<Vertex_Basic> vertices;
    std::vector<uint>         indices;
  };
  struct IcosahedronSide
  {
    std::vector<DetailLevel> detailLevel;
  };
  struct Icosahedron
  {
    IcosahedronSide sides[ICOSAHEDRON_SIDES];
  };

private:
  void
  _CreateIcosahedronAndSubdivide(IcosahedronSideDuringCreation icosahedronSide[ICOSAHEDRON_SIDES],
                                 uint                          subdivitions);
  void _Subdivide(DetailLevelDuringCreation& detail);

  void _CreateVertices(Icosahedron&                  icosahedron,
                       IcosahedronSideDuringCreation sides[ICOSAHEDRON_SIDES]);

  void _FixWrappedUVCoords(std::vector<uint>& indices, std::vector<Vertex_Basic>& vertices);

  void _FixSharedPoleVertices(std::vector<uint>& indices, std::vector<Vertex_Basic>& vertices);

  DM::Vec3f myTopLevelNormals[ICOSAHEDRON_SIDES];
};