#pragma once
#include "../renderer/Mesh.h"
#include "../utility/DMath.h"

class Planet3
{
public:
  Planet3();
  ~Planet3();

  void        Create(float size, uint div, float uvTiles = 1.0f);
  const Mesh& GetMesh() const;

private:
private:
  struct Triangle
  {
    Triangle(uint a = 0u, uint b = 0u, uint c = 0u)
    {
      A = a;
      B = b;
      C = c;
    }
    uint A, B, C;
  };
  void _createIcosahedron(std::vector<std::vector<Triangle>>&  triangles,
                          std::vector<std::vector<DM::Vec3f>>& vertices);
  void _subdevideIcosahedron(std::vector<Triangle>& triangles, std::vector<DM::Vec3f>& vertices);
  /*void _optimizeMesh(std::vector<std::vector<Triangle>>&  triangles,
                     std::vector<std::vector<DM::Vec3f>>& vertices);*/
  void _uvMap(std::vector<std::vector<Triangle>>&  triangles,
              std::vector<std::vector<DM::Vec3f>>& vertices);

private:
  Mesh myMesh;
};