#pragma once
#include <d3d12.h>
#include <vector>
#include <string>

class ComputationalPipeline : public D3D12_COMPUTE_PIPELINE_STATE_DESC
{
public:
  ComputationalPipeline();
  ~ComputationalPipeline();

  HRESULT SetComputeShader(const std::string& computeShader);
  HRESULT CreatePipelineState();
  ID3D12PipelineState* GetPipelineState() const;

private:
  void _initDefaultValues();

private:
  ID3DBlob* myComputeShader_p = nullptr;
  ID3D12PipelineState*   myPipelineState_p = nullptr;
};