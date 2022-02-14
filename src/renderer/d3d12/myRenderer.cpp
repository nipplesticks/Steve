#include "myRenderer.h"
#define NOMINMAX
#include "../../utility/RenderUtility.h"
#include "../../window/Window.h"
#include "d3dx12.h"
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3dcompiler.lib")

MyRenderer MyRenderer::gRenderer;
bool       MyRenderer::ENABLE_DEBUG_LAYER      = true;
bool       MyRenderer::ENABLE_DEBUG_CONTROLLER = false;
uint       MyRenderer::MAX_ALLOWED_CBV         = 32;
uint       MyRenderer::MAX_ALLOWED_SRV         = 16;
uint       MyRenderer::MAX_ALLOWED_UAV         = 16;

void MyRenderer::Init(HWND hwnd, uint resX, uint resY)
{
  gRenderer._Init(resX, resY, hwnd);
}

void MyRenderer::Release()
{
  gRenderer._Cleanup();
}

MyRenderer* MyRenderer::GetInstance()
{
  return &gRenderer;
}

void MyRenderer::BeginFrame(const DM::Vec4f& color)
{
  myGraphicalInterface.commandAllocator_p->Reset();
  myGraphicalInterface.commandList4_p->Reset(myGraphicalInterface.commandAllocator_p, nullptr);

  _SetResourceTransitionBarrier(
      myGraphicalInterface.commandList4_p,
      myGraphicalInterface.renderTargets_pp[myGraphicalInterface.currentBackbufferIndex],
      D3D12_RESOURCE_STATE_PRESENT,
      D3D12_RESOURCE_STATE_RENDER_TARGET);

  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHndl =
      myGraphicalInterface.renderTargetHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHndl.ptr +=
      myGraphicalInterface.currentBackbufferIndex * myGraphicalInterface.renderTargetDescriptorSize;

  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHnd2 =
      myGraphicalInterface.depthBufferHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHnd2.ptr +=
      myGraphicalInterface.currentBackbufferIndex * myGraphicalInterface.depthBufferDescriptorSize;
  myGraphicalInterface.commandList4_p->OMSetRenderTargets(1, &cpuDescHndl, TRUE, &cpuDescHnd2);
  
  myGraphicalInterface.commandList4_p->ClearDepthStencilView(
      cpuDescHnd2, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
  myGraphicalInterface.commandList4_p->ClearRenderTargetView(cpuDescHndl, (FLOAT*)color.data, 0, NULL);
  myGraphicalInterface.commandList4_p->SetGraphicsRootSignature(
      myGraphicalInterface.rootSignature_p);
}

void MyRenderer::EndFrame() { }

void MyRenderer::BeginCompute()
{
  myComputeInterface.commandAllocator_p->Reset();
  myComputeInterface.commandList4_p->Reset(myComputeInterface.commandAllocator_p, nullptr);
}

void MyRenderer::EndCompute() { }

void MyRenderer::DrawImgui() { }

void MyRenderer::SetResolution(uint resX, uint resY)
{
  SafeRelease(&myGraphicalInterface.swapChain_p);

  IDXGIFactory5* factory_p = nullptr;
  CreateDXGIFactory(IID_PPV_ARGS(&factory_p));

  myResulotion.x = resX;
  myResulotion.y = resY;

  DXGI_SWAP_CHAIN_DESC1 scDesc = {};
  scDesc.Width                 = resX;
  scDesc.Height                = resY;
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
  HR_ASSERT(factory_p->CreateSwapChainForHwnd(
      myGraphicalInterface.commandList4_p, myHwnd, &scDesc, nullptr, nullptr, &swapChain1_p));
  HR_ASSERT(swapChain1_p->QueryInterface(IID_PPV_ARGS(&myGraphicalInterface.swapChain_p)));
  SafeRelease(&swapChain1_p);
  myGraphicalInterface.currentBackbufferIndex =
      myGraphicalInterface.swapChain_p->GetCurrentBackBufferIndex();
  SafeRelease(&factory_p);
  myGraphicalInterface.swapChain_p->GetSourceSize(&myResulotion.x, &myResulotion.y);

  for (uint i = 0; i < NUM_SWAP_BUFFERS; i++)
  {
    SafeRelease(&myGraphicalInterface.renderTargets_pp[i]);
    SafeRelease(&myGraphicalInterface.depthBuffers_pp[i]);
  }

  _CreateViewport();

  D3D12_CPU_DESCRIPTOR_HANDLE cdh =
      myGraphicalInterface.renderTargetHeap_p->GetCPUDescriptorHandleForHeapStart();

  for (UINT n = 0; n < NUM_SWAP_BUFFERS; n++)
  {
    HR_ASSERT(myGraphicalInterface.swapChain_p->GetBuffer(
        n, IID_PPV_ARGS(&myGraphicalInterface.renderTargets_pp[n])));
    myDevice_p->CreateRenderTargetView(myGraphicalInterface.renderTargets_pp[n], nullptr, cdh);
    cdh.ptr += myGraphicalInterface.renderTargetDescriptorSize;
  }


  D3D12_HEAP_PROPERTIES heapProp = {};
  heapProp.Type                  = D3D12_HEAP_TYPE_DEFAULT;
  heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

  D3D12_RESOURCE_DESC desc = {};
  desc.DepthOrArraySize    = 1;
  desc.Dimension           = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  desc.Flags               = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
  desc.Format              = DXGI_FORMAT_D32_FLOAT;
  desc.Width               = myResulotion.x;
  desc.Height              = myResulotion.y;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;

  D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
  dsvDesc.Format                        = DXGI_FORMAT_D32_FLOAT;
  dsvDesc.ViewDimension                 = D3D12_DSV_DIMENSION_TEXTURE2D;

  D3D12_CPU_DESCRIPTOR_HANDLE cdh =
      myGraphicalInterface.depthBufferHeap_p->GetCPUDescriptorHandleForHeapStart();

  D3D12_CLEAR_VALUE clearVal  = {};
  clearVal.Format             = DXGI_FORMAT_D32_FLOAT;
  clearVal.DepthStencil.Depth = 1.0f;

  for (uint i = 0; i < NUM_SWAP_BUFFERS; i++)
  {
    HR_ASSERT(myDevice_p->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearVal,
        IID_PPV_ARGS(&myGraphicalInterface.depthBuffers_pp[i])));

    myDevice_p->CreateDepthStencilView(myGraphicalInterface.depthBuffers_pp[i], &dsvDesc, cdh);
    cdh.ptr += myGraphicalInterface.depthBufferDescriptorSize;
  }
}

