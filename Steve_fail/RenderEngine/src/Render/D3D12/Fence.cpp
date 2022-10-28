#include "pch.h"
#include "Render/D3D12/Fence.h"

void Render::Fence::Create(const std::string& name, uint64 fenceValue, D3D12_FENCE_FLAGS fenceFlags)
{
  auto _name = String::ToWString(name);
  HR_ASSERT(Device::GetDevice()->CreateFence(fenceValue, fenceFlags, IID_PPV_ARGS(&myFence_p)));
  myFence_p->SetName(_name.c_str());
  myFenceValue  = fenceValue + 1;
  myEventHandle = CreateEvent(0, FALSE, FALSE, _name.c_str());
}
