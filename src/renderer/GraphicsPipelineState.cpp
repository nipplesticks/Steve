#include "GraphicsPipelineState.h"
#include "../utility/RenderUtility.h"
#include "../utility/UtilityFuncs.h"
#include "Renderer.h"
#include <d3dcompiler.h>

D3D12_ROOT_PARAMETER_TYPE ConvertToParameterType(D3D_SHADER_INPUT_TYPE inputType)
{
  switch (inputType)
  {
  case D3D_SIT_CBUFFER: // CBV
    return D3D12_ROOT_PARAMETER_TYPE_CBV;
  case D3D_SIT_TEXTURE: // Texture
    return D3D12_ROOT_PARAMETER_TYPE_SRV;
  }

  ASSERT_STR(false, "Passed input not defined (%d), eat ass\n", inputType);

  return D3D12_ROOT_PARAMETER_TYPE_CBV;
}

D3D12_DESCRIPTOR_RANGE_TYPE ConvertToRangeType(D3D12_ROOT_PARAMETER_TYPE inputType)
{
  switch (inputType)
  {
  case D3D12_ROOT_PARAMETER_TYPE_CBV:
    return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
  case D3D12_ROOT_PARAMETER_TYPE_SRV:
    return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  case D3D12_ROOT_PARAMETER_TYPE_UAV:
    return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
  }

  ASSERT_STR(false, "Passed input not defined (%d), eat ass\n", inputType);

  return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
}

GraphicsPipelineState::GraphicsPipelineState()
    : D3D12_GRAPHICS_PIPELINE_STATE_DESC {}

{
  _defaultValues();
}

GraphicsPipelineState::~GraphicsPipelineState() { }