ID3D12Device5* MyRenderer::GetDevice() const
{
  return myDevice_p;
}

ID3D12DescriptorHeap* MyRenderer::GetUploadHeap() const
{
  return myUploadHeap_p;
}

uint MyRenderer::GetSrvUavCbvDescritorSize() const
{
  return mySrvUavCbvDescriptorSize;
}

void MyRenderer::_Init(uint resX, uint resY, HWND hwnd)
{
  myHwnd         = hwnd;
  myResulotion.x = resX;
  myResulotion.y = resY;
  _CreateDevice();
  _CreateCommandInterfaceAndSwapChain();
  _CreateViewport();
  _CreateFenceAndHandleEvent();
  _CreateRenderTargets();
  _CreateDepthBuffers();
  _SetupComputeInterface();
  _CreateRootsignatures();
  _InitImgui();
}

void MyRenderer::_InitImgui()
{
  D3D12_DESCRIPTOR_HEAP_DESC desc = {};
  desc.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  desc.NumDescriptors             = 1;
  desc.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  HR_ASSERT(
      myDevice_p->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&myGraphicalInterface.imguiDescHeap_p)));

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  ImGui::StyleColorsDark();
  ASSERT(ImGui_ImplWin32_Init(myHwnd));
  ASSERT(ImGui_ImplDX12_Init(
      myDevice_p,
      NUM_SWAP_BUFFERS,
      DXGI_FORMAT_R8G8B8A8_UNORM,
      myGraphicalInterface.imguiDescHeap_p,
      myGraphicalInterface.imguiDescHeap_p->GetCPUDescriptorHandleForHeapStart(),
      myGraphicalInterface.imguiDescHeap_p->GetGPUDescriptorHandleForHeapStart()));
  Window::IMGUI_READY = true;
}

