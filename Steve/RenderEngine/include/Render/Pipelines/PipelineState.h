#pragma once

struct ID3D12PipelineState;

namespace Render
{
  class PipelineState
  {
  public:
    virtual ID3D12PipelineState* GetPipelineState() const = 0;
  };
}