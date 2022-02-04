#include "ConstantBuffer.h"
#include "../../utility/RenderUtility.h"
#include "../d3d12/Renderer.h"
#include "../../utility/UtilityFuncs.h"

void ConstantBuffer::Init(uint dataByteSize)
{
  myByteSize                      = dataByteSize;
  dataByteSize                    = AlignAs256(dataByteSize);
  ID3D12Device5*        gDevice_p = Renderer::GetDevice();
  D3D12_HEAP_PROPERTIES heapProp  = {};
  heapProp.Type                   = D3D12_HEAP_TYPE_UPLOAD;
  heapProp.CPUPageProperty        = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference   = D3D12_MEMORY_POOL_UNKNOWN;

  D3D12_RESOURCE_DESC desc = {};
  desc.DepthOrArraySize    = 1;
  desc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
  desc.Flags               = D3D12_RESOURCE_FLAG_NONE;
  desc.Format              = DXGI_FORMAT_UNKNOWN;
  desc.Height              = 1;
  desc.Width               = dataByteSize;
  desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;

  HR_ASSERT(gDevice_p->CreateCommittedResource(&heapProp,
                                               D3D12_HEAP_FLAG_NONE,
                                               &desc,
                                               D3D12_RESOURCE_STATE_GENERIC_READ,
                                               nullptr,
                                               IID_PPV_ARGS(&myConstantBuffer_p)));
}

void ConstantBuffer::Update(void* data_p, uint dataByteSize)
{
  ASSERT_STR(dataByteSize <= myByteSize, "Passed size is greater than allocated resource");
  void* adress_p = nullptr;
  HR_ASSERT(myConstantBuffer_p->Map(0, nullptr, &adress_p));
  memcpy(adress_p, data_p, dataByteSize);
  myConstantBuffer_p->Unmap(0, nullptr);
}

uint ConstantBuffer::GetByteSize() const
{
  return myByteSize;
}

ID3D12Resource* ConstantBuffer::GetResource() const
{
  return myConstantBuffer_p;
}
