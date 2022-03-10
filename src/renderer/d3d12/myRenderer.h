#pragma once

#define MAX_NUMBER_OF_SUB_RESOURCES 256

#include "../../utility/DMath.h"
#include "../../utility/Typedef.h"
#include "../buffers/Rendertarget.h"
#include "../buffers/VertexBuffer.h"
#include <d3d12.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx12.h>
#include <imgui/imgui_impl_win32.h>
#include <windows.h>
#include "../d3d12/ResourceDescriptorHeap.h"

struct IDXGISwapChain4;
class Resource;
class ComputationalPipeline;
class ResourceDescriptorHeap;
class GraphicsPipelineState;

class MyRenderer
{
private:
  static MyRenderer gRenderer;
  MyRenderer()  = default;
  ~MyRenderer() = default;

public:
  static bool        ENABLE_DEBUG_LAYER;
  static bool        ENABLE_DEBUG_CONTROLLER;
  static uint        MAX_ALLOWED_CBV;
  static uint        MAX_ALLOWED_SRV;
  static uint        MAX_ALLOWED_UAV;
  static void        Init(HWND hwnd, uint resX = 0, uint resY = 0);
  static void        Release();
  static MyRenderer* GetInstance();

  void BeginFrame();
  void Clear(const DM::Vec4f& color = DM::Vec4f());
  void FlushDrawQueue();
  void Draw(Resource*               vertexBuffer_p,
            Resource*               indexBuffer_p,
            ResourceDescriptorHeap* resourceDescHeap_p,
            GraphicsPipelineState*  graphicalPipelineState_p);

  void EndFrame();
  void BeginCompute();
  void Compute(ComputationalPipeline*  pipeline_p,
               ResourceDescriptorHeap* resourceDescHeap_p,
               const DM::Vec3u&        numThreads);
  void EndCompute();
  void DrawImgui();

  void SetResolution(uint resX, uint resY);
  void ResourceUpdate(void*                 data_p,
                      uint64                sizeofData,
                      uint64                offset,
                      D3D12_RESOURCE_STATES stateAfter,
                      Resource*             resource_p);

  ID3D12RootSignature* GetGraphicalRootSignature();
  ID3D12RootSignature* GetComputeRootSignature();

  ID3D12Device5*        GetDevice() const;
  ID3D12DescriptorHeap* GetUploadHeap() const;
  uint                  GetSrvUavCbvDescritorSize() const;
  void                  ChangeResourceStateGraphic(ID3D12Resource*       resource_p,
                                                   D3D12_RESOURCE_STATES stateBefore,
                                                   D3D12_RESOURCE_STATES stateAfter);
  void                  ChangeResourceStateCompute(ID3D12Resource*       resource_p,
                                                   D3D12_RESOURCE_STATES stateBefore,
                                                   D3D12_RESOURCE_STATES stateAfter);
  void                  ChangeResourceStateNow(ID3D12Resource*       resource_p,
                                               D3D12_RESOURCE_STATES stateBefore,
                                               D3D12_RESOURCE_STATES stateAfter);

private:
  void _Init(uint resX, uint resY, HWND hwnd);
  void _InitImgui();
  void _CreateDevice();
  void _CreateCommandInterfaceAndSwapChain();
  void _CreateViewport();
  void _CreateFenceAndHandleEvent();
  void _CreateRenderTargets();
  void _CreateDepthBuffers();
  void _CreateRootsignatures();
  void _SetupComputeInterface();
  void _CreateDeferredQuad();
  void _Cleanup();
  void _HardWait(ID3D12CommandQueue* commandQueue_p);
  void _SetResourceTransitionBarrier(ID3D12GraphicsCommandList* commandList_p,
                                     ID3D12Resource*            resource_p,
                                     D3D12_RESOURCE_STATES      StateBefore,
                                     D3D12_RESOURCE_STATES      StateAfter);

private:
  static const uint           NUM_SWAP_BUFFERS               = 2u;
  ID3D12Device5*              myDevice_p                     = nullptr;
  ID3D12DescriptorHeap*       myUploadHeap_p                 = nullptr;
  uint                        mySrvUavCbvDescriptorSize      = 0u;
  ID3D12Fence1*               myFence_p                      = nullptr;
  HANDLE                      myEventHandle                  = nullptr;
  ID3D12CommandAllocator*     myResourceUpdateAllocator_p    = nullptr;
  ID3D12GraphicsCommandList4* myResourceUpdateCommandList4_p = nullptr;
  ID3D12CommandQueue*         myResourceUpdateCommandQueue_p = nullptr;
  uint64                      myFenceValue                   = 0u;
  HWND                        myHwnd                         = 0;
  DM::Vec2u                   myResulotion;

  struct
  {
    ID3D12RootSignature*        rootSignature_p                    = nullptr;
    ID3D12CommandQueue*         commandQueue_p                     = nullptr;
    ID3D12CommandAllocator*     commandAllocator_p                 = nullptr;
    ID3D12GraphicsCommandList4* commandList4_p                     = nullptr;
    IDXGISwapChain4*            swapChain_p                        = nullptr;
    ID3D12DescriptorHeap*       renderTargetHeap_p                 = nullptr;
    ID3D12DescriptorHeap*       deferredRenderTargetsHeap_p        = nullptr;
    ID3D12DescriptorHeap*       depthBufferHeap_p                  = nullptr;
    ID3D12DescriptorHeap*       imguiDescHeap_p                    = nullptr;
    ID3D12Resource1*            depthBuffers_pp[NUM_SWAP_BUFFERS]  = {};
    ID3D12Resource1*            renderTargets_pp[NUM_SWAP_BUFFERS] = {};
    D3D12_VIEWPORT              viewport                           = {};
    D3D12_RECT                  scissorRect                        = {};
    uint                        currentBackbufferIndex             = 0u;
    uint                        renderTargetDescriptorSize         = 0u;
    uint                        depthBufferDescriptorSize          = 0u;
    VertexBuffer                deferredQuad;
    RenderTarget
        deferredRenderTargets[NUM_SWAP_BUFFERS]
                             [RenderTarget::RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES];
    ResourceDescriptorHeap deferredResourceDescHeap[NUM_SWAP_BUFFERS];
  } myGraphicalInterface;

  struct
  {
    ID3D12RootSignature*        rootSignature_p    = nullptr;
    ID3D12CommandQueue*         commandQueue_p     = nullptr;
    ID3D12CommandAllocator*     commandAllocator_p = nullptr;
    ID3D12GraphicsCommandList4* commandList4_p     = nullptr;
  } myComputeInterface;
};