#pragma once
#include "../entity/Drawable.h"
#include "../renderer/buffers/TextureBuffer.h"
#include "../renderer/mesh/Mesh.h"
#include "../utility/DMath.h"

struct TextureLoader::Image;
class TextureBuffer;

class Planet : public Drawable
{
public:
  enum Biom
  {
    Ocean = 0,
    Beach,
    Scorched,
    Bare,
    Tundra,
    Snow,
    TemperateDesert,
    Shrubland,
    Taiga,
    GrassLand,
    TemperateDeciduousForest,
    TemperateRainForest,
    SubtropicalDesert,
    TropicalSeasonalFoest,
    TropicalRainForest
  };

  struct alignas(16) GenerationType
  {
    struct GenOptions
    {
      float frequency;
      float exponent;
      float fudgeFactor;
      int   iterations;
    };

    GenerationType()
    {
      height.frequency   = 1.0f;
      height.iterations  = 1;
      height.exponent    = 1.0f;
      height.fudgeFactor = 1.0f;

      moisture.frequency   = 1.0f;
      moisture.iterations  = 1;
      moisture.exponent    = 1.0f;
      moisture.fudgeFactor = 1.0f;
      waterLevel           = 0.1f;
      texWidth             = 512;
      texHeight            = 512;
      seed                 = 1337;
    }
    GenOptions height;
    GenOptions moisture;
    float      waterLevel;
    int        texWidth;
    int        texHeight;
    int        seed;
  };

public:
  Planet();
  ~Planet();

  void
  Create(float size, uint div, float uvTiles = 1.0f, GenerationType genType = GenerationType());
  void UpdateGeneration(GenerationType genType = GenerationType());
  void SetWaterLevel(float wl);

  const Mesh&     GetMesh() const;
  void            Bind() override;
  void            BindForOffsetGpu();
  TextureBuffer*  GetHeightMap();
  TextureBuffer*  GetDiffuse();
  TextureBuffer*  GetBump();
  ConstantBuffer* GetWaterLevelCb();

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
  void _generateHeightMapAndTexture(TextureLoader::Image* heightMap,
                                    TextureLoader::Image* diffuse,
                                    GenerationType        genType);

  void _getBiomAndColor(double                       elevation,
                        double                       moisture,
                        TextureLoader::Image::Pixel& color,
                        Planet::Biom&                biom,
                        GenerationType               genType);

  void _calcTangent(const std::vector<uint>& indices, std::vector<Vertex>& verts);

  TextureLoader::Image::Pixel _getColor(Planet::Biom biom);

private:
  Mesh           myMesh;
  Mesh           myWaterMesh;
  TextureBuffer  myTextureBuffer;
  ConstantBuffer myWaterLevel;
  TextureBuffer  myHeightMapBuffer;
  TextureBuffer  myBumpMapBuffer;
};