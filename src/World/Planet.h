#pragma once
#include "../entity/Drawable.h"
#include "../renderer/Mesh.h"
#include "../renderer/TextureBuffer.h"
#include "../utility/DMath.h"

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

  void _createIcosahedronAndSubdivide(std::vector<uint>&      indices,
                                      std::vector<DM::Vec3f>& vertices,
                                      uint                    divitions);
  void _createIcosahedron(std::vector<uint>& indices, std::vector<DM::Vec3f>& vertices);
  void _subdivideIcosahedron(std::vector<Triangle>& triangles, std::vector<DM::Vec3f>& vertices);
  void _createVertices(std::vector<Vertex>& verts, const std::vector<DM::Vec3f>& points);
  void _detectWrappedUVCoords(std::vector<uint>&   indices,
                              std::vector<Vertex>& vertices,
                              std::vector<uint>&   wrappedIndices);
  void _fixWrappedUVCoords(std::vector<uint>&   wrapped,
                           std::vector<uint>&   indices,
                           std::vector<Vertex>& vertices);
  void _fixSharedPoleVertices(std::vector<uint>& indices, std::vector<Vertex>& vertices);
  void _scaleUVs(std::vector<Vertex>& vertices, float uvTiles);
  void _offsetBasedOnHeightMap(TextureLoader::Image* heightMap,
                               std::vector<uint>&    indices,
                               std::vector<Vertex>&  verts);
  void _generateHeightMapAndTexture(TextureLoader::Image* heightMap, TextureLoader::Image* diffuse, uint width, uint height, const std::vector<Vertex>& vertices);

private:
  Mesh          myMesh;
  TextureBuffer myTextureBuffer;
};