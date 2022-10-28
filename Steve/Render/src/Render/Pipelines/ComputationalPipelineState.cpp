#include "pch.h"
#include "Render/Pipelines/ComputationalPipelineState.h"
#include <d3dcompiler.h>

using namespace Render;

ComputationalPipelineState::ComputationalPipelineState()
    : D3D12_COMPUTE_PIPELINE_STATE_DESC {}
{
  _initDefaultValues();
}

ComputationalPipelineState::~ComputationalPipelineState() { }

void ComputationalPipelineState::SetComputeShader(const std::string& computeShader)
{
  auto         shaderLocation = String::ToWString(computeShader);
  ID3DBlob*    errorBlob_p = nullptr;
#ifdef _DEBUG
  UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
  UINT compileFlags = 0;
#endif // DEBUG

  HR_ASSERT(D3DCompileFromFile(shaderLocation.c_str(),
                               nullptr,
                               D3D_COMPILE_STANDARD_FILE_INCLUDE,
                               "main",
                               "cs_5_0",
                               compileFlags,
                               0,
                               &myComputeShader_p,
                               &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  CS.BytecodeLength  = myComputeShader_p->GetBufferSize();
  CS.pShaderBytecode = myComputeShader_p->GetBufferPointer();
}

void ComputationalPipelineState::CreatePipelineState(const std::string& name)
{
  pRootSignature = Rootsignature::GetComputeRootsignature();

  HR_ASSERT(
      Device::GetDevice()->CreateComputePipelineState(this, IID_PPV_ARGS(&myPipelineState_p)));
  myPipelineState_p->SetName(String::ToWString(name).c_str());
}

ID3D12PipelineState* ComputationalPipelineState::GetPipelineState() const
{
  return myPipelineState_p;
}

void ComputationalPipelineState::_initDefaultValues() { }
