#include "ComputationalPipeline.h"
#include "../../utility/RenderUtility.h"
#include "../../utility/UtilityFuncs.h"
#include "myRenderer.h"
#include <d3dcompiler.h>

ComputationalPipeline::ComputationalPipeline()
    : D3D12_COMPUTE_PIPELINE_STATE_DESC {}
{
  _initDefaultValues();
}

ComputationalPipeline::~ComputationalPipeline() { }

HRESULT ComputationalPipeline::SetComputeShader(const std::string& computeShader)
{
  std::cout << "shader: " << computeShader << std::endl;
  std::wstring shaderLocation(computeShader.begin(), computeShader.end());
  ID3DBlob*    errorBlob_p  = nullptr;
  UINT         compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT      hr           = 0;

  HR_ASSERT(hr = D3DCompileFromFile(shaderLocation.c_str(),
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

  return hr;
}

HRESULT ComputationalPipeline::CreatePipelineState()
{
  HRESULT hr = 0;
  pRootSignature    = MyRenderer::GetInstance()->GetComputeRootSignature();
  CS.BytecodeLength = myComputeShader_p->GetBufferSize();
  CS.pShaderBytecode = myComputeShader_p->GetBufferPointer();
  HR_ASSERT(hr = MyRenderer::GetInstance()->GetDevice()->CreateComputePipelineState(
                this, IID_PPV_ARGS(&myPipelineState_p)));

  return hr;
}

ID3D12PipelineState* ComputationalPipeline::GetPipelineState() const
{
  return myPipelineState_p;
}

void ComputationalPipeline::_initDefaultValues()
{

}
