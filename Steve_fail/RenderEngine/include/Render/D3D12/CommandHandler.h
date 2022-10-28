#pragma once

#include <string>

namespace Render
{
  class CommandHandler
  {
  public:
    void Create(const std::string&              name,
                D3D12_COMMAND_LIST_TYPE         listType,
                const D3D12_COMMAND_QUEUE_DESC& queueDesc = {});

    void Open();
    void Reset();
    void Execute();

    void Release();

    ID3D12CommandAllocator*     GetCommandAllocator() const;
    ID3D12GraphicsCommandList4* GetCommandList() const;
    ID3D12CommandQueue*         GetCommandQueue() const;

  private:
    ID3D12CommandAllocator*     myCommandAllocator_p = nullptr;
    ID3D12GraphicsCommandList4* myCommandList_p      = nullptr;
    ID3D12CommandQueue*         myCommandQueue_p     = nullptr;
  };
} // namespace Render