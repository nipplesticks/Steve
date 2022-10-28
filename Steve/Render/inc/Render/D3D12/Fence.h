#pragma once

#include <string>

namespace Render
{
  class Fence
  {
  public:
    void Create(const std::string& name,
                uint64             fenceValue = 0,
                D3D12_FENCE_FLAGS  fenceFlags = D3D12_FENCE_FLAG_NONE);

  private:
    HANDLE        myEventHandle;
    uint64        myFenceValue;
    ID3D12Fence1* myFence_p = nullptr;
  };
} // namespace Render