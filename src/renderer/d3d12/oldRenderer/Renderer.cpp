#include "Renderer.h"
#define NOMINMAX
#include "../../entity/Drawable.h"
#include "../../utility/RenderUtility.h"
#include "../../window/Window.h"
#include "../buffers/ConstantBuffer.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/TextureBuffer.h"
#include "../buffers/VertexBuffer.h"
#include "../mesh/Mesh.h"
#include "ComputationalPipeline.h"
#include "GraphicsPipelineState.h"
#include "ResourceDescriptorHeap.h"
#include "d3dx12.h"
#include <d3dcompiler.h>
#include <dxgi1_6.h> //Only used for initialization of the device and swap chain.

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3dcompiler.lib")

ID3D12Device5*        Renderer::gDevice5_p               = nullptr;
ID3D12DescriptorHeap* Renderer::gUploadHeap_p            = nullptr;
uint                  Renderer::gSrvUavCbvDescriptorSize = 0u;
Renderer*             Renderer::gRenderer_p              = nullptr;

Renderer::Renderer(uint x, uint y, HWND aHwnd)
{
  _createDevice();
  _createCommandInterfaceAndSwapChain(aHwnd);
  _createViewport();
  _createFenceAndHandleEvent();
  _createRenderTargets();
  _createDepthBuffers();
  _setupComputeInterface();
}

Renderer::~Renderer() { }

void Renderer::Init(uint x, uint y, HWND hwnd)
{
  if (!gRenderer_p)
  {
    gRenderer_p = new Renderer(x, y, hwnd);
    gRenderer_p->_InitImgui(hwnd);
  }
}

void Renderer::Release() { }

Renderer* Renderer::GetInstance()
{
  return gRenderer_p;
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

  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHnd2 =
      myDepthBufferHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHnd2.ptr += myCurrentBackbufferIndex * myDepthBufferDescriptorSize;

  myCommandList4_p->OMSetRenderTargets(1, &cpuDescHndl, TRUE, &cpuDescHnd2);
}

void Renderer::UploadTexture(const TextureBuffer& textureBuffer, void* data_p)
{
  ID3D12Resource* tempResource_p = nullptr;

  D3D12_HEAP_PROPERTIES heapProp = {};
  heapProp.Type                  = D3D12_HEAP_TYPE_UPLOAD;
  heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

  D3D12_RESOURCE_DESC texDesc  = textureBuffer.GetResource()->GetDesc();
  UINT64              byteSize = 0;
  gDevice5_p->GetCopyableFootprints(&texDesc, 0, 1, 0, nullptr, nullptr, nullptr, &byteSize);

  D3D12_RESOURCE_DESC desc = {};
  desc.DepthOrArraySize    = 1;
  desc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
  desc.Flags               = D3D12_RESOURCE_FLAG_NONE;
  desc.Format              = DXGI_FORMAT_UNKNOWN;
  desc.Height              = 1;
  desc.Width               = byteSize;
  desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;

  HR_ASSERT(gDevice5_p->CreateCommittedResource(&heapProp,
                                                D3D12_HEAP_FLAG_NONE,
                                                &desc,
                                                D3D12_RESOURCE_STATE_GENERIC_READ,
                                                nullptr,
                                                IID_PPV_ARGS(&tempResource_p)));

  D3D12_SUBRESOURCE_DATA srdDesc = {};
  srdDesc.pData                  = data_p;
  srdDesc.RowPitch               = textureBuffer.GetRowPitch();
  srdDesc.SlicePitch             = srdDesc.RowPitch * textureBuffer.GetHeight();

  myTextureUploadAllocator_p->Reset();
  myTextureUploadCommandList4_p->Reset(myTextureUploadAllocator_p, nullptr);

  {
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Transition.pResource   = textureBuffer.GetResource();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST;
    barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    myTextureUploadCommandList4_p->ResourceBarrier(1, &barrier);
  }

  UpdateSubresources(myTextureUploadCommandList4_p,
                     textureBuffer.GetResource(),
                     tempResource_p,
                     0,
                     0,
                     1,
                     &srdDesc);

  {
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Transition.pResource   = textureBuffer.GetResource();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_GENERIC_READ;
    barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    myTextureUploadCommandList4_p->ResourceBarrier(1, &barrier);
  }
  myTextureUploadCommandList4_p->Close();
  myCommandQueue_p->ExecuteCommandLists(
      1, reinterpret_cast<ID3D12CommandList**>(&myTextureUploadCommandList4_p));

  _HardWait(myCommandQueue_p);
}

