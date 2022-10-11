#include "pch.h"
#include "Render/DescriptorHeap/DescriptorHeap.h"

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

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCpuDescHeandle() const
{
  return myDescHeap_p->GetCPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGpuDescHeandle() const
{
  return myDescHeap_p->GetGPUDescriptorHandleForHeapStart();
}
