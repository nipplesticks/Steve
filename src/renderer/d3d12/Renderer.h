#pragma once
#define NOMINMAX
#include "../../utility/DMath.h"
#include "../../utility/Typedef.h"
#include "../../utility/Vector4f.h"
#include "../mesh/Vertex.h"
#include <d3d12.h>
#include <windows.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx12.h>
#include <imgui/imgui_impl_win32.h>

struct IDXGISwapChain4;

class VertexBuffer;
class IndexBuffer;
class TextureBuffer;
class ConstantBuffer;
class GraphicsPipelineState;
class ResourceDescriptorHeap;

class Renderer
{
private:
  static Renderer* gRenderer_p;
  Renderer(uint x, uint y, HWND aHwnd);
  ~Renderer();
public:
  static void Init(uint x, uint y, HWND hwnd);
  static void Release();
  static Renderer* GetInstance();


  void BeginFrame();

  void UploadTexture(const TextureBuffer& textureBuffer, void* data_p);

  void Draw(const VertexBuffer&           vertexBuffer,
            const IndexBuffer&            indexBuffer,
            const ResourceDescriptorHeap& rh,
            const GraphicsPipelineState& pipelineState);


  void Clear(const Vector4f& color = Vector4f());

  void DrawImgui();

  void Flush();

  void EndFrame();

  static ID3D12Device5*        GetDevice();
  static ID3D12DescriptorHeap* GetUploadHeap();
  static uint                  GetSrvUavCbvDescriptorSize();

private:
  void _HardWait();
  void _SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p,
                                     ID3D12Resource*            resource_p,
                                     D3D12_RESOURCE_STATES      StateBefore,
                                     D3D12_RESOURCE_STATES      StateAfter);
  void _InitImgui(HWND hwnd);
  void _createDevice();
  void _createCommandInterfaceAndSwapChain(HWND aHwnd);
  void _createViewport();
  void _createFenceAndHandleEvent();
  void _createRenderTargets();
  void _createDepthBuffers();
  void _setupComputeInterface();

private:
  static const uint            NUM_SWAP_BUFFERS = 2u;
  static ID3D12Device5*        gDevice5_p;
  static ID3D12DescriptorHeap* gUploadHeap_p;
  static uint                  gSrvUavCbvDescriptorSize;

  ID3D12CommandQueue* myCommandQueue_p = nullptr;
  struct
  {
    ID3D12CommandQueue* commandQueue_p = nullptr;
    ID3D12CommandAllocator* commandAllocator_p = nullptr;
    ID3D12GraphicsCommandList4* commandList4_p     = nullptr;
  } myComputeInterface;
  

  IDXGISwapChain4* mySwapChain4_p           = nullptr;
  uint             myCurrentBackbufferIndex = 0u;
  D3D12_VIEWPORT   myViewport               = {};
  D3D12_RECT       myScissorRect            = {};

  ID3D12CommandAllocator*     myCommandAllocator_p  = nullptr;
  ID3D12GraphicsCommandList4* myCommandList4_p      = nullptr;
  ID3D12Fence1*               myFence_p             = nullptr;
  HANDLE                      myEventHandle         = nullptr;
  ID3D12DescriptorHeap*       myRenderTargetsHeap_p = nullptr;

  ID3D12CommandAllocator*     myTextureUploadAllocator_p    = nullptr;
  ID3D12GraphicsCommandList4* myTextureUploadCommandList4_p = nullptr;

  ID3D12Resource1*      myDepthBuffers_pp[NUM_SWAP_BUFFERS] = {};
  ID3D12DescriptorHeap* myDepthBufferHeap_p                 = nullptr;
  uint                  myDepthBufferDescriptorSize         = 0u;

  ID3D12Resource1* myRenderTargets_pp[NUM_SWAP_BUFFERS] = {};
  uint             myRenderTargetDescriptorSize         = 0u;
  uint64           myFenceValue                         = 0u;

  uint mySrvUavCbvDescriptorSize = 0u;

  ID3D12DescriptorHeap* myImguiDescHeap_p = nullptr;

};