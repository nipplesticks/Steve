#pragma once

#include <windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "../utility/Typedef.h"
#include "../utility/Vector4f.h"

struct IDXGISwapChain4;

struct Vertex
{
  DirectX::XMFLOAT4A position;
  DirectX::XMFLOAT4A color;
  DirectX::XMFLOAT2A uv;
};

static DirectX::XMFLOAT4A gTriangle[]
{
  {-0.5f, -0.5f, 0.0f, 1.0f},
  {0.5f, 0.5f, 0.0f, 1.0f},
  {-0.5f, 0.5f, 0.0f, 1.0f}
};

class Renderer
{
public:
  Renderer(uint x, uint y, HWND aHwnd);
  ~Renderer();

  void BeginFrame();

  void DrawTriangle();

  void Clear(const Vector4f& color = Vector4f());

  void EndFrame();

private:
  void _SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p, ID3D12Resource* resource_p,
    D3D12_RESOURCE_STATES StateBefore, D3D12_RESOURCE_STATES StateAfter);
  void _SetupVertexBuffer();


private:
  static const uint NUM_SWAP_BUFFERS = 2u;
  ID3D12Device5* myDevice5_p = nullptr;
  ID3D12CommandQueue* myCommandQueue_p = nullptr;

  IDXGISwapChain4* mySwapChain4_p = nullptr;
  D3D12_VIEWPORT myViewport = {};
  D3D12_RECT myScissorRect = {};

  ID3D12CommandAllocator* myCommandAllocator_p = nullptr;
  ID3D12GraphicsCommandList4* myCommandList4_p = nullptr;
  ID3D12Fence1* myFence_p = nullptr;
  HANDLE myEventHandle = nullptr;
  ID3D12DescriptorHeap* myRenderTargetsHeap_p = nullptr;

  ID3D12RootSignature* myRootSignature_p = nullptr;

  ID3D12PipelineState* myPipelineState_p = nullptr;

  ID3D12Resource* myVertexBuffer_p = nullptr;
  D3D12_VERTEX_BUFFER_VIEW myVertexBufferView = {};
  ID3DBlob* myVertexShader_p = nullptr;
  ID3DBlob* myPixelShader_p = nullptr;

  ID3D12Resource1* myRenderTargets_pp[NUM_SWAP_BUFFERS] = {};
  uint myRenderTargetDescriptorSize = 0;
  uint64 myFenceValue = 0u;
};