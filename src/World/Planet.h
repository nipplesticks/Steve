#pragma once
#include "../entity/Drawable.h"
#include "../renderer/Mesh.h"
#include "../utility/DMath.h"
#include "../renderer/TextureBuffer.h"

struct TextureLoader::Image;
class TextureBuffer;


class Planet : public Drawable
{
public:
  Planet();
  ~Planet();

  void        Create(float size, uint div, float uvTiles = 1.0f);
  const Mesh& GetMesh() const;

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

  void _createIcosahedron(std::vector<uint>& indices, std::vector<DM::Vec3f>& vertices);
  void _subdivideIcosahedron(std::vector<Triangle>& triangles, std::vector<DM::Vec3f>& vertices);
  std::vector<uint> _detectWrappedUVCoords(std::vector<uint>&   indices,
                                           std::vector<Vertex>& vertices);
  void              _fixWrappedUVCoords(std::vector<uint>&   wrapped,
                                        std::vector<uint>&   indices,
                                        std::vector<Vertex>& vertices);
  void _fixSharedPoleVertices(std::vector<uint>& indices, std::vector<Vertex>& vertices);

  float _sampleHeight(TextureLoader::Image* img, int x, int y, int steps);

private:
  Mesh myMesh;
  TextureBuffer myTextureBuffer;
};