HRESULT GraphicsPipelineState::SetVertexShader(const std::string& vertexShader)
{
  std::wstring shaderLocation(vertexShader.begin(), vertexShader.end());
  ID3DBlob*    errorBlob_p  = nullptr;
  UINT         compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT      hr           = 0;
  HR_ASSERT(hr = D3DCompileFromFile(shaderLocation.c_str(),
                                    nullptr,
                                    nullptr,
                                    "main",
                                    "vs_5_1",
                                    compileFlags,
                                    0,
                                    &myVertexShader_p,
                                    &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  VS.pShaderBytecode = myVertexShader_p->GetBufferPointer();
  VS.BytecodeLength  = myVertexShader_p->GetBufferSize();

  return hr;
}

HRESULT GraphicsPipelineState::SetHullShader(const std::string& hullShader)
{
  return E_NOTIMPL;
}

HRESULT GraphicsPipelineState::SetDomainShader(const std::string& domainShader)
{
  return E_NOTIMPL;
}

HRESULT GraphicsPipelineState::SetGeometryShader(const std::string& geometryShader)
{
  return E_NOTIMPL;
}

HRESULT GraphicsPipelineState::SetPixelShader(const std::string& pixelShader)
{
  ID3DBlob* errorBlob_p  = nullptr;
  UINT      compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT   hr           = 0;
  HR_ASSERT(hr = D3DCompileFromFile(L"assets/shaders/PixelHelloTriangle.hlsl",
                                    nullptr,
                                    nullptr,
                                    "main",
                                    "ps_5_1",
                                    compileFlags,
                                    0,
                                    &myPixelShader_p,
                                    &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  PS.pShaderBytecode = myPixelShader_p->GetBufferPointer();
  PS.BytecodeLength  = myPixelShader_p->GetBufferSize();

  return hr;
}

void GraphicsPipelineState::GenerateInputElementDesc()
{
  ID3D12ShaderReflection* shaderReflection_p = nullptr;
  HR_ASSERT(D3DReflect(myVertexShader_p->GetBufferPointer(),
                       myVertexShader_p->GetBufferSize(),
                       IID_PPV_ARGS(&shaderReflection_p)));

  D3D12_SHADER_DESC shaderDesc = {};
  shaderReflection_p->GetDesc(&shaderDesc);

  myInputElementDescs.resize(shaderDesc.InputParameters);

  for (uint i = 0; i < shaderDesc.InputParameters; i++)
  {
    D3D12_SIGNATURE_PARAMETER_DESC paramDesc = {};
    shaderReflection_p->GetInputParameterDesc(i, &paramDesc);
    myInputElementDescs[i].SemanticName      = paramDesc.SemanticName;
    myInputElementDescs[i].SemanticIndex     = paramDesc.SemanticIndex;
    myInputElementDescs[i].InputSlot         = 0;
    myInputElementDescs[i].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
    myInputElementDescs[i].InputSlotClass    = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;

    // determine DXGI format
    if (paramDesc.Mask == 1)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32_FLOAT;
    }
    else if (paramDesc.Mask <= 3)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32_FLOAT;
    }
    else if (paramDesc.Mask <= 7)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32B32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32B32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    }
    else if (paramDesc.Mask <= 15)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32B32A32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32B32A32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        myInputElementDescs[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    }
  }
}

void GraphicsPipelineState::SetRootSignature(ID3D12RootSignature* rootSignature_p)
{
  myRootSignature_p = rootSignature_p;
}

HRESULT GraphicsPipelineState::GenerateRootSignature()
{
  enum ShaderType
  {
    VertexShader = 0,
    PixelShader
  };

  struct ShaderObject
  {
    ShaderType                shaderType;
    uint                      shaderRegister;
    uint                      registerSpace;
    D3D12_ROOT_PARAMETER_TYPE parameterType;
    bool                      operator==(const ShaderObject& other)
    {
      return shaderRegister == other.shaderRegister && parameterType == other.parameterType;
    }
  };

  std::vector<ShaderObject> shaderObjects;
  ID3DBlob*                 shaders_p[] = {myVertexShader_p, myPixelShader_p};

  for (ID3DBlob* shader_p : shaders_p)
  {
    if (shader_p)
    {
      ID3D12ShaderReflection* shaderReflection_p = nullptr;
      HR_ASSERT(D3DReflect(shader_p->GetBufferPointer(),
                           shader_p->GetBufferSize(),
                           IID_PPV_ARGS(&shaderReflection_p)));

      D3D12_SHADER_DESC shaderDesc = {};
      shaderReflection_p->GetDesc(&shaderDesc);

      for (uint i = 0; i < shaderDesc.BoundResources; i++)
      {
        ShaderObject shaderObj {};
        if (shader_p == myVertexShader_p)
          shaderObj.shaderType = ShaderType::VertexShader;
        else if (shader_p == myPixelShader_p)
          shaderObj.shaderType = ShaderType::PixelShader;

        D3D12_SHADER_INPUT_BIND_DESC desc {};
        shaderReflection_p->GetResourceBindingDesc(i, &desc);
        if (desc.Type == D3D_SIT_SAMPLER)
          continue;
        shaderObj.parameterType   = ConvertToParameterType(desc.Type);
        shaderObj.shaderRegister  = desc.BindPoint;
        shaderObj.registerSpace   = desc.Space;
        shaderObjects.push_back(shaderObj);
      }
    }
  }

  std::vector<D3D12_DESCRIPTOR_RANGE> cbvRanges;
  std::vector<D3D12_DESCRIPTOR_RANGE> srvRanges;

  for (uint i = 0; i < shaderObjects.size(); i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc = {};
    rangeDesc.RangeType              = ConvertToRangeType(shaderObjects[i].parameterType);
    rangeDesc.NumDescriptors         = 1;
    rangeDesc.RegisterSpace          = shaderObjects[i].registerSpace;
    rangeDesc.BaseShaderRegister     = shaderObjects[i].shaderRegister;
    if (rangeDesc.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_CBV)
    {
      rangeDesc.OffsetInDescriptorsFromTableStart = cbvRanges.size();
      cbvRanges.push_back(rangeDesc);
    }
    else if (rangeDesc.RangeType == D3D12_DESCRIPTOR_RANGE_TYPE_SRV)
    {
      rangeDesc.OffsetInDescriptorsFromTableStart = srvRanges.size();
      srvRanges.push_back(rangeDesc);
    }
  }

  D3D12_ROOT_PARAMETER rootParams[2] = {};

  // CBV
  rootParams[0].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[0].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[0].DescriptorTable.NumDescriptorRanges = cbvRanges.size();
  rootParams[0].DescriptorTable.pDescriptorRanges   = cbvRanges.data();

  // SRV
  rootParams[1].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[1].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[1].DescriptorTable.NumDescriptorRanges = srvRanges.size();
  rootParams[1].DescriptorTable.pDescriptorRanges   = srvRanges.data();

  D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSigDesc = {};
  rootSigDesc.Version                             = D3D_ROOT_SIGNATURE_VERSION_1_0;
  rootSigDesc.Desc_1_0.Flags         = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
  rootSigDesc.Desc_1_0.NumParameters = 2;
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

void GraphicsPipelineState::SetInputElementDesc(
    const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElementDescs)
{
  myInputElementDescs = inputElementDescs;
}

HRESULT GraphicsPipelineState::CreatePipelineState()
{
  InputLayout.pInputElementDescs = myInputElementDescs.data();
  InputLayout.NumElements        = myInputElementDescs.size();
  pRootSignature                 = myRootSignature_p;
  HRESULT hr                     = 0;
  HR_ASSERT(hr = Renderer::GetDevice()->CreateGraphicsPipelineState(
                this, IID_PPV_ARGS(&myPipelineState_p)));

  return hr;
}

ID3D12PipelineState* GraphicsPipelineState::GetPipelineState() const
{
  return myPipelineState_p;
}

ID3D12RootSignature* GraphicsPipelineState::GetRootSignature() const
{
  return myRootSignature_p;
}

void GraphicsPipelineState::_defaultValues()
{
  RasterizerState.FillMode                         = D3D12_FILL_MODE_SOLID;
  RasterizerState.CullMode                         = D3D12_CULL_MODE_BACK;
  PrimitiveTopologyType                            = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
  NumRenderTargets                                 = 1;
  RTVFormats[0]                                    = DXGI_FORMAT_R8G8B8A8_UNORM;
  SampleDesc.Count                                 = 1;
  SampleMask                                       = UINT_MAX;
  GS.BytecodeLength                                = 0;
  BlendState.AlphaToCoverageEnable                 = FALSE;
  BlendState.IndependentBlendEnable                = FALSE;
  BlendState.RenderTarget[0].BlendEnable           = FALSE;
  BlendState.RenderTarget[0].LogicOpEnable         = FALSE;
  BlendState.RenderTarget[0].SrcBlend              = D3D12_BLEND_ONE;
  BlendState.RenderTarget[0].DestBlend             = D3D12_BLEND_ZERO;
  BlendState.RenderTarget[0].BlendOp               = D3D12_BLEND_OP_ADD;
  BlendState.RenderTarget[0].SrcBlendAlpha         = D3D12_BLEND_ONE;
  BlendState.RenderTarget[0].DestBlendAlpha        = D3D12_BLEND_ZERO;
  BlendState.RenderTarget[0].BlendOpAlpha          = D3D12_BLEND_OP_ADD;
  BlendState.RenderTarget[0].LogicOp               = D3D12_LOGIC_OP_NOOP;
  BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
  DepthStencilState.DepthEnable                    = TRUE;
  DepthStencilState.DepthFunc                      = D3D12_COMPARISON_FUNC_LESS_EQUAL;
  DSVFormat                                        = DXGI_FORMAT_D32_FLOAT;
  DepthStencilState.DepthWriteMask                 = D3D12_DEPTH_WRITE_MASK_ALL;
}
