#pragma once
#include "../Noise/PerlinNoise.h"
#include "../entity/Drawable.h"
#include "../renderer/buffers/StructuredBuffer.h"
#include "../renderer/buffers/Texture2D.h"
#include "../renderer/camera/Camera.h"
#include "../renderer/d3d12/ComputationalPipeline.h"
#include "../renderer/d3d12/GraphicsPipelineState.h"
#include "../renderer/d3d12/ResourceDescriptorHeap.h"
#include "../renderer/mesh/Mesh.h"

#define ICOSAHEDRON_SIDES 20

class Map : public Transform
{

public:
  static float LOD_MAX_DISTANCE;

public:
  Map();
  ~Map() = default;

  void SetRotationSpeed(float rotationSpeed);
  void Create(uint             maxSubdivisions,
              float            waterTiles        = 20.0f,
              const DM::Vec2u& textureResulotion = DM::Vec2u(1024, 1024));
  void SetWaterLevel(float waterLevel);
  void Update(float dt, Camera* camera_p = nullptr);
  void GenerateMap(const Noise& heightMap, const Noise& diffuseMap);
  void Draw();

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
    std::vector<Vertex> vertices;
    std::vector<uint>   indices;
  };
  struct IcosahedronSide
  {
    std::vector<DetailLevel> detailLevel;
  };
  struct Icosahedron
  {
    IcosahedronSide sides[ICOSAHEDRON_SIDES];
  };
  struct alignas(256) GPUGenerationInput
  {
    float              frequency;
    float              exponent;
    float              fudgeFactor;
    uint               iterations;
    float              waterLevel;
    DirectX::XMFLOAT2A textureSize;
    int                permutationVector[256];
  };

private:
  void
  _CreateIcosahedronAndSubdivide(IcosahedronSideDuringCreation icosahedronSide[ICOSAHEDRON_SIDES],
                                 uint                          subdivitions);
  void _Subdivide(DetailLevelDuringCreation& detail);

  void _CreateVertices(Icosahedron&                  icosahedron,
                       IcosahedronSideDuringCreation sides[ICOSAHEDRON_SIDES]);

  void _FixWrappedUVCoords(std::vector<uint>& indices, std::vector<Vertex>& vertices);

  void _FixSharedPoleVertices(std::vector<uint>& indices, std::vector<Vertex>& vertices);

  void _SetupDetailLevels(const Icosahedron& icosahedron, uint divisions);

  void _CalcDetailLevel(Camera* camera_p);

  void _SetupGraphicPipelineState();

  void _SetupComputePipelineState();

  void _SetupTextures(const DM::Vec2u& textureResulotion);

  void _CreateWater(const Icosahedron& icosahedron, uint waterDetailLevel, float waterTiles);

private:
  struct MeshPerDetailLevel
  {
    Mesh                   sides[ICOSAHEDRON_SIDES];
  };

  Texture2D              myHeightMap;
  Texture2D              myDiffuseMap;
  Texture2D              myBumpMap;
  ComputationalPipeline  myHeightGenPipeline;
  ComputationalPipeline  myDiffuseGenPipeline;
  ComputationalPipeline  myBumpGenPipeline;
  GraphicsPipelineState  myGraphicPipeline;
  ResourceDescriptorHeap myHeightGenDescHeap;
  ResourceDescriptorHeap myDiffuseGenDescHeap;
  ResourceDescriptorHeap myBumpGenDescHeap;
  ConstantBuffer         myHeightMapGenInput;
  ConstantBuffer         myDiffuseMapGenInput;

  Texture2D              myWaterBumpMap;
  ResourceDescriptorHeap myWaterResourceDescHeap;
  GraphicsPipelineState  myWaterGraphicPipeline;
  Mesh                   myWaterMesh;
  Drawable               myWaterDrawable;
  StructuredBuffer       myWaterTangents;
  ConstantBuffer         myWaterOffsetBuffer;
  float                  myWaterOffset = 0.0f;
  float                  myWaterLevel = 0.0f;

  Drawable                        mySides[ICOSAHEDRON_SIDES];
  DM::Vec3f                       myTopLevelNormals[ICOSAHEDRON_SIDES];
  std::vector<MeshPerDetailLevel> myDetailLevels;
  ConstantBuffer                  myWorldMatrix;
  ResourceDescriptorHeap          myRenderDescHeap;

  StructuredBuffer myLights;

  uint      myCurrentDetailLevel = 0;
  uint      myTotalDetailLevels  = 0;
  DM::Vec3f myLocalCameraDirection;
  DM::Vec2f myTextureSize;


  float myRotationSpeed = 0.1f;
};