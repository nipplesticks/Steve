#pragma once
#define NOMINMAX
#include "../renderer/buffers/ConstantBuffer.h"
#include "../renderer/d3d12/ResourceDescriptorHeap.h"
#include "Transform.h"
#include <unordered_map>
#include <vector>

class Mesh;
class Texture2D;
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
      if (nrOfElements >= queue.size())
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

  void            SetMesh(Mesh* mesh_p);
  void            SetTexture(Texture2D* textureBuffer_p);
  void            SetGraphicsPipelineState(GraphicsPipelineState* state_p);
  virtual void    BindWithDefaultResourceDescHeap();
  void            SetCustomResourceDescriptorHeap(ResourceDescriptorHeap* customHeap_p);
  void            UpdateWorldMatrixConstantBuffer();
  ConstantBuffer* GetWorldMatrixConstantBuffer() const;

  virtual void Draw();

  Mesh*                   GetMesh() const;
  Texture2D*              GetTextureBuffer() const;
  GraphicsPipelineState*  GetGraphicsPipelineState() const;
  ResourceDescriptorHeap* GetResourceDescHeap() const;

  static std::unordered_map<GraphicsPipelineState*, DrawQueue> DRAW_QUEUE;

protected:
  static void PushDrawableToDrawQueue(Drawable* drawable);

protected:
  bool                    myIsBinded           = false;
  Mesh*                   myMesh_p             = nullptr;
  Texture2D*              myTextureBuffer_p    = nullptr;
  GraphicsPipelineState*  myGraphicsState_p    = nullptr;
  ResourceDescriptorHeap* myResourceDescHeap_p = nullptr;
  ConstantBuffer          myWorldConstantBuffer;
};