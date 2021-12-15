#include "IndexBuffer.h"
#include "../utility/RenderUtility.h"
#include "Renderer.h"

void IndexBuffer::Init(uint indexCount)
{
  myNumIndices                    = indexCount;
  uint size                       = indexCount * sizeof(uint);
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
  desc.Width               = size;
  desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;

  HR_ASSERT(gDevice_p->CreateCommittedResource(&heapProp,
                                               D3D12_HEAP_FLAG_NONE,
                                               &desc,
                                               D3D12_RESOURCE_STATE_GENERIC_READ,
                                               nullptr,
                                               IID_PPV_ARGS(&myIndexBuffer_p)));

  myIndexBufferView.BufferLocation = myIndexBuffer_p->GetGPUVirtualAddress();
  myIndexBufferView.SizeInBytes    = size;
  myIndexBufferView.Format         = DXGI_FORMAT_R32_UINT;
}

void IndexBuffer::Update(void* data)
{
  uint  size     = myNumIndices * sizeof(uint);
  void* adress_p = nullptr;
  HR_ASSERT(myIndexBuffer_p->Map(0, nullptr, &adress_p));
  memcpy(adress_p, data, size);
  myIndexBuffer_p->Unmap(0, nullptr);
}

ID3D12Resource* IndexBuffer::GetResource()
{
  return myIndexBuffer_p;
}

const D3D12_INDEX_BUFFER_VIEW& IndexBuffer::GetIBV() const
{
  return myIndexBufferView;
}

uint IndexBuffer::GetIndexCount() const
{
  return myNumIndices;
}
