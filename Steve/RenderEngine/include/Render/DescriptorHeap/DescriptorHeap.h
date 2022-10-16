#pragma once

#include <string>
#include <Common/Typedef.h>
#include <d3d12.h>

namespace Render
{
  class DescriptorHeap : public D3D12_DESCRIPTOR_HEAP_DESC
  {
  public:
    DescriptorHeap();
    virtual ~DescriptorHeap() = default;
    void                  Release();
    void                  Create(const std::string& name);
    ID3D12DescriptorHeap* GetDescHeap();
    uint32                GetDescHeapSize() const;
    D3D12_CPU_DESCRIPTOR_HANDLE GetCpuDescHeandle() const;
    D3D12_GPU_DESCRIPTOR_HANDLE GetGpuDescHeandle() const;

  private:
    ID3D12DescriptorHeap* myDescHeap_p = nullptr;
    uint32                myDescHeapSize = 0;
  };
} // namespace Render