void Renderer::ChangeResourceStateForCompute(ID3D12Resource*       resource_p,
                                             D3D12_RESOURCE_STATES before,
                                             D3D12_RESOURCE_STATES after)
{
  myTextureUploadAllocator_p->Reset();
  myTextureUploadCommandList4_p->Reset(myTextureUploadAllocator_p, nullptr);

  D3D12_RESOURCE_BARRIER barrier = {};
  barrier.Transition.pResource   = resource_p;
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = before;
  barrier.Transition.StateAfter  = after;;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  myTextureUploadCommandList4_p->ResourceBarrier(1, &barrier);

  myTextureUploadCommandList4_p->Close();
  myCommandQueue_p->ExecuteCommandLists(
      1, reinterpret_cast<ID3D12CommandList**>(&myTextureUploadCommandList4_p));
  _HardWait(myCommandQueue_p);
}

void Renderer::ChangeResourceStateForGraphic(ID3D12Resource*       resourse_p,
                                             D3D12_RESOURCE_STATES before,
                                             D3D12_RESOURCE_STATES after)
{
  D3D12_RESOURCE_BARRIER barrier = {};
  barrier.Transition.pResource   = resourse_p;
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = before;
  barrier.Transition.StateAfter  = after;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  myCommandList4_p->ResourceBarrier(1, &barrier);
}

void Renderer::Draw(const VertexBuffer&           vertexBuffer,
                    const IndexBuffer&            indexBuffer,
                    const ResourceDescriptorHeap& rh,
                    const GraphicsPipelineState&  pipelineState)
{
  myCommandList4_p->SetPipelineState(pipelineState.GetPipelineState());
  myCommandList4_p->SetGraphicsRootSignature(pipelineState.GetRootSignature());

  myCommandList4_p->RSSetViewports(1, &myViewport);
  myCommandList4_p->RSSetScissorRects(1, &myScissorRect);

  myCommandList4_p->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  myCommandList4_p->IASetVertexBuffers(0, 1, &vertexBuffer.GetVBV());
  myCommandList4_p->IASetIndexBuffer(&indexBuffer.GetIBV());

  ID3D12DescriptorHeap* arr[1] = {rh.GetDescriptorHeap()};

  myCommandList4_p->SetDescriptorHeaps(1, arr);
  if (rh.HasCbvs())
    myCommandList4_p->SetGraphicsRootDescriptorTable(0, rh.GetCbvHeapLocationStart());
  if (rh.HasSrvs())
    myCommandList4_p->SetGraphicsRootDescriptorTable(1, rh.GetSrvHeapLocationStart());
  if (rh.HasUavs())
    myCommandList4_p->SetGraphicsRootDescriptorTable(2, rh.GetUavBufferHeapLocationStart());

  myCommandList4_p->DrawIndexedInstanced(indexBuffer.GetIndexCount(), 1, 0, 0, 0);
}

void Renderer::BeginCompute()
{
  myComputeInterface.commandAllocator_p->Reset();
  myComputeInterface.commandList4_p->Reset(myComputeInterface.commandAllocator_p, nullptr);
}