void MyRenderer::_CreateDevice()
{
  if (ENABLE_DEBUG_LAYER || ENABLE_DEBUG_CONTROLLER)
  {
    ID3D12Debug* debugController_p = nullptr;
    HR_ASSERT(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_p)));
    debugController_p->EnableDebugLayer();
    if (ENABLE_DEBUG_CONTROLLER)
    {
      ID3D12Debug1* debugcontroller1_p;
      HR_ASSERT(debugController_p->QueryInterface(IID_PPV_ARGS(&debugcontroller1_p)));
      debugcontroller1_p->SetEnableGPUBasedValidation(true);
    }
    SafeRelease(&debugController_p);
  }

  IDXGIFactory6* factory_p = nullptr;
  IDXGIAdapter1* adapter_p = nullptr;
  CreateDXGIFactory(IID_PPV_ARGS(&factory_p));
  for (UINT adapterIndex = 0;; adapterIndex++)
  {
    adapter_p = nullptr;
    if (DXGI_ERROR_NOT_FOUND == factory_p->EnumAdapters1(adapterIndex, &adapter_p))
      break;
    if (SUCCEEDED(
            D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device5), nullptr)))
      break;
    SafeRelease(&adapter_p);
  }
  if (adapter_p)
  {
    HR_ASSERT(D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&myDevice_p)));
    SafeRelease(&adapter_p);
  }
  else
  {
    factory_p->EnumWarpAdapter(IID_PPV_ARGS(&adapter_p));
    D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&myDevice_p));
  }
  SafeRelease(&factory_p);
}

void MyRenderer::_CreateCommandInterfaceAndSwapChain()
{
  D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
  HR_ASSERT(myDevice_p->CreateCommandQueue(&commandQueueDesc,
                                           IID_PPV_ARGS(&myGraphicalInterface.commandQueue_p)));
  HR_ASSERT(myDevice_p->CreateCommandAllocator(
      D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&myGraphicalInterface.commandAllocator_p)));
  HR_ASSERT(myDevice_p->CreateCommandList(0,
                                          D3D12_COMMAND_LIST_TYPE_DIRECT,
                                          myGraphicalInterface.commandAllocator_p,
                                          nullptr,
                                          IID_PPV_ARGS(&myGraphicalInterface.commandList4_p)));
  HR_ASSERT(myDevice_p->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                               IID_PPV_ARGS(&myResourceUploadAllocator_p)));
  HR_ASSERT(myDevice_p->CreateCommandList(0,
                                          D3D12_COMMAND_LIST_TYPE_DIRECT,
                                          myResourceUploadAllocator_p,
                                          nullptr,
                                          IID_PPV_ARGS(&myResourceUploadCommandList4_p)));
  HR_ASSERT(myResourceUploadCommandList4_p->Close());
  HR_ASSERT(myGraphicalInterface.commandList4_p->Close());

  IDXGIFactory5* factory_p = nullptr;
  CreateDXGIFactory(IID_PPV_ARGS(&factory_p));

  DXGI_SWAP_CHAIN_DESC1 scDesc = {};
  scDesc.Width                 = myResulotion.x;
  scDesc.Height                = myResulotion.y;
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
  HR_ASSERT(factory_p->CreateSwapChainForHwnd(
      myGraphicalInterface.commandList4_p, myHwnd, &scDesc, nullptr, nullptr, &swapChain1_p));
  HR_ASSERT(swapChain1_p->QueryInterface(IID_PPV_ARGS(&myGraphicalInterface.swapChain_p)));
  SafeRelease(&swapChain1_p);
  myGraphicalInterface.currentBackbufferIndex =
      myGraphicalInterface.swapChain_p->GetCurrentBackBufferIndex();
  SafeRelease(&factory_p);
  myGraphicalInterface.swapChain_p->GetSourceSize(&myResulotion.x, &myResulotion.y);
}

void MyRenderer::_CreateViewport()
{
  myGraphicalInterface.viewport.Width     = (float)myResulotion.x;
  myGraphicalInterface.viewport.Height    = (float)myResulotion.y;
  myGraphicalInterface.viewport.MinDepth  = D3D12_MIN_DEPTH;
  myGraphicalInterface.viewport.MaxDepth  = D3D12_MAX_DEPTH;
  myGraphicalInterface.scissorRect.right  = (long)INT_MAX;
  myGraphicalInterface.scissorRect.bottom = (long)INT_MAX;
}

void MyRenderer::_CreateFenceAndHandleEvent()
{
  myDevice_p->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&myFence_p));
  myFenceValue  = 1;
  myEventHandle = CreateEvent(0, FALSE, FALSE, 0);
}

