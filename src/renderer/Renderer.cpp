#include "Renderer.h"

#include "../utility/RenderUtility.h"
#include <d3dcompiler.h>
#include <dxgi1_6.h> //Only used for initialization of the device and swap chain.

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3dcompiler.lib")

template <class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
  if (*ppInterfaceToRelease != NULL)
  {
    (*ppInterfaceToRelease)->Release();

    (*ppInterfaceToRelease) = NULL;
  }
}

Renderer::Renderer(uint x, uint y, HWND aHwnd)
{
  DirectX::XMFLOAT4A triPos[] = {
      {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, -1.0f, 0.0f, 1.0f}, {-1.0f, -1.0f, 0.0f, 1.0f}};

  gTriangle[0].position = triPos[0];
  gTriangle[0].color    = DirectX::XMFLOAT4A(1.0f, 0.0f, 0.0f, 1.0f);
  gTriangle[0].uv       = DirectX::XMFLOAT2A(0.0f, 0.0f);

  gTriangle[1].position = triPos[1];
  gTriangle[1].color    = DirectX::XMFLOAT4A(0.0f, 1.0f, 0.0f, 1.0f);
  gTriangle[1].uv       = DirectX::XMFLOAT2A(0.0f, 0.0f);

  gTriangle[2].position = triPos[2];
  gTriangle[2].color    = DirectX::XMFLOAT4A(0.0f, 0.0f, 1.0f, 1.0f);
  gTriangle[2].uv       = DirectX::XMFLOAT2A(0.0f, 0.0f);

  // Init device
  {
    ID3D12Debug* debugController_p = nullptr;

    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_p))))
    {
      debugController_p->EnableDebugLayer();
    }

    SafeRelease(&debugController_p);

    IDXGIFactory6* factory_p = nullptr;
    IDXGIAdapter1* adapter_p = nullptr;
    CreateDXGIFactory(IID_PPV_ARGS(&factory_p));

    for (UINT adapterIndex = 0;; adapterIndex++)
    {
      adapter_p = nullptr;
      if (DXGI_ERROR_NOT_FOUND == factory_p->EnumAdapters1(adapterIndex, &adapter_p))
      {
        break; //No more adapters to enumerate.
      }

      // Check to see if the adapter supports Direct3D 12, but don't create the actual device yet.
      if (SUCCEEDED(D3D12CreateDevice(
              adapter_p, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device5), nullptr)))
      {
        break;
      }

      SafeRelease(&adapter_p);
    }

    if (adapter_p)
    {
      HRESULT hr = S_OK;
      //Create the actual device.
      if (SUCCEEDED(hr = D3D12CreateDevice(
                        adapter_p, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&myDevice5_p))))
      {
        int lol = 123;
      }

      SafeRelease(&adapter_p);
    }
    else
    {
      //Create warp device if no adapter was found.
      factory_p->EnumWarpAdapter(IID_PPV_ARGS(&adapter_p));
      D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&myDevice5_p));
    }

    SafeRelease(&factory_p);
  }

  // Create Commandinterfaces And Swap Chain
  {
    //Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC cqd = {};
    HRESULT hr = myDevice5_p->CreateCommandQueue(&cqd, IID_PPV_ARGS(&myCommandQueue_p));

    //Create command allocator. The command allocator object corresponds
    //to the underlying allocations in which GPU commands are stored.
    hr = myDevice5_p->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                             IID_PPV_ARGS(&myCommandAllocator_p));

    //Create command list.
    hr = myDevice5_p->CreateCommandList(0,
                                        D3D12_COMMAND_LIST_TYPE_DIRECT,
                                        myCommandAllocator_p,
                                        nullptr,
                                        IID_PPV_ARGS(&myCommandList4_p));

    //Command lists are created in the recording state. Since there is nothing to
    //record right now and the main loop expects it to be closed, we close it.
    hr = myCommandList4_p->Close();

    IDXGIFactory5* factory_p = nullptr;
    CreateDXGIFactory(IID_PPV_ARGS(&factory_p));

    //Create swap chain.
    DXGI_SWAP_CHAIN_DESC1 scDesc = {};
    scDesc.Width                 = 0;
    scDesc.Height                = 0;
    scDesc.Format                = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.Stereo                = FALSE;
    scDesc.SampleDesc.Count      = 1;
    scDesc.SampleDesc.Quality    = 0;
    scDesc.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.BufferCount           = NUM_SWAP_BUFFERS;
    scDesc.Scaling               = DXGI_SCALING_NONE;
    scDesc.SwapEffect            = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scDesc.Flags                 = 0;
    scDesc.AlphaMode             = DXGI_ALPHA_MODE_UNSPECIFIED;

    IDXGISwapChain1* swapChain1_p = nullptr;
    if (SUCCEEDED(factory_p->CreateSwapChainForHwnd(
            myCommandQueue_p, aHwnd, &scDesc, nullptr, nullptr, &swapChain1_p)))
    {
      if (SUCCEEDED(swapChain1_p->QueryInterface(IID_PPV_ARGS(&mySwapChain4_p))))
      {
        swapChain1_p->Release();
      }
      myCurrentBackbufferIndex = mySwapChain4_p->GetCurrentBackBufferIndex();
    }

    SafeRelease(&factory_p);
  }
  // Setup Viewport
  {
    uint width  = 0u;
    uint height = 0u;
    mySwapChain4_p->GetSourceSize(&width, &height);
    myViewport.Width  = (float)width;
    myViewport.Height = (float)height;

    myScissorRect.right  = (long)INT_MAX;
    myScissorRect.bottom = (long)INT_MAX;
  }
  // Create Fence And Event Handle
  {
    myDevice5_p->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&myFence_p));
    myFenceValue = 1;
    //Create an event handle to use for GPU synchronization.
    myEventHandle = CreateEvent(0, false, false, 0);
  }
  // Create Render Targets
  {
    //Create descriptor heap for render target views.
    D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
    dhd.NumDescriptors             = NUM_SWAP_BUFFERS;
    dhd.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

    HRESULT hr = myDevice5_p->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(&myRenderTargetsHeap_p));

    //Create resources for the render targets.
    myRenderTargetDescriptorSize =
        myDevice5_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE cdh = myRenderTargetsHeap_p->GetCPUDescriptorHandleForHeapStart();

    //One RTV for each frame.
    for (UINT n = 0; n < NUM_SWAP_BUFFERS; n++)
    {
      hr = mySwapChain4_p->GetBuffer(n, IID_PPV_ARGS(&myRenderTargets_pp[n]));
      myDevice5_p->CreateRenderTargetView(myRenderTargets_pp[n], nullptr, cdh);
      cdh.ptr += myRenderTargetDescriptorSize;
    }
  }

  //Setup Vertex Buffer
  _SetupShaderState();
}

