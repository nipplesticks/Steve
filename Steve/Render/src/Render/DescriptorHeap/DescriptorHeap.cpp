#include "pch.h"
#include "Render/DescriptorHeap/DescriptorHeap.h"
#include "Render/Renderer.h"

using namespace Render;

DescriptorHeap::DescriptorHeap()
    : D3D12_DESCRIPTOR_HEAP_DESC {}
{ }

void DescriptorHeap::Release()
{
  SafeRelease(&myDescHeap_p);
}

void DescriptorHeap::Create(const std::string& name)
{
  if (myDescHeap_p == nullptr)
  {
    HR_ASSERT(Device::GetDevice()->CreateDescriptorHeap(this, IID_PPV_ARGS(&myDescHeap_p)));
    myDescHeapSize = Device::GetDevice()->GetDescriptorHandleIncrementSize(Type);
  }
  myDescHeap_p->SetName(String::ToWString(name).c_str());
}

ID3D12DescriptorHeap* DescriptorHeap::GetDescHeap()
{
  return myDescHeap_p;
}

uint32 DescriptorHeap::GetDescHeapSize() const
{
  return myDescHeapSize;
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCpuDescHandle(uint16 swapBufferIdx,
                                                             uint16 numDescriptors) const
{
  auto handle = myDescHeap_p->GetCPUDescriptorHandleForHeapStart();
  _offsetDescHandlePtr(handle.ptr, swapBufferIdx, numDescriptors);

  return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGpuDescHandle(uint16 swapBufferIdx,
                                                             uint16 numDescriptors) const
{
  auto handle = myDescHeap_p->GetGPUDescriptorHandleForHeapStart();
  _offsetDescHandlePtr(handle.ptr, swapBufferIdx, numDescriptors);
  return handle;
}

void Render::DescriptorHeap::_offsetDescHandlePtr(size_t& ptr,
                                                  uint16  swapBufferIdx,
                                                  uint16  numDescriptors) const
{
  ptr += (uint64)swapBufferIdx * myDescHeapSize * numDescriptors;
}