void MyRenderer::_CreateRenderTargets()
{
  D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
  dhd.NumDescriptors             = NUM_SWAP_BUFFERS;
  dhd.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

  HR_ASSERT(myDevice_p->CreateDescriptorHeap(
      &dhd, IID_PPV_ARGS(&myGraphicalInterface.renderTargetHeap_p)));

  mySrvUavCbvDescriptorSize =
      myDevice_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

  myGraphicalInterface.renderTargetDescriptorSize =
      myDevice_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

  D3D12_CPU_DESCRIPTOR_HANDLE cdh =
      myGraphicalInterface.renderTargetHeap_p->GetCPUDescriptorHandleForHeapStart();

  for (UINT n = 0; n < NUM_SWAP_BUFFERS; n++)
  {
    HR_ASSERT(myGraphicalInterface.swapChain_p->GetBuffer(
        n, IID_PPV_ARGS(&myGraphicalInterface.renderTargets_pp[n])));
    myDevice_p->CreateRenderTargetView(myGraphicalInterface.renderTargets_pp[n], nullptr, cdh);
    cdh.ptr += myGraphicalInterface.renderTargetDescriptorSize;
  }
}

void MyRenderer::_CreateDepthBuffers()
{
  // Create Depth buffers

  D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
  dhd.NumDescriptors             = NUM_SWAP_BUFFERS;
  dhd.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
  HR_ASSERT(myDevice_p->CreateDescriptorHeap(
      &dhd, IID_PPV_ARGS(&myGraphicalInterface.depthBufferHeap_p)));

  myGraphicalInterface.depthBufferDescriptorSize =
      myDevice_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

  D3D12_HEAP_PROPERTIES heapProp = {};
  heapProp.Type                  = D3D12_HEAP_TYPE_DEFAULT;
  heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

  D3D12_RESOURCE_DESC desc = {};
  desc.DepthOrArraySize    = 1;
  desc.Dimension           = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  desc.Flags               = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
  desc.Format              = DXGI_FORMAT_D32_FLOAT;
  desc.Width               = myResulotion.x;
  desc.Height              = myResulotion.y;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;

  D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
  dsvDesc.Format                        = DXGI_FORMAT_D32_FLOAT;
  dsvDesc.ViewDimension                 = D3D12_DSV_DIMENSION_TEXTURE2D;

  D3D12_CPU_DESCRIPTOR_HANDLE cdh =
      myGraphicalInterface.depthBufferHeap_p->GetCPUDescriptorHandleForHeapStart();

  D3D12_CLEAR_VALUE clearVal  = {};
  clearVal.Format             = DXGI_FORMAT_D32_FLOAT;
  clearVal.DepthStencil.Depth = 1.0f;

  for (uint i = 0; i < NUM_SWAP_BUFFERS; i++)
  {
    HR_ASSERT(myDevice_p->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearVal,
        IID_PPV_ARGS(&myGraphicalInterface.depthBuffers_pp[i])));

    myDevice_p->CreateDepthStencilView(myGraphicalInterface.depthBuffers_pp[i], &dsvDesc, cdh);
    cdh.ptr += myGraphicalInterface.depthBufferDescriptorSize;
  }
}

