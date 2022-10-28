#pragma once

#include <Common/DMath.h>
#include <Common/Transform.h>
#include "Render/Resource/ConstantBuffer.h"

namespace Render
{
  class Mesh;
  class GraphicsPipelineState;
  class ResourceDescriptorHeap;

  class Drawable : public Transform
  {
  public:
    Drawable();
    virtual ~Drawable();

    Mesh*                   GetMesh() const;
    GraphicsPipelineState*  GetGraphicalPipelineState() const;
    ResourceDescriptorHeap* GetResourceDescriptorHeap() const;
    ConstantBuffer*         GetConstantBuffer() const;

  private:
    Mesh*                   myMesh_p             = nullptr;
    GraphicsPipelineState*  myGraphicsState_p    = nullptr;
    ResourceDescriptorHeap* myResourceDescHeap_p = nullptr;
    ConstantBuffer          myConstantBuffer;
  };
} // namespace Render