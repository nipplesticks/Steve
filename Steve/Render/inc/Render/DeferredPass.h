#pragma once

#include "Resource/VertexBuffer.h"
#include "Resource/IndexBuffer.h"
#include "Pipelines/GraphicalPipelineState.h"
#include "DescriptorHeap/ResourceDescriptorHeap.h"

namespace Render
{
  class DeferredPass
  {
  private:
    DeferredPass()  = default;
    ~DeferredPass() = default;
    static VertexBuffer                        gVertexBuffer;
    static IndexBuffer                         gIndexBuffer;
    static GraphicalPipelineState              gGraphicalPipelineState;
    static std::vector<ResourceDescriptorHeap> gResourceDescHeap;

  public:
    static void Init();
    //Call this function for each Swap buffers
    static void                    AppendRenderTargets(const std::vector<Resource*>& renderTargets);
    static VertexBuffer*           GetVertexBuffer();
    static IndexBuffer*            GetIndexBuffer();
    static GraphicalPipelineState* GetPipelineState();
    static ResourceDescriptorHeap* GetResourceDescHeap(uint16 swapBufferIdx);
  };

} // namespace Render
