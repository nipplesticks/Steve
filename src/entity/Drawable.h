#pragma once
#define NOMINMAX
#include "../renderer/ConstantBuffer.h"
#include "../renderer/ResourceDescriptorHeap.h"
#include "Transform.h"
#include <unordered_map>
#include <vector>

class Mesh;
class TextureBuffer;
class GraphicsPipelineState;

class Drawable : public Transform
{
public:
  struct DrawQueue
  {
    DrawQueue()
    {
      queue.resize(5);
      nrOfElements = 0u;
    }
    void Push(Drawable* drawable)
    {
      if (nrOfElements > queue.size())
      {
        queue.resize(queue.size() * 2);
      }
      queue[nrOfElements++] = drawable;
    }
    void Clear()
    {
      nrOfElements = 0;
    }
    std::vector<Drawable*> queue;
    uint                   nrOfElements;
  };

public:
  Drawable(const DM::Vec3f& position = DM::Vec3f());
  virtual ~Drawable() = default;

  void SetMesh(Mesh* mesh_p);
  void SetTexture(TextureBuffer* textureBuffer_p);
  void SetGraphicsPipelineState(GraphicsPipelineState* state_p);
  void Bind();
  void UpdateConstantBuffer();

  void Draw();

  Mesh*                         GetMesh() const;
  TextureBuffer*                GetTextureBuffer() const;
  GraphicsPipelineState*        GetGraphicsPipelineState() const;
  const ResourceDescriptorHeap& GetResourceDescHeap() const;

  static std::unordered_map<GraphicsPipelineState*, DrawQueue> DRAW_QUEUE;

private:
  static void PushDrawableToDrawQueue(Drawable* drawable);

private:
  bool                   myIsBinded        = false;
  Mesh*                  myMesh_p          = nullptr;
  TextureBuffer*         myTextureBuffer_p = nullptr;
  GraphicsPipelineState* myGraphicsState_p = nullptr;
  ConstantBuffer         myWorldConstantBuffer;
  ResourceDescriptorHeap myResourceDescHeap;
};