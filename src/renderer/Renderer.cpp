#include "Renderer.h"

#include <dxgi1_6.h> //Only used for initialization of the device and swap chain.
#include <d3dcompiler.h>

#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "d3dcompiler.lib")

template<class Interface>
inline void SafeRelease(
  Interface** ppInterfaceToRelease)
{
  if (*ppInterfaceToRelease != NULL)
  {
    (*ppInterfaceToRelease)->Release();

    (*ppInterfaceToRelease) = NULL;
  }
}

Renderer::Renderer(uint x, uint y, HWND aHwnd)
{
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
      if (SUCCEEDED(D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device5), nullptr)))
      {
        break;
      }

      SafeRelease(&adapter_p);
    }

    if (adapter_p)
    {
      HRESULT hr = S_OK;
      //Create the actual device.
      if (SUCCEEDED(hr = D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&myDevice5_p))))
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
    hr = myDevice5_p->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&myCommandAllocator_p));

    //Create command list.
    hr = myDevice5_p->CreateCommandList(
      0,
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
    scDesc.Width = 0;
    scDesc.Height = 0;
    scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.Stereo = FALSE;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.BufferCount = NUM_SWAP_BUFFERS;
    scDesc.Scaling = DXGI_SCALING_NONE;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scDesc.Flags = 0;
    scDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

    IDXGISwapChain1* swapChain1_p = nullptr;
    if (SUCCEEDED(factory_p->CreateSwapChainForHwnd(
      myCommandQueue_p,
      aHwnd,
      &scDesc,
      nullptr,
      nullptr,
      &swapChain1_p)))
    {
      if (SUCCEEDED(swapChain1_p->QueryInterface(IID_PPV_ARGS(&mySwapChain4_p))))
      {
        swapChain1_p->Release();
      }
    }

    SafeRelease(&factory_p);
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
    dhd.NumDescriptors = NUM_SWAP_BUFFERS;
    dhd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

    HRESULT hr = myDevice5_p->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(&myRenderTargetsHeap_p));

    //Create resources for the render targets.
    myRenderTargetDescriptorSize = myDevice5_p->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE cdh = myRenderTargetsHeap_p->GetCPUDescriptorHandleForHeapStart();

    //One RTV for each frame.
    for (UINT n = 0; n < NUM_SWAP_BUFFERS; n++)
    {
      hr = mySwapChain4_p->GetBuffer(n, IID_PPV_ARGS(&myRenderTargets_pp[n]));
      myDevice5_p->CreateRenderTargetView(myRenderTargets_pp[n], nullptr, cdh);
      cdh.ptr += myRenderTargetDescriptorSize;
    }
  }
}

Renderer::~Renderer()
{
}

void Renderer::Clear(const Vector4f& color)
{
  // Clear Rendertarget
  myCommandAllocator_p->Reset();
  myCommandList4_p->Reset(myCommandAllocator_p, nullptr);
  uint backBufferIdx = mySwapChain4_p->GetCurrentBackBufferIndex();

  SetResourceTransitionBarrier(myCommandList4_p,
    myRenderTargets_pp[backBufferIdx],
    D3D12_RESOURCE_STATE_PRESENT,
    D3D12_RESOURCE_STATE_RENDER_TARGET);

  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHndl = myRenderTargetsHeap_p->GetCPUDescriptorHandleForHeapStart();
  cpuDescHndl.ptr += backBufferIdx * myRenderTargetDescriptorSize;

  myCommandList4_p->OMSetRenderTargets(1, &cpuDescHndl, TRUE, NULL);
  myCommandList4_p->ClearRenderTargetView(cpuDescHndl, (FLOAT*)&color, 0, NULL);

  SetResourceTransitionBarrier(myCommandList4_p,
    myRenderTargets_pp[backBufferIdx],
    D3D12_RESOURCE_STATE_RENDER_TARGET,
    D3D12_RESOURCE_STATE_PRESENT);

  myCommandList4_p->Close();

  // Send to queue
  myCommandQueue_p->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList**>(&myCommandList4_p));

  // Hard wait
  myCommandQueue_p->Signal(myFence_p, myFenceValue);

  if (myFenceValue > myFence_p->GetCompletedValue())
  {
    myFence_p->SetEventOnCompletion(myFenceValue, myEventHandle);
    WaitForMultipleObjects(1, &myEventHandle, TRUE, INFINITE);
  }

  myFenceValue++;

  // Present
  mySwapChain4_p->Present(0, 0);
}

void Renderer::SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p, ID3D12Resource* resource_p, D3D12_RESOURCE_STATES StateBefore, D3D12_RESOURCE_STATES StateAfter)
{
  D3D12_RESOURCE_BARRIER barrierDesc = {};

  barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrierDesc.Transition.pResource = resource_p;
  barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrierDesc.Transition.StateBefore = StateBefore;
  barrierDesc.Transition.StateAfter = StateAfter;

  commandList_p->ResourceBarrier(1, &barrierDesc);
}