void MyRenderer::_CreateRootsignatures()
{
  D3D12_ROOT_PARAMETER                rootParams[3] = {};
  std::vector<D3D12_DESCRIPTOR_RANGE> cbvRanges(MAX_ALLOWED_CBV);
  std::vector<D3D12_DESCRIPTOR_RANGE> srvRanges(MAX_ALLOWED_SRV);
  std::vector<D3D12_DESCRIPTOR_RANGE> uavRanges(MAX_ALLOWED_UAV);

  for (uint i = 0; i < MAX_ALLOWED_CBV; i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc            = {};
    rangeDesc.RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    rangeDesc.NumDescriptors                    = 1;
    rangeDesc.RegisterSpace                     = 0;
    rangeDesc.BaseShaderRegister                = i;
    rangeDesc.OffsetInDescriptorsFromTableStart = i;
    cbvRanges[i]                                = rangeDesc;
  }
  for (uint i = 0; i < MAX_ALLOWED_SRV; i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc            = {};
    rangeDesc.RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    rangeDesc.NumDescriptors                    = 1;
    rangeDesc.RegisterSpace                     = 0;
    rangeDesc.BaseShaderRegister                = i;
    rangeDesc.OffsetInDescriptorsFromTableStart = i;
    srvRanges[i]                                = rangeDesc;
  }
  for (uint i = 0; i < MAX_ALLOWED_UAV; i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc            = {};
    rangeDesc.RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
    rangeDesc.NumDescriptors                    = 1;
    rangeDesc.RegisterSpace                     = 0;
    rangeDesc.BaseShaderRegister                = i;
    rangeDesc.OffsetInDescriptorsFromTableStart = i;
    srvRanges[i]                                = rangeDesc;
  }

  D3D12_ROOT_PARAMETER rootParams[3] = {};

  rootParams[0].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[0].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[0].DescriptorTable.NumDescriptorRanges = MAX_ALLOWED_CBV;
  rootParams[0].DescriptorTable.pDescriptorRanges   = cbvRanges.data();

  rootParams[1].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[1].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[1].DescriptorTable.NumDescriptorRanges = MAX_ALLOWED_SRV;
  rootParams[1].DescriptorTable.pDescriptorRanges   = srvRanges.data();

  rootParams[2].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[2].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[2].DescriptorTable.NumDescriptorRanges = MAX_ALLOWED_UAV;
  rootParams[2].DescriptorTable.pDescriptorRanges   = uavRanges.data();

  D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSigDesc = {};
  rootSigDesc.Version                             = D3D_ROOT_SIGNATURE_VERSION_1_0;
  rootSigDesc.Desc_1_0.Flags         = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
  rootSigDesc.Desc_1_0.NumParameters = 3;
  rootSigDesc.Desc_1_0.pParameters   = &rootParams[0];

  D3D12_STATIC_SAMPLER_DESC samplerDesc  = {};
  samplerDesc.Filter                     = D3D12_FILTER_ANISOTROPIC;
  samplerDesc.AddressU                   = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.AddressV                   = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.AddressW                   = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.MaxAnisotropy              = 16;
  samplerDesc.RegisterSpace              = 0;
  samplerDesc.MinLOD                     = -D3D12_FLOAT32_MAX;
  samplerDesc.MaxLOD                     = D3D12_FLOAT32_MAX;
  samplerDesc.MipLODBias                 = 0;
  samplerDesc.ShaderRegister             = 0;
  samplerDesc.ShaderVisibility           = D3D12_SHADER_VISIBILITY_ALL;
  rootSigDesc.Desc_1_0.pStaticSamplers   = &samplerDesc;
  rootSigDesc.Desc_1_0.NumStaticSamplers = 1;

  ID3DBlob* errorBlob_p     = nullptr;
  ID3DBlob* signatureBlob_p = nullptr;

  HR_ASSERT(D3D12SerializeRootSignature(
      &rootSigDesc.Desc_1_0, rootSigDesc.Version, &signatureBlob_p, &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  HR_ASSERT(myDevice_p->CreateRootSignature(0,
                                            signatureBlob_p->GetBufferPointer(),
                                            signatureBlob_p->GetBufferSize(),
                                            IID_PPV_ARGS(&myGraphicalInterface.rootSignature_p)));

  rootSigDesc.Desc_1_0.Flags = D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
  HR_ASSERT(D3D12SerializeRootSignature(
      &rootSigDesc.Desc_1_0, rootSigDesc.Version, &signatureBlob_p, &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  HR_ASSERT(myDevice_p->CreateRootSignature(0,
                                            signatureBlob_p->GetBufferPointer(),
                                            signatureBlob_p->GetBufferSize(),
                                            IID_PPV_ARGS(&myComputeInterface.rootSignature_p)));
}

void MyRenderer::_SetupComputeInterface()
{
  D3D12_COMMAND_QUEUE_DESC desc {};
  desc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
  HR_ASSERT(
      myDevice_p->CreateCommandQueue(&desc, IID_PPV_ARGS(&myComputeInterface.commandQueue_p)));
  HR_ASSERT(myDevice_p->CreateCommandAllocator(
      D3D12_COMMAND_LIST_TYPE_COMPUTE, IID_PPV_ARGS(&myComputeInterface.commandAllocator_p)));
  HR_ASSERT(myDevice_p->CreateCommandList(0,
                                          D3D12_COMMAND_LIST_TYPE_COMPUTE,
                                          myComputeInterface.commandAllocator_p,
                                          nullptr,
                                          IID_PPV_ARGS(&myComputeInterface.commandList4_p)));
  HR_ASSERT(myComputeInterface.commandList4_p->Close());
}

void MyRenderer::_Cleanup() { }

void MyRenderer::_HardWait(ID3D12CommandQueue* commandQueue_p)
{
  commandQueue_p->Signal(myFence_p, myFenceValue);

  if (myFenceValue > myFence_p->GetCompletedValue())
  {
    myFence_p->SetEventOnCompletion(myFenceValue, myEventHandle);
    WaitForMultipleObjects(1, &myEventHandle, TRUE, INFINITE);
  }

  myFenceValue++;
}

void MyRenderer::_SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p,
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