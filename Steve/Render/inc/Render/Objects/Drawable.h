#pragma once

#include <Common/DMath.h>
#include <Common/Transform.h>
#include "../Resource/ConstantBuffer.h"
#include "../DescriptorHeap/ResourceDescriptorHeap.h"
#include "../Mesh/Mesh.h"
#include "../Pipelines/GraphicalPipelineState.h"

namespace Render
{
  class Drawable : public Transform
  {
  public:
    static std::vector<Drawable*> gDrawQueue;

  public:
    Drawable();
    virtual ~Drawable();

    void SetMesh(Mesh* mesh_p);
    void SetGraphicalPipelineState(GraphicalPipelineState* graphicPipelineState_p);
    void CreateGPUData();
    void UpdateConstantbuffer();
    void Draw();

    Mesh*                   GetMesh();
    GraphicalPipelineState* GetGraphicalPipelineState();
    ResourceDescriptorHeap* GetResourceDescriptorHeap();
    ConstantBuffer*         GetConstantBuffer();

  private:
    Mesh*                   myMesh_p          = nullptr;
    GraphicalPipelineState* myGraphicsState_p = nullptr;
    ResourceDescriptorHeap  myResourceDescHeap;
    ConstantBuffer          myConstantBuffer;
  };
} // namespace Render