Renderer::~Renderer() { }

void Renderer::SetViewProjection(const DM::Mat4x4& viewProj)
{
  void* adress_p = nullptr;
  HR_ASSERT(myViewProjBuffer_p->Map(0, nullptr, &adress_p));
  memcpy(adress_p, &viewProj, sizeof(viewProj));
  myViewProjBuffer_p->Unmap(0, nullptr);
}

void Renderer::BeginFrame()
{
  myCommandAllocator_p->Reset();
  myCommandList4_p->Reset(myCommandAllocator_p, nullptr);

  _SetResourceTransitionBarrier(myCommandList4_p,
                                myRenderTargets_pp[myCurrentBackbufferIndex],
                                D3D12_RESOURCE_STATE_PRESENT,
                                D3D12_RESOURCE_STATE_RENDER_TARGET);

  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHndl =
      myRenderTargetsHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHndl.ptr += myCurrentBackbufferIndex * myRenderTargetDescriptorSize;

  myCommandList4_p->OMSetRenderTargets(1, &cpuDescHndl, TRUE, NULL);
}

void Renderer::DrawTriangle()
{
  myCommandList4_p->SetPipelineState(myPipelineState_p);
  myCommandList4_p->SetGraphicsRootSignature(myRootSignature_p);


  myCommandList4_p->RSSetViewports(1, &myViewport);
  myCommandList4_p->RSSetScissorRects(1, &myScissorRect);

  myCommandList4_p->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  myCommandList4_p->IASetVertexBuffers(0, 1, &myVertexBufferView);

  myCommandList4_p->SetGraphicsRootConstantBufferView(0,
                                                      myViewProjBuffer_p->GetGPUVirtualAddress());

  myCommandList4_p->DrawInstanced(3, 1, 0, 0);
}

