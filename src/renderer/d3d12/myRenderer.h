#pragma once

#include "../../utility/DMath.h"
#include "../../utility/Typedef.h"
#include <d3d12.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx12.h>
#include <imgui/imgui_impl_win32.h>
#include <windows.h>

struct IDXGISwapChain4;
class Resource;

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

  void BeginFrame(const DM::Vec4f& color = DM::Vec4f());
  void EndFrame();
  void BeginCompute();
  void EndCompute();
  void DrawImgui();

  void SetResolution(uint resX, uint resY);
  void ResourceUpdate(void* data_p, Resource* resource_p, D3D12_RESOURCE_STATES stateAfter);

  ID3D12Device5*        GetDevice() const;
  ID3D12DescriptorHeap* GetUploadHeap() const;
  uint                  GetSrvUavCbvDescritorSize() const;
  void                  ChangeResourceStateGraphic(ID3D12Resource*       resource_p,
                                            D3D12_RESOURCE_STATES StateBefore,
                                            D3D12_RESOURCE_STATES StateAfter);
  void                  ChangeResourceStateCompute(ID3D12Resource*       resource_p,
                                                   D3D12_RESOURCE_STATES StateBefore,
                                                   D3D12_RESOURCE_STATES StateAfter);
  void                  ChangeResourceStateNow(ID3D12Resource*       resource_p,
                                               D3D12_RESOURCE_STATES StateBefore,
                                               D3D12_RESOURCE_STATES StateAfter);

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
    ID3D12DescriptorHeap*       depthBufferHeap_p                  = nullptr;
    ID3D12DescriptorHeap*       imguiDescHeap_p                    = nullptr;
    ID3D12Resource1*            depthBuffers_pp[NUM_SWAP_BUFFERS]  = {};
    ID3D12Resource1*            renderTargets_pp[NUM_SWAP_BUFFERS] = {};
    D3D12_VIEWPORT              viewport                           = {};
    D3D12_RECT                  scissorRect                        = {};
    uint                        currentBackbufferIndex             = 0u;
    uint                        renderTargetDescriptorSize         = 0u;
    uint                        depthBufferDescriptorSize          = 0u;
  } myGraphicalInterface;

  struct
  {
    ID3D12RootSignature*        rootSignature_p    = nullptr;
    ID3D12CommandQueue*         commandQueue_p     = nullptr;
    ID3D12CommandAllocator*     commandAllocator_p = nullptr;
    ID3D12GraphicsCommandList4* commandList4_p     = nullptr;
  } myComputeInterface;
};