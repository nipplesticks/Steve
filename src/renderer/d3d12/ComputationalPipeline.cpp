#include "ComputationalPipeline.h"
#include "../../utility/RenderUtility.h"
#include "../../utility/UtilityFuncs.h"
#include "Renderer.h"
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

HRESULT ComputationalPipeline::GenerateRootSignature()
{
  struct ShaderObject
  {
    uint                      shaderRegister;
    uint                      registerSpace;
    D3D12_ROOT_PARAMETER_TYPE parameterType;
  };

  std::vector<ShaderObject> shaderObjects;
  if (myComputeShader_p)
  {
    ShaderObject            shaderObj {};
    ID3D12ShaderReflection* shaderReflection_p = nullptr;
    HR_ASSERT(D3DReflect(myComputeShader_p->GetBufferPointer(),
                         myComputeShader_p->GetBufferSize(),
                         IID_PPV_ARGS(&shaderReflection_p)));
    D3D12_SHADER_DESC shaderDesc = {};
    shaderReflection_p->GetDesc(&shaderDesc);
    for (uint i = 0; i < shaderDesc.BoundResources; i++)
    {
      D3D12_SHADER_INPUT_BIND_DESC desc {};
      shaderReflection_p->GetResourceBindingDesc(i, &desc);
      if (desc.Type == D3D_SIT_SAMPLER)
        continue;
      shaderObj.parameterType  = ConvertToParameterType(desc.Type);
      shaderObj.shaderRegister = desc.BindPoint;
      shaderObj.registerSpace  = desc.Space;
      shaderObjects.push_back(shaderObj);
    }
  }
  std::vector<D3D12_DESCRIPTOR_RANGE> cbvRanges;
  std::vector<D3D12_DESCRIPTOR_RANGE> srvRanges;
  std::vector<D3D12_DESCRIPTOR_RANGE> uavRanges;

  for (uint i = 0; i < shaderObjects.size(); i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc = {};
    rangeDesc.RangeType              = ConvertToRangeType(shaderObjects[i].parameterType);
    rangeDesc.NumDescriptors         = 1;
    rangeDesc.RegisterSpace          = shaderObjects[i].registerSpace;
    rangeDesc.BaseShaderRegister     = shaderObjects[i].shaderRegister;
    if (rangeDesc.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_CBV)
    {
      rangeDesc.OffsetInDescriptorsFromTableStart = (UINT)cbvRanges.size();
      cbvRanges.push_back(rangeDesc);
    }
    else if (rangeDesc.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_SRV)
    {
      rangeDesc.OffsetInDescriptorsFromTableStart = (UINT)srvRanges.size();
      srvRanges.push_back(rangeDesc);
    }
    else if (rangeDesc.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_UAV)
    {
      rangeDesc.OffsetInDescriptorsFromTableStart = (UINT)uavRanges.size();
      uavRanges.push_back(rangeDesc);
    }
  }

  D3D12_ROOT_PARAMETER rootParams[3] = {};

  // CBV
  rootParams[0].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[0].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[0].DescriptorTable.NumDescriptorRanges = (UINT)cbvRanges.size();
  rootParams[0].DescriptorTable.pDescriptorRanges   = cbvRanges.data();

  // SRV
  rootParams[1].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[1].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[1].DescriptorTable.NumDescriptorRanges = (UINT)srvRanges.size();
  rootParams[1].DescriptorTable.pDescriptorRanges   = srvRanges.data();

  // UAV
  rootParams[2].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[2].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[2].DescriptorTable.NumDescriptorRanges = (UINT)uavRanges.size();
  rootParams[2].DescriptorTable.pDescriptorRanges   = uavRanges.data();

  D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSigDesc = {};
  rootSigDesc.Version                             = D3D_ROOT_SIGNATURE_VERSION_1_0;
  rootSigDesc.Desc_1_0.Flags = D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
  rootSigDesc.Desc_1_0.NumParameters = 3;
  rootSigDesc.Desc_1_0.pParameters   = &rootParams[0];

  D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
  samplerDesc.Filter                    = D3D12_FILTER_ANISOTROPIC;
  samplerDesc.AddressU                  = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.AddressV                  = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.AddressW                  = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.MaxAnisotropy             = 16;
  samplerDesc.RegisterSpace             = 0;
  samplerDesc.MinLOD                    = -D3D12_FLOAT32_MAX;
  samplerDesc.MaxLOD                    = D3D12_FLOAT32_MAX;
  samplerDesc.MipLODBias                = 0;
  samplerDesc.ShaderRegister            = 0;
  samplerDesc.ShaderVisibility          = D3D12_SHADER_VISIBILITY_ALL;

  rootSigDesc.Desc_1_0.pStaticSamplers   = &samplerDesc;
  rootSigDesc.Desc_1_0.NumStaticSamplers = 1;

  ID3DBlob* errorBlob_p     = nullptr;
  ID3DBlob* signatureBlob_p = nullptr;

  HR_ASSERT(D3D12SerializeRootSignature(
      &rootSigDesc.Desc_1_0, rootSigDesc.Version, &signatureBlob_p, &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  HRESULT hr = 0;

  HR_ASSERT(hr = Renderer::GetDevice()->CreateRootSignature(0,
                                                            signatureBlob_p->GetBufferPointer(),
                                                            signatureBlob_p->GetBufferSize(),
                                                            IID_PPV_ARGS(&myRootSignature_p)));

  return hr;
}

HRESULT ComputationalPipeline::CreatePipelineState()
{
  HRESULT hr = 0;
  pRootSignature    = myRootSignature_p;
  CS.BytecodeLength = myComputeShader_p->GetBufferSize();
  CS.pShaderBytecode = myComputeShader_p->GetBufferPointer();
  HR_ASSERT(hr = Renderer::GetDevice()->CreateComputePipelineState(
                this, IID_PPV_ARGS(&myPipelineState_p)));

  return hr;
}

ID3D12PipelineState* ComputationalPipeline::GetPipelineState() const
{
  return myPipelineState_p;
}

ID3D12RootSignature* ComputationalPipeline::GetRootSignature() const
{
  return myRootSignature_p;
}

void ComputationalPipeline::_initDefaultValues()
{

}