void Renderer::Clear(const Vector4f& color)
{
  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHndl =
      myRenderTargetsHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHndl.ptr += myCurrentBackbufferIndex * myRenderTargetDescriptorSize;

  myCommandList4_p->ClearRenderTargetView(cpuDescHndl, (FLOAT*)&color, 0, NULL);
}

void Renderer::EndFrame()
{
  _SetResourceTransitionBarrier(myCommandList4_p,
                                myRenderTargets_pp[myCurrentBackbufferIndex],
                                D3D12_RESOURCE_STATE_RENDER_TARGET,
                                D3D12_RESOURCE_STATE_PRESENT);

  HR_ASSERT(myCommandList4_p->Close());

  // Send to queue
  myCommandQueue_p->ExecuteCommandLists(1,
                                        reinterpret_cast<ID3D12CommandList**>(&myCommandList4_p));

  // Present
  HR_ASSERT(mySwapChain4_p->Present(0, 0));

  // Hard wait
  myCommandQueue_p->Signal(myFence_p, myFenceValue);

  if (myFenceValue > myFence_p->GetCompletedValue())
  {
    myFence_p->SetEventOnCompletion(myFenceValue, myEventHandle);
    WaitForMultipleObjects(1, &myEventHandle, TRUE, INFINITE);
  }

  myFenceValue++;

  myCurrentBackbufferIndex = mySwapChain4_p->GetCurrentBackBufferIndex();
}

void Renderer::_SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p,
                                             ID3D12Resource*            resource_p,
                                             D3D12_RESOURCE_STATES      StateBefore,
                                             D3D12_RESOURCE_STATES      StateAfter)
{
  D3D12_RESOURCE_BARRIER barrierDesc = {};

  barrierDesc.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrierDesc.Transition.pResource   = resource_p;
  barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrierDesc.Transition.StateBefore = StateBefore;
  barrierDesc.Transition.StateAfter  = StateAfter;

  commandList_p->ResourceBarrier(1, &barrierDesc);
}

