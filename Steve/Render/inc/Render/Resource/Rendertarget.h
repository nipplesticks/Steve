#pragma once
#include "Resource.h"
#include "../Pipelines/GraphicalPipelineState.h"

namespace Render
{
  class RenderTarget : public Resource
  {
  public:
    void             Create(const std::string& name,
                            uint32             width,
                            uint32             height,
                            RenderTargetType   type,
                            DXGI_FORMAT        format = DXGI_FORMAT_R8G8B8A8_UNORM);
    RenderTargetType GetRenderTargetType() const;

  private:
    RenderTargetType myRenderTargetType = RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES;
  };
} // namespace Render