void Renderer::Compute(const ComputationalPipeline&  pipeline,
                       const ResourceDescriptorHeap& rh,
                       const DM::Vec3i&              threads)
{
  myComputeInterface.commandList4_p->SetPipelineState(pipeline.GetPipelineState());
  myComputeInterface.commandList4_p->SetComputeRootSignature(pipeline.GetRootSignature());
  ID3D12DescriptorHeap* arr[1] = {rh.GetDescriptorHeap()};
  myComputeInterface.commandList4_p->SetDescriptorHeaps(1, arr);
  if (rh.HasCbvs())
    myComputeInterface.commandList4_p->SetComputeRootDescriptorTable(
        0, rh.GetCbvHeapLocationStart());
  if (rh.HasSrvs())
    myComputeInterface.commandList4_p->SetComputeRootDescriptorTable(
        1, rh.GetSrvHeapLocationStart());
  if (rh.HasUavs())
    myComputeInterface.commandList4_p->SetComputeRootDescriptorTable(
        2, rh.GetUavBufferHeapLocationStart());

  myComputeInterface.commandList4_p->Dispatch(threads.x, threads.y, threads.z);
}

void Renderer::EndCompute()
{
  HR_ASSERT(myComputeInterface.commandList4_p->Close());

  // Send to queue

  myComputeInterface.commandQueue_p->ExecuteCommandLists(
      1, reinterpret_cast<ID3D12CommandList**>(&myComputeInterface.commandList4_p));
  _HardWait(myComputeInterface.commandQueue_p);
}

void Renderer::Clear(const Vector4f& color)
{
  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHndl =
      myRenderTargetsHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHndl.ptr += myCurrentBackbufferIndex * myRenderTargetDescriptorSize;
  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHnd2 =
      myDepthBufferHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHnd2.ptr += myCurrentBackbufferIndex * myDepthBufferDescriptorSize;

  myCommandList4_p->ClearDepthStencilView(cpuDescHnd2, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
  myCommandList4_p->ClearRenderTargetView(cpuDescHndl, (FLOAT*)&color, 0, NULL);
}

void Renderer::DrawImgui()
{
  ImGui::Render();
  myCommandList4_p->SetDescriptorHeaps(1, &myImguiDescHeap_p);
  ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), myCommandList4_p);
}

void Renderer::Flush()
{
  for (auto& gps : Drawable::DRAW_QUEUE)
  {
    Drawable::DrawQueue* drawQueue     = &gps.second;
    uint                 nrOfDrawables = drawQueue->nrOfElements;
    for (uint i = 0; i < nrOfDrawables; i++)
    {
      Drawable*                         d_p         = drawQueue->queue[i];
      Mesh*                             mesh_p      = d_p->GetMesh();
      const ResourceDescriptorHeap&     rdh         = d_p->GetResourceDescHeap();
      const std::vector<Mesh::Buffers>& meshBuffers = mesh_p->GetBuffers();

      for (auto& buffer : meshBuffers)
      {
        Draw(buffer.vb, buffer.ib, rdh, *gps.first);
      }
    }
    drawQueue->Clear();
  }
}

void Renderer::EndFrame()
{
  Flush();
  DrawImgui();
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

  _HardWait(myCommandQueue_p);

  myCurrentBackbufferIndex = mySwapChain4_p->GetCurrentBackBufferIndex();
}

ID3D12Device5* Renderer::GetDevice()
{
  return gDevice5_p;
}

ID3D12DescriptorHeap* Renderer::GetUploadHeap()
{
  return gUploadHeap_p;
}

uint Renderer::GetSrvUavCbvDescriptorSize()
{
  return gSrvUavCbvDescriptorSize;
}

void Renderer::_HardWait(ID3D12CommandQueue* commandQueue_p)
{ // Hard wait
  commandQueue_p->Signal(myFence_p, myFenceValue);

  if (myFenceValue > myFence_p->GetCompletedValue())
  {
    myFence_p->SetEventOnCompletion(myFenceValue, myEventHandle);
    WaitForMultipleObjects(1, &myEventHandle, TRUE, INFINITE);
  }

  myFenceValue++;
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

void Renderer::_InitImgui(HWND hwnd)
{
  D3D12_DESCRIPTOR_HEAP_DESC desc = {};
  desc.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  desc.NumDescriptors             = 1;
  desc.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  HR_ASSERT(gDevice5_p->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&myImguiDescHeap_p)));

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  ImGui::StyleColorsDark();
  ImGui_ImplWin32_Init(hwnd);
  ImGui_ImplDX12_Init(Renderer::GetDevice(),
                      NUM_SWAP_BUFFERS,
                      DXGI_FORMAT_R8G8B8A8_UNORM,
                      myImguiDescHeap_p,
                      myImguiDescHeap_p->GetCPUDescriptorHandleForHeapStart(),
                      myImguiDescHeap_p->GetGPUDescriptorHandleForHeapStart());
  Window::IMGUI_READY = true;
}

