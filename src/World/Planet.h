#pragma once
#include "../entity/Drawable.h"
#include "../renderer/mesh/Mesh.h"
#include "../renderer/buffers/TextureBuffer.h"
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

  struct GenerationType
  {
    struct GenOptions
    {
      double frequency;
      double exponent;
      double fudgeFactor;
      uint   iterations;
    };

    GenerationType()
    {
      height.frequency   = 1.0f;
      height.iterations  = 3;
      height.exponent    = 1.0f;
      height.fudgeFactor = 1.0f;

      moisture.frequency   = 1.0f;
      moisture.iterations  = 3;
      moisture.exponent    = 0.60f;
      moisture.fudgeFactor = 1.2f;
      waterLevel           = 0.1;
      texWidth             = 512;
      texHeight            = 512;
      seed                 = 1337;
    }
    GenOptions height;
    GenOptions moisture;
    double     waterLevel;
    uint       texWidth;
    uint       texHeight;
    uint       seed;
  };

public:
  Planet();
  ~Planet();

  void
  Create(float size, uint div, float uvTiles = 1.0f, GenerationType genType = GenerationType());
  void CreateOffsetGpu(float          size,
                       uint           div,
                       float          uvTiles = 1.0f,
                       GenerationType genType = GenerationType());
  void UpdateGeneration(GenerationType genType = GenerationType());

  const Mesh& GetMesh() const;
  void        Bind() override;
  void        BindForOffsetGpu();

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
  void _generateHeightMapAndTexture(TextureLoader::Image*      heightMap,
                                    TextureLoader::Image*      diffuse,
                                    GenerationType             genType);

  void _getBiomAndColor(double                       elevation,
                        double                       moisture,
                        TextureLoader::Image::Pixel& color,
                        Planet::Biom&                biom,
                        GenerationType               genType);

  TextureLoader::Image::Pixel _getColor(Planet::Biom biom);

private:
  Mesh           myMesh;
  TextureBuffer  myTextureBuffer;
  ConstantBuffer myWaterLevel;
  TextureBuffer  myHeightMapBuffer;
};