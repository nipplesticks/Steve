#pragma once
#define NOMINMAX
#include "../utility/DMath.h"
#include "../utility/Typedef.h"
#include "../utility/Vector4f.h"
#include "Vertex.h"
#include <d3d12.h>
#include <windows.h>

struct IDXGISwapChain4;

class VertexBuffer;
class IndexBuffer;

class Renderer
{
public:
  Renderer(uint x, uint y, HWND aHwnd);
  ~Renderer();

  void UpdateViewProjection(const DM::Mat4x4& viewProj);

  void BeginFrame();

  void DrawVertexBuffer(const VertexBuffer& vertexBuffer); // Temp
  void DrawVertexAndIndexBuffer(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer); // Temp

  void Clear(const Vector4f& color = Vector4f());

  void EndFrame();

  static ID3D12Device5* GetDevice();

private:
  void _SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p,
                                     ID3D12Resource*            resource_p,
                                     D3D12_RESOURCE_STATES      StateBefore,
                                     D3D12_RESOURCE_STATES      StateAfter);
  void _SetupShaderState();

private:
  static const uint     NUM_SWAP_BUFFERS = 2u;
  static ID3D12Device5* gDevice5_p;
  ID3D12CommandQueue*   myCommandQueue_p = nullptr;

  IDXGISwapChain4* mySwapChain4_p           = nullptr;
  uint             myCurrentBackbufferIndex = 0u;
  D3D12_VIEWPORT   myViewport               = {};
  D3D12_RECT       myScissorRect            = {};

  ID3D12CommandAllocator*     myCommandAllocator_p  = nullptr;
  ID3D12GraphicsCommandList4* myCommandList4_p      = nullptr;
  ID3D12Fence1*               myFence_p             = nullptr;
  HANDLE                      myEventHandle         = nullptr;
  ID3D12DescriptorHeap*       myRenderTargetsHeap_p = nullptr;

  ID3D12RootSignature* myRootSignature_p = nullptr;

  ID3D12PipelineState* myPipelineState_p = nullptr;

  ID3D12Resource*          myVertexBuffer_p   = nullptr;
  D3D12_VERTEX_BUFFER_VIEW myVertexBufferView = {};
  ID3DBlob*                myVertexShader_p   = nullptr;
  ID3DBlob*                myPixelShader_p    = nullptr;

  ID3D12Resource1*      myDepthBuffers_pp[NUM_SWAP_BUFFERS]  = {};
  ID3D12DescriptorHeap* myDepthBufferHeap_p                  = nullptr;
  uint                  myDepthBufferDescriptorSize          = 0;

  ID3D12Resource1*      myRenderTargets_pp[NUM_SWAP_BUFFERS] = {};
  uint                  myRenderTargetDescriptorSize         = 0;
  uint64                myFenceValue                         = 0u;

  ID3D12Resource* myViewProjBuffer_p = nullptr;
};