void Renderer::_createDevice()
{
  // Init device

  ID3D12Debug* debugController_p = nullptr;

  if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_p))))
  {
    debugController_p->EnableDebugLayer();/*
    ID3D12Debug1* debugcontroller1_p;
    debugController_p->QueryInterface(IID_PPV_ARGS(&debugcontroller1_p));
    debugcontroller1_p->SetEnableGPUBasedValidation(true);*/
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
    if (SUCCEEDED(
            D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device5), nullptr)))
    {
      break;
    }

    SafeRelease(&adapter_p);
  }

  if (adapter_p)
  {
    HRESULT hr = S_OK;
    //Create the actual device.
    if (SUCCEEDED(
            hr = D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&gDevice5_p))))
    {
      int lol = 123;
    }

    SafeRelease(&adapter_p);
  }
  else
  {
    //Create warp device if no adapter was found.
    factory_p->EnumWarpAdapter(IID_PPV_ARGS(&adapter_p));
    D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&gDevice5_p));
  }

  SafeRelease(&factory_p);
}

void Renderer::_createCommandInterfaceAndSwapChain(HWND aHwnd)
{
  // Create Command interfaces And Swap Chain

  //Describe and create the command queue.
  D3D12_COMMAND_QUEUE_DESC cqd = {};
  HR_ASSERT(gDevice5_p->CreateCommandQueue(&cqd, IID_PPV_ARGS(&myCommandQueue_p)));

  //Create command allocator. The command allocator object corresponds
  //to the underlying allocations in which GPU commands are stored.
  HR_ASSERT(gDevice5_p->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                               IID_PPV_ARGS(&myCommandAllocator_p)));

  HR_ASSERT(gDevice5_p->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                               IID_PPV_ARGS(&myTextureUploadAllocator_p)));

  //Create command list.
  HR_ASSERT(gDevice5_p->CreateCommandList(0,
                                          D3D12_COMMAND_LIST_TYPE_DIRECT,
                                          myCommandAllocator_p,
                                          nullptr,
                                          IID_PPV_ARGS(&myCommandList4_p)));
  //Create command list.
  HR_ASSERT(gDevice5_p->CreateCommandList(0,
                                          D3D12_COMMAND_LIST_TYPE_DIRECT,
                                          myTextureUploadAllocator_p,
                                          nullptr,
                                          IID_PPV_ARGS(&myTextureUploadCommandList4_p)));

  //Command lists are created in the recording state. Since there is nothing to
  //record right now and the main loop expects it to be closed, we close it.
  HR_ASSERT(myCommandList4_p->Close());
  HR_ASSERT(myTextureUploadCommandList4_p->Close());

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

void Renderer::_createViewport()
{
  // Setup Viewport
  uint width  = 0u;
  uint height = 0u;
  mySwapChain4_p->GetSourceSize(&width, &height);
  myViewport.Width    = (float)width;
  myViewport.Height   = (float)height;
  myViewport.MinDepth = D3D12_MIN_DEPTH;
  myViewport.MaxDepth = D3D12_MAX_DEPTH;

  myScissorRect.right  = (long)INT_MAX;
  myScissorRect.bottom = (long)INT_MAX;
}

void Renderer::_createFenceAndHandleEvent()
{
  // Create Fence And Event Handle
  gDevice5_p->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&myFence_p));
  myFenceValue = 1;
  //Create an event handle to use for GPU synchronization.
  myEventHandle = CreateEvent(0, false, false, 0);
}

