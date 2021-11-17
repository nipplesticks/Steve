#pragma once

#include <windows.h>
#include <d3d12.h>
#include "../utility/Typedef.h"
#include "../utility/Vector4f.h"

class IDXGISwapChain4;

class Renderer
{
public:
  Renderer(uint x, uint y, HWND aHwnd);
  ~Renderer();

  void Clear(const Vector4f& color = Vector4f());

private:
  void SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p, ID3D12Resource* resource_p,
    D3D12_RESOURCE_STATES StateBefore, D3D12_RESOURCE_STATES StateAfter);

private:
  static const uint NUM_SWAP_BUFFERS = 2u;
  ID3D12Device5* myDevice5_p = nullptr;
  ID3D12CommandQueue* myCommandQueue_p = nullptr;
  IDXGISwapChain4* mySwapChain4_p = nullptr;
  ID3D12CommandAllocator* myCommandAllocator_p = nullptr;
  ID3D12GraphicsCommandList4* myCommandList4_p = nullptr;
  ID3D12Fence1* myFence_p = nullptr;
  HANDLE myEventHandle = nullptr;
  ID3D12DescriptorHeap* myRenderTargetsHeap_p = nullptr;

  ID3D12Resource1* myRenderTargets_pp[NUM_SWAP_BUFFERS] = {};
  uint myRenderTargetDescriptorSize = 0;
  uint64 myFenceValue = 0u;

};