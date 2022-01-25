#include "TextureBuffer.h"
#include "../utility/RenderUtility.h"
#include "Renderer.h"

void TextureBuffer::Init(uint width, uint height, uint channels)
{
  myHeight                 = height;
  myWidth                  = width;
  ID3D12Device5* gDevice_p = Renderer::GetDevice();

  D3D12_HEAP_PROPERTIES heapProp = {};
  heapProp.Type                  = D3D12_HEAP_TYPE_DEFAULT;
  heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

  D3D12_RESOURCE_DESC desc = {};
  desc.DepthOrArraySize    = 1;
  desc.Dimension           = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  desc.Flags               = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
  desc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.Height              = height;
  desc.Width               = width;
  //desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;

  HR_ASSERT(gDevice_p->CreateCommittedResource(&heapProp,
                                               D3D12_HEAP_FLAG_NONE,
                                               &desc,
                                               D3D12_RESOURCE_STATE_COPY_DEST,
                                               nullptr,
                                               IID_PPV_ARGS(&myTextureBuffer_p)));

  /*D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
  heapDesc.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  heapDesc.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  heapDesc.NumDescriptors             = 1;

  HR_ASSERT(gDevice_p->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&myHeap_p)));

  D3D12_SHADER_RESOURCE_VIEW_DESC rsvDesc = {};
  rsvDesc.Shader4ComponentMapping         = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  rsvDesc.Format                          = desc.Format;
  rsvDesc.ViewDimension                   = D3D12_SRV_DIMENSION_TEXTURE2D;
  rsvDesc.Texture2D.MipLevels             = desc.MipLevels;

  gDevice_p->CreateShaderResourceView(
      myTextureBuffer_p, &rsvDesc, myHeap_p->GetCPUDescriptorHandleForHeapStart());*/
}

void TextureBuffer::Update(Renderer* renderer_p, void* data_p)
{
  renderer_p->UploadTexture(*this, data_p);
}

uint TextureBuffer::GetHeight() const
{
  return myHeight;
}

uint TextureBuffer::GetWidth() const
{
  return myWidth;
}

ID3D12Resource* TextureBuffer::GetResource() const
{
  return myTextureBuffer_p;
}

ID3D12DescriptorHeap* TextureBuffer::GetHeap() const
{
  return myHeap_p;
}