void Renderer::_createRenderTargets()
{
  // Create Render Targets

  //Create descriptor heap for render target views.
  D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
  dhd.NumDescriptors             = NUM_SWAP_BUFFERS;
  dhd.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

  HRESULT hr = gDevice5_p->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(&myRenderTargetsHeap_p));

  gSrvUavCbvDescriptorSize =
      gDevice5_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

  //Create resources for the render targets.
  myRenderTargetDescriptorSize =
      gDevice5_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  D3D12_CPU_DESCRIPTOR_HANDLE cdh = myRenderTargetsHeap_p->GetCPUDescriptorHandleForHeapStart();

  //One RTV for each frame.
  for (UINT n = 0; n < NUM_SWAP_BUFFERS; n++)
  {
    hr = mySwapChain4_p->GetBuffer(n, IID_PPV_ARGS(&myRenderTargets_pp[n]));
    gDevice5_p->CreateRenderTargetView(myRenderTargets_pp[n], nullptr, cdh);
    cdh.ptr += myRenderTargetDescriptorSize;
  }
}

void Renderer::_createDepthBuffers()
{
  // Create Depth buffers

  D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
  dhd.NumDescriptors             = NUM_SWAP_BUFFERS;
  dhd.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
  HRESULT hr = gDevice5_p->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(&myDepthBufferHeap_p));

  myDepthBufferDescriptorSize =
      gDevice5_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

  D3D12_HEAP_PROPERTIES heapProp = {};
  heapProp.Type                  = D3D12_HEAP_TYPE_DEFAULT;
  heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;
  uint width                     = 0u;
  uint height                    = 0u;

  mySwapChain4_p->GetSourceSize(&width, &height);

  D3D12_RESOURCE_DESC desc = {};
  desc.DepthOrArraySize    = 1;
  desc.Dimension           = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  desc.Flags               = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
  desc.Format              = DXGI_FORMAT_D32_FLOAT;
  desc.Width               = width;
  desc.Height              = height;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;

  D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
  dsvDesc.Format                        = DXGI_FORMAT_D32_FLOAT;
  dsvDesc.ViewDimension                 = D3D12_DSV_DIMENSION_TEXTURE2D;

  D3D12_CPU_DESCRIPTOR_HANDLE cdh = myDepthBufferHeap_p->GetCPUDescriptorHandleForHeapStart();

  D3D12_CLEAR_VALUE clearVal  = {};
  clearVal.Format             = DXGI_FORMAT_D32_FLOAT;
  clearVal.DepthStencil.Depth = 1.0f;

  for (uint i = 0; i < NUM_SWAP_BUFFERS; i++)
  {
    HR_ASSERT(gDevice5_p->CreateCommittedResource(&heapProp,
                                                  D3D12_HEAP_FLAG_NONE,
                                                  &desc,
                                                  D3D12_RESOURCE_STATE_DEPTH_WRITE,
                                                  &clearVal,
                                                  IID_PPV_ARGS(&myDepthBuffers_pp[i])));

    gDevice5_p->CreateDepthStencilView(myDepthBuffers_pp[i], &dsvDesc, cdh);
    cdh.ptr += myDepthBufferDescriptorSize;
  }
}

void Renderer::_setupComputeInterface()
{
  D3D12_COMMAND_QUEUE_DESC desc {};
  desc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
  HR_ASSERT(
      gDevice5_p->CreateCommandQueue(&desc, IID_PPV_ARGS(&myComputeInterface.commandQueue_p)));
  HR_ASSERT(gDevice5_p->CreateCommandAllocator(
      D3D12_COMMAND_LIST_TYPE_COMPUTE, IID_PPV_ARGS(&myComputeInterface.commandAllocator_p)));
  HR_ASSERT(gDevice5_p->CreateCommandList(0,
                                          D3D12_COMMAND_LIST_TYPE_COMPUTE,
                                          myComputeInterface.commandAllocator_p,
                                          nullptr,
                                          IID_PPV_ARGS(&myComputeInterface.commandList4_p)));
  myComputeInterface.commandList4_p->Close();
}
