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

class Map : public Transform
{
public:
  Map();
  ~Map() = default;

  void SetRotationSpeed(float rotationSpeed);
  
  float GetHightLevelAt(const DM::Vec3f& position);

  void Create();
  void Create(const std::vector<std::vector<Vertex>>& vertices,
              const std::vector<std::vector<uint>>&   indices,
              const std::vector<DM::Vec3f>&           sideNormals,
              const DM::Vec2u&                  textureResulotion = DM::Vec2u(4096, 4096));
  void Update(float dt, Camera* camera_p = nullptr);
  void GenerateMap(const Noise& heightMap, const Noise& diffuseMap);
  void Draw();

private:
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
  void _SetupGraphicPipelineState();

  void _SetupComputePipelineState();

  void _SetupTextures(const DM::Vec2u& textureResulotion);

private:
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

  Mesh                   myMeshes[ICOSAHEDRON_SIDES];
  Drawable               mySides[ICOSAHEDRON_SIDES];
  DM::Vec3f              myTopLevelNormals[ICOSAHEDRON_SIDES];
  ConstantBuffer         myWorldMatrix;
  ResourceDescriptorHeap myRenderDescHeap;

  StructuredBuffer myLights;

  DM::Vec3f myLocalCameraDirection;
  DM::Vec2f myTextureSize;
};