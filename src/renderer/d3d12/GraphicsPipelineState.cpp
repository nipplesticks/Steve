#include "GraphicsPipelineState.h"
#include "../../utility/RenderUtility.h"
#include "../../utility/UtilityFuncs.h"
#include "myRenderer.h"
#include <d3dcompiler.h>
#include "../buffers/Rendertarget.h"

bool GraphicsPipelineState::WIRE_FRAME = false;

GraphicsPipelineState::GraphicsPipelineState()
    : D3D12_GRAPHICS_PIPELINE_STATE_DESC {}

{
  _defaultValues();
}

GraphicsPipelineState::~GraphicsPipelineState()
{
  
}

HRESULT GraphicsPipelineState::SetVertexShader(const std::string& vertexShader)
{
  std::cout << "shader: " << vertexShader << std::endl;
  std::wstring shaderLocation(vertexShader.begin(), vertexShader.end());
  ID3DBlob*    errorBlob_p  = nullptr;
  UINT         compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT      hr           = 0;
  HR_ASSERT(hr = D3DCompileFromFile(shaderLocation.c_str(),
                                    nullptr,
                                    D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                    "main",
                                    "vs_5_0",
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
  std::cout << "shader: " << hullShader << std::endl;
  std::wstring shaderLocation(hullShader.begin(), hullShader.end());
  ID3DBlob*    errorBlob_p  = nullptr;
  UINT         compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT      hr           = 0;
  HR_ASSERT(hr = D3DCompileFromFile(shaderLocation.c_str(),
                                    nullptr,
                                    D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                    "main",
                                    "hs_5_0",
                                    compileFlags,
                                    0,
                                    &myHullShader_p,
                                    &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  HS.pShaderBytecode = myHullShader_p->GetBufferPointer();
  HS.BytecodeLength  = myHullShader_p->GetBufferSize();

  return hr;
}

HRESULT GraphicsPipelineState::SetDomainShader(const std::string& domainShader)
{
  std::cout << "shader: " << domainShader << std::endl;
  std::wstring shaderLocation(domainShader.begin(), domainShader.end());
  ID3DBlob*    errorBlob_p  = nullptr;
  UINT         compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT      hr           = 0;
  HR_ASSERT(hr = D3DCompileFromFile(shaderLocation.c_str(),
                                    nullptr,
                                    D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                    "main",
                                    "ds_5_0",
                                    compileFlags,
                                    0,
                                    &myDomainShader_p,
                                    &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  DS.pShaderBytecode = myDomainShader_p->GetBufferPointer();
  DS.BytecodeLength  = myDomainShader_p->GetBufferSize();

  return hr;
}

HRESULT GraphicsPipelineState::SetGeometryShader(const std::string& geometryShader)
{
  std::cout << "shader: " << geometryShader << std::endl;
  std::wstring shaderLocation(geometryShader.begin(), geometryShader.end());
  ID3DBlob*    errorBlob_p  = nullptr;
  UINT         compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT      hr           = 0;
  HR_ASSERT(hr = D3DCompileFromFile(shaderLocation.c_str(),
                                    nullptr,
                                    D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                    "main",
                                    "gs_5_0",
                                    compileFlags,
                                    0,
                                    &myGeometryShader_p,
                                    &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  GS.pShaderBytecode = myGeometryShader_p->GetBufferPointer();
  GS.BytecodeLength  = myGeometryShader_p->GetBufferSize();

  return hr;
}

HRESULT GraphicsPipelineState::SetPixelShader(const std::string& pixelShader)
{
  std::cout << "shader: " << pixelShader << std::endl;
  std::wstring shaderLocation(pixelShader.begin(), pixelShader.end());
  ID3DBlob*    errorBlob_p  = nullptr;
  UINT         compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
  HRESULT      hr           = 0;
  HR_ASSERT(hr = D3DCompileFromFile(shaderLocation.c_str(),
                                    nullptr,
                                    D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                    "main",
                                    "ps_5_0",
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

void GraphicsPipelineState::EnableBlending()
{
  uint i                                           = RenderTarget::RenderTargetType::Color;
  BlendState.AlphaToCoverageEnable                 = FALSE;
  BlendState.IndependentBlendEnable                = FALSE;
  BlendState.RenderTarget[i].BlendEnable           = TRUE;
  BlendState.RenderTarget[i].LogicOpEnable         = FALSE;
  BlendState.RenderTarget[i].SrcBlend              = D3D12_BLEND_SRC_ALPHA;
  BlendState.RenderTarget[i].DestBlend             = D3D12_BLEND_INV_SRC_ALPHA;
  BlendState.RenderTarget[i].BlendOp               = D3D12_BLEND_OP_ADD;
  BlendState.RenderTarget[i].SrcBlendAlpha         = D3D12_BLEND_ONE;
  BlendState.RenderTarget[i].DestBlendAlpha        = D3D12_BLEND_ZERO;
  BlendState.RenderTarget[i].BlendOpAlpha          = D3D12_BLEND_OP_ADD;
  BlendState.RenderTarget[i].LogicOp               = D3D12_LOGIC_OP_NOOP;
  BlendState.RenderTarget[i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
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

void GraphicsPipelineState::SetInputElementDesc(
    const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElementDescs)
{
  myInputElementDescs = inputElementDescs;
}

HRESULT GraphicsPipelineState::CreatePipelineState()
{
  auto before                    = RasterizerState.FillMode;
  InputLayout.pInputElementDescs = myInputElementDescs.data();
  InputLayout.NumElements        = (UINT)myInputElementDescs.size();
  pRootSignature                 = MyRenderer::GetInstance()->GetGraphicalRootSignature();
  HRESULT hr                     = 0;
  HR_ASSERT(hr = MyRenderer::GetInstance()->GetDevice()->CreateGraphicsPipelineState(
                this, IID_PPV_ARGS(&myPipelineState_p)));

  RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
  HR_ASSERT(hr = MyRenderer::GetInstance()->GetDevice()->CreateGraphicsPipelineState(
                this, IID_PPV_ARGS(&myPipelineStateWireframe_p)));

  RasterizerState.FillMode = before;

  return hr;
}

ID3D12PipelineState* GraphicsPipelineState::GetPipelineState() const
{
  if (WIRE_FRAME)
    return myPipelineStateWireframe_p;
  return myPipelineState_p;
}

void GraphicsPipelineState::_defaultValues()
{
  RasterizerState.FillMode                         = D3D12_FILL_MODE_SOLID;
  RasterizerState.CullMode                         = D3D12_CULL_MODE_BACK;
  PrimitiveTopologyType                            = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
  NumRenderTargets                                 = RenderTarget::RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES;
  SampleDesc.Count                                 = 1;
  SampleMask                                       = UINT_MAX;
  DepthStencilState.DepthEnable                    = TRUE;
  DepthStencilState.DepthFunc                      = D3D12_COMPARISON_FUNC_LESS_EQUAL;
  DSVFormat                                        = DXGI_FORMAT_D32_FLOAT;
  DepthStencilState.DepthWriteMask                 = D3D12_DEPTH_WRITE_MASK_ALL;

  for (uint i = 0; i < NumRenderTargets; i++)
  {
    RTVFormats[i] = DXGI_FORMAT_R32G32B32A32_FLOAT;
    if (RenderTarget::RenderTargetType(i) == RenderTarget::RenderTargetType::PickableID)
      RTVFormats[i] = DXGI_FORMAT_R32_UINT;

    BlendState.AlphaToCoverageEnable                 = FALSE;
    BlendState.IndependentBlendEnable                = FALSE;
    BlendState.RenderTarget[i].BlendEnable           = FALSE;
    BlendState.RenderTarget[i].LogicOpEnable         = FALSE;
    BlendState.RenderTarget[i].SrcBlend              = D3D12_BLEND_ONE;
    BlendState.RenderTarget[i].DestBlend             = D3D12_BLEND_ZERO;
    BlendState.RenderTarget[i].BlendOp               = D3D12_BLEND_OP_ADD;
    BlendState.RenderTarget[i].SrcBlendAlpha         = D3D12_BLEND_ONE;
    BlendState.RenderTarget[i].DestBlendAlpha        = D3D12_BLEND_ZERO;
    BlendState.RenderTarget[i].BlendOpAlpha          = D3D12_BLEND_OP_ADD;
    BlendState.RenderTarget[i].LogicOp               = D3D12_LOGIC_OP_NOOP;
    BlendState.RenderTarget[i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    }
}
