#include "pch.h"
#include "Render/D3D12/CommandHandler.h"

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

  Reset();
}

void Render::CommandHandler::Open()
{
  myCommandAllocator_p->Reset();
  myCommandList_p->Reset(myCommandAllocator_p, nullptr);
}

void Render::CommandHandler::Reset()
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