void Renderer::_SetupShaderState()
{
  // Init vertex buffer
  {
    D3D12_HEAP_PROPERTIES heapProp = {};
    heapProp.Type                  = D3D12_HEAP_TYPE_UPLOAD;
    heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

    D3D12_RESOURCE_DESC desc = {};
    desc.DepthOrArraySize    = 1;
    desc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Flags               = D3D12_RESOURCE_FLAG_NONE;
    desc.Format              = DXGI_FORMAT_UNKNOWN;
    desc.Height              = 1;
    desc.Width               = sizeof(gTriangle);
    desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.MipLevels           = 1;
    desc.SampleDesc.Count    = 1;
    desc.SampleDesc.Quality  = 0;

    HR_ASSERT(myDevice5_p->CreateCommittedResource(&heapProp,
                                                   D3D12_HEAP_FLAG_NONE,
                                                   &desc,
                                                   D3D12_RESOURCE_STATE_GENERIC_READ,
                                                   nullptr,
                                                   IID_PPV_ARGS(&myVertexBuffer_p)));

    void* adress_p = nullptr;
    HR_ASSERT(myVertexBuffer_p->Map(0, nullptr, &adress_p));
    memcpy(adress_p, &gTriangle[0], sizeof(gTriangle));
    myVertexBuffer_p->Unmap(0, nullptr);

    myVertexBufferView.BufferLocation = myVertexBuffer_p->GetGPUVirtualAddress();
    myVertexBufferView.SizeInBytes    = sizeof(Vertex) * 3;
    myVertexBufferView.StrideInBytes  = sizeof(Vertex);
  }

  // Setup ViewProj buffer
  {
    D3D12_HEAP_PROPERTIES heapProp = {};
    heapProp.Type                  = D3D12_HEAP_TYPE_UPLOAD;
    heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

    D3D12_RESOURCE_DESC desc = {};
    desc.DepthOrArraySize    = 1;
    desc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Flags               = D3D12_RESOURCE_FLAG_NONE;
    desc.Format              = DXGI_FORMAT_UNKNOWN;
    desc.Height              = 1;
    desc.Width               = sizeof(DirectX::XMFLOAT4X4);
    desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.MipLevels           = 1;
    desc.SampleDesc.Count    = 1;
    desc.SampleDesc.Quality  = 0;

    HR_ASSERT(myDevice5_p->CreateCommittedResource(&heapProp,
                                                   D3D12_HEAP_FLAG_NONE,
                                                   &desc,
                                                   D3D12_RESOURCE_STATE_GENERIC_READ,
                                                   nullptr,
                                                   IID_PPV_ARGS(&myViewProjBuffer_p)));
  }

  // Create root signature
  {
    D3D12_ROOT_PARAMETER rootParam = {};
    rootParam.ParameterType        = D3D12_ROOT_PARAMETER_TYPE_CBV;
    rootParam.ShaderVisibility     = D3D12_SHADER_VISIBILITY_VERTEX;
    rootParam.Descriptor.RegisterSpace = 0;
    rootParam.Descriptor.ShaderRegister = 0;

    D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSigDesc = {};
    rootSigDesc.Version                             = D3D_ROOT_SIGNATURE_VERSION_1_0;
    rootSigDesc.Desc_1_0.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    rootSigDesc.Desc_1_0.NumParameters = 1;
    rootSigDesc.Desc_1_0.pParameters   = &rootParam;

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

    HR_ASSERT(myDevice5_p->CreateRootSignature(0,
                                               signatureBlob_p->GetBufferPointer(),
                                               signatureBlob_p->GetBufferSize(),
                                               IID_PPV_ARGS(&myRootSignature_p)));
  }

  // Setup Shaders
  {
    // Compile shaders
    {
      ID3DBlob* errorBlob_p  = nullptr;
      UINT      compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

      HR_ASSERT(D3DCompileFromFile(L"assets/shaders/VertexHelloTriangle.hlsl",
                                   nullptr,
                                   nullptr,
                                   "main",
                                   "vs_5_0",
                                   compileFlags,
                                   0,
                                   &myVertexShader_p,
                                   &errorBlob_p));

      if (errorBlob_p != nullptr)
        printf("%s\n", (char*)errorBlob_p->GetBufferPointer());
    }
    {
      ID3DBlob* errorBlob_p  = nullptr;
      UINT      compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

      HR_ASSERT(D3DCompileFromFile(L"assets/shaders/PixelHelloTriangle.hlsl",
                                   nullptr,
                                   nullptr,
                                   "main",
                                   "ps_5_0",
                                   compileFlags,
                                   0,
                                   &myPixelShader_p,
                                   &errorBlob_p));

      if (errorBlob_p != nullptr)
        printf("%s\n", (char*)errorBlob_p->GetBufferPointer());
    }

    // Setup pipeline state
    {
      D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeDesc = {};
      memset(&pipeDesc, 0, sizeof(pipeDesc));
      pipeDesc.RasterizerState.FillMode                  = D3D12_FILL_MODE_SOLID;
      pipeDesc.RasterizerState.CullMode                  = D3D12_CULL_MODE_BACK;
      pipeDesc.PrimitiveTopologyType                     = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
      pipeDesc.NumRenderTargets                          = 1;
      pipeDesc.RTVFormats[0]                             = DXGI_FORMAT_R8G8B8A8_UNORM;
      pipeDesc.SampleDesc.Count                          = 1;
      pipeDesc.SampleMask                                = UINT_MAX;
      pipeDesc.VS.pShaderBytecode                        = myVertexShader_p->GetBufferPointer();
      pipeDesc.VS.BytecodeLength                         = myVertexShader_p->GetBufferSize();
      pipeDesc.PS.pShaderBytecode                        = myPixelShader_p->GetBufferPointer();
      pipeDesc.PS.BytecodeLength                         = myPixelShader_p->GetBufferSize();
      pipeDesc.BlendState.AlphaToCoverageEnable          = FALSE;
      pipeDesc.BlendState.IndependentBlendEnable         = FALSE;
      pipeDesc.BlendState.RenderTarget[0].BlendEnable    = FALSE;
      pipeDesc.BlendState.RenderTarget[0].LogicOpEnable  = FALSE;
      pipeDesc.BlendState.RenderTarget[0].SrcBlend       = D3D12_BLEND_ONE;
      pipeDesc.BlendState.RenderTarget[0].DestBlend      = D3D12_BLEND_ZERO;
      pipeDesc.BlendState.RenderTarget[0].BlendOp        = D3D12_BLEND_OP_ADD;
      pipeDesc.BlendState.RenderTarget[0].SrcBlendAlpha  = D3D12_BLEND_ONE;
      pipeDesc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
      pipeDesc.BlendState.RenderTarget[0].BlendOpAlpha   = D3D12_BLEND_OP_ADD;
      pipeDesc.BlendState.RenderTarget[0].LogicOp        = D3D12_LOGIC_OP_NOOP;
      pipeDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

      ID3D12ShaderReflection* shaderReflection_p = nullptr;
      HR_ASSERT(D3DReflect(myVertexShader_p->GetBufferPointer(),
                           myVertexShader_p->GetBufferSize(),
                           IID_PPV_ARGS(&shaderReflection_p)));

      D3D12_SHADER_DESC shaderDesc = {};
      shaderReflection_p->GetDesc(&shaderDesc);

      D3D12_INPUT_ELEMENT_DESC inputDesc[8] = {};

      for (uint i = 0; i < shaderDesc.InputParameters; i++)
      {
        D3D12_SIGNATURE_PARAMETER_DESC paramDesc = {};
        shaderReflection_p->GetInputParameterDesc(i, &paramDesc);
        inputDesc[i].SemanticName      = paramDesc.SemanticName;
        inputDesc[i].SemanticIndex     = paramDesc.SemanticIndex;
        inputDesc[i].InputSlot         = 0;
        inputDesc[i].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
        inputDesc[i].InputSlotClass    = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;

        // determine DXGI format
        if (paramDesc.Mask == 1)
        {
          if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32_UINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32_SINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
            inputDesc[i].Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask <= 3)
        {
          if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32_UINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32_SINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask <= 7)
        {
          if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32B32_UINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32B32_SINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask <= 15)
        {
          if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32B32A32_UINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32B32A32_SINT;
          else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
            inputDesc[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
      }

      pipeDesc.InputLayout.pInputElementDescs = &inputDesc[0];
      pipeDesc.InputLayout.NumElements        = shaderDesc.InputParameters;
      pipeDesc.pRootSignature                 = myRootSignature_p;

      HR_ASSERT(
          myDevice5_p->CreateGraphicsPipelineState(&pipeDesc, IID_PPV_ARGS(&myPipelineState_p)));
    }
  }
}
