#pragma once
#include <d3d12.h>
#include <string>
#include "PipelineState.h"

namespace Render
{
  class ComputationalPipelineState : public PipelineState, public D3D12_COMPUTE_PIPELINE_STATE_DESC
  {
  public:
    ComputationalPipelineState();
    ~ComputationalPipelineState();

    void                 SetComputeShader(const std::string& computeShader);
    void                 CreatePipelineState(const std::string& name);
    virtual ID3D12PipelineState* GetPipelineState() const override;

  private:
    void _initDefaultValues();

    ID3DBlob*            myComputeShader_p = nullptr;
    ID3D12PipelineState* myPipelineState_p = nullptr;
  };
} // namespace Render