#include "pch.h"
#include "Render/D3D12/CommandHandler.h"
#include "Render/Resource/Resource.h"

constexpr uint16 MAX_NUM_RESOURCE_TRANS_BARRIERS = 128;

using namespace Render;

void Render::CommandHandler::Create(const std::string&              name,
                                    D3D12_COMMAND_LIST_TYPE         listType,
                                    const D3D12_COMMAND_QUEUE_DESC& queueDesc)
{
  HR_ASSERT(Device::GetDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&myCommandQueue_p)));
  HR_ASSERT(
      Device::GetDevice()->CreateCommandAllocator(listType, IID_PPV_ARGS(&myCommandAllocator_p)));
  HR_ASSERT(Device::GetDevice()->CreateCommandList(
      0, listType, myCommandAllocator_p, nullptr, IID_PPV_ARGS(&myCommandList_p)));

  myCommandQueue_p->SetName(String::ToWString(name + "_queue").c_str());
  myCommandAllocator_p->SetName(String::ToWString(name + "_allocator").c_str());
  myCommandList_p->SetName(String::ToWString(name + "_list").c_str());

  Close();
}

void Render::CommandHandler::Reset()
{
  myCommandAllocator_p->Reset();
  myCommandList_p->Reset(myCommandAllocator_p, nullptr);
}

void Render::CommandHandler::Close()
{
  myCommandList_p->Close();
}

void Render::CommandHandler::Execute()
{
  myCommandQueue_p->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList**>(myCommandList_p));
}

void Render::CommandHandler::Release()
{
  SafeRelease(&myCommandAllocator_p);
  SafeRelease(&myCommandList_p);
  SafeRelease(&myCommandQueue_p);
}

void Render::CommandHandler::SetRenderTargets(uint32 numRenderTargetDesc,
                                              const D3D12_CPU_DESCRIPTOR_HANDLE* rtvCpuDescHandle_p,
                                              const D3D12_CPU_DESCRIPTOR_HANDLE* dsvCpuDescHandle_p)
{
  myCommandList_p->OMSetRenderTargets(
      numRenderTargetDesc, rtvCpuDescHandle_p, TRUE, dsvCpuDescHandle_p);
  myCommandList_p->SetGraphicsRootSignature(Rootsignature::GetGraphicRootsignature());
}

void Render::CommandHandler::ResourceTransitionBarrier(Resource*             resources_p,
                                                       uint16                numResources,
                                                       D3D12_RESOURCE_STATES after)
{
  D3D12_RESOURCE_BARRIER desc[MAX_NUM_RESOURCE_TRANS_BARRIERS] = {};
  ASSERT(!(numResources < MAX_NUM_RESOURCE_TRANS_BARRIERS));

  for (uint16 i = 0; i < numResources; i++)
  {
    desc[i].Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    desc[i].Transition.pResource   = resources_p[i].GetResource();
    desc[i].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    desc[i].Transition.StateBefore = resources_p[i].GetState();
    desc[i].Transition.StateAfter  = after;
  }

  myCommandList_p->ResourceBarrier(numResources, desc);
}

ID3D12CommandAllocator* Render::CommandHandler::GetCommandAllocator() const
{
  return myCommandAllocator_p;
}

ID3D12GraphicsCommandList4* Render::CommandHandler::GetCommandList() const
{
  return myCommandList_p;
}

ID3D12CommandQueue* Render::CommandHandler::GetCommandQueue() const
{
  return myCommandQueue_p;
}
