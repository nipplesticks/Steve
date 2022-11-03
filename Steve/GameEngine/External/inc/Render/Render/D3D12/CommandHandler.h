#pragma once

#include <string>
#include <d3d12.h>
#include "Fence.h"

namespace Render
{
  class Resource;
  class CommandHandler
  {
  public:
    void Create(const std::string&              name,
                D3D12_COMMAND_LIST_TYPE         listType,
                const D3D12_COMMAND_QUEUE_DESC& queueDesc = {});

    void Reset();
    void Close();
    void Execute();
    void Release();

    void HardWait();

    void SetRenderTargets(uint32                             numRenderTargetDesc,
                          const D3D12_CPU_DESCRIPTOR_HANDLE* rtvCpuDescHandle_p,
                          const D3D12_CPU_DESCRIPTOR_HANDLE* dsvCpuDescHandle_p);
    void ResourceTransitionBarrier(Resource*             resources_p,
                                   uint16                numResources,
                                   D3D12_RESOURCE_STATES after);
    void ResourceTransitionBarrier(ID3D12Resource1*                          resources_p,
                                   uint16                                    numResources,
                                   const std::vector<D3D12_RESOURCE_STATES>& beforeStates,
                                   D3D12_RESOURCE_STATES                     after);

    void ClearDsv(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle, uint16 numDsv = 1u);
    void ClearRtv(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle,
                  const DM::Vec4f&            clearColor = DM::Vec4f(),
                  uint16                      numRtvs    = 1u);

    void BindGraphicalRootSignature();
    void BindComputationalRootSignature();

    ID3D12CommandAllocator*     GetCommandAllocator() const;
    ID3D12GraphicsCommandList4* GetCommandList() const;
    ID3D12CommandQueue*         GetCommandQueue() const;

  private:
    ID3D12CommandAllocator*     myCommandAllocator_p = nullptr;
    ID3D12GraphicsCommandList4* myCommandList_p      = nullptr;
    ID3D12CommandQueue*         myCommandQueue_p     = nullptr;
    Fence                       myFence;
  };
} // namespace Render