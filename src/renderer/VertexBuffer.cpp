#include "VertexBuffer.h"
#include "../utility/RenderUtility.h"
#include "Renderer.h"

void VertexBuffer::Init(uint size, uint stride)
{

  assert((size % stride) == 0);
  myNumVertices                   = size / stride;
  size                            = AlignAs256(size);
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
                                               IID_PPV_ARGS(&myVertexBuffer_p)));

  myVertexBufferView.BufferLocation = myVertexBuffer_p->GetGPUVirtualAddress();
  myVertexBufferView.SizeInBytes    = size;
  myVertexBufferView.StrideInBytes  = stride;
}

void VertexBuffer::Update(void* data, uint size)
{
  void* adress_p = nullptr;
  HR_ASSERT(myVertexBuffer_p->Map(0, nullptr, &adress_p));
  memcpy(adress_p, data, size);
  myVertexBuffer_p->Unmap(0, nullptr);
}

ID3D12Resource* VertexBuffer::GetResource()
{
  return myVertexBuffer_p;
}

const D3D12_VERTEX_BUFFER_VIEW& VertexBuffer::GetVBV() const
{
  return myVertexBufferView;
}

uint VertexBuffer::GetVertexCount() const
{
  return myNumVertices;
}
