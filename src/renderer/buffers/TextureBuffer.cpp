#include "TextureBuffer.h"
#include "../../utility/RenderUtility.h"
#include "../d3d12/Renderer.h"

void TextureBuffer::Init(uint width, uint height, DXGI_FORMAT format)
{
  myHeight                 = height;
  myWidth                  = width;
  myFormat                 = format;
  _setChannelInfo();
  ID3D12Device5* gDevice_p = Renderer::GetDevice();
  
  D3D12_HEAP_PROPERTIES heapProp = {};
  heapProp.Type                  = D3D12_HEAP_TYPE_DEFAULT;
  heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

  D3D12_RESOURCE_DESC desc = {};
  desc.DepthOrArraySize    = 1;
  desc.Dimension           = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  desc.Flags               = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
  desc.Format              = format;
  desc.Height              = height;
  desc.Width               = width;
  //desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  desc.MipLevels           = 1;
  desc.SampleDesc.Count    = 1;
  desc.SampleDesc.Quality  = 0;
  myStateBefore            = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
  HR_ASSERT(gDevice_p->CreateCommittedResource(&heapProp,
                                               D3D12_HEAP_FLAG_NONE,
                                               &desc,
                                               D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
                                               nullptr,
                                               IID_PPV_ARGS(&myTextureBuffer_p)));
}

void TextureBuffer::Update(Renderer* renderer_p, void* data_p)
{
  ASSERT(myStateBefore == D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
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

D3D12_RESOURCE_STATES TextureBuffer::GetBeforeState() const
{
  return myStateBefore;
}

void TextureBuffer::SetState(D3D12_RESOURCE_STATES state)
{
  myStateBefore = state;
}

DXGI_FORMAT TextureBuffer::GetFormat() const
{
  return myFormat;
}

uint TextureBuffer::GetNumberOfChannels() const
{
  return myNumberOfChannels;
}

uint TextureBuffer::GetChannelEllementSize() const
{
  return myChannelElementSize;
}

uint TextureBuffer::GetRowPitch() const
{
  return myWidth * myChannelElementSize * myNumberOfChannels;
}

void TextureBuffer::_setChannelInfo()
{
  switch (myFormat)
  {
  case DXGI_FORMAT_R32G32B32A32_TYPELESS:
  case DXGI_FORMAT_R32G32B32A32_FLOAT:
  case DXGI_FORMAT_R32G32B32A32_UINT:
  case DXGI_FORMAT_R32G32B32A32_SINT:
    myChannelElementSize = sizeof(uint);
    myNumberOfChannels   = 4;
    break;
  case DXGI_FORMAT_R32G32B32_TYPELESS:
  case DXGI_FORMAT_R32G32B32_FLOAT:
  case DXGI_FORMAT_R32G32B32_UINT:
  case DXGI_FORMAT_R32G32B32_SINT:
    myChannelElementSize = sizeof(uint);
    myNumberOfChannels   = 3;
    break;
  case DXGI_FORMAT_R16G16B16A16_TYPELESS:
  case DXGI_FORMAT_R16G16B16A16_FLOAT:
  case DXGI_FORMAT_R16G16B16A16_UNORM:
  case DXGI_FORMAT_R16G16B16A16_UINT:
  case DXGI_FORMAT_R16G16B16A16_SNORM:
  case DXGI_FORMAT_R16G16B16A16_SINT:
    myChannelElementSize = sizeof(uint16);
    myNumberOfChannels   = 4;
    break;
  case DXGI_FORMAT_R32G32_TYPELESS:
  case DXGI_FORMAT_R32G32_FLOAT:
  case DXGI_FORMAT_R32G32_UINT:
  case DXGI_FORMAT_R32G32_SINT:
    myChannelElementSize = sizeof(uint);
    myNumberOfChannels   = 2;
    break;
  case DXGI_FORMAT_R8G8B8A8_TYPELESS:
  case DXGI_FORMAT_R8G8B8A8_UNORM:
  case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
  case DXGI_FORMAT_R8G8B8A8_UINT:
  case DXGI_FORMAT_R8G8B8A8_SNORM:
  case DXGI_FORMAT_R8G8B8A8_SINT:
    myChannelElementSize = sizeof(uint8);
    myNumberOfChannels   = 4;
    break;
  case DXGI_FORMAT_R16G16_TYPELESS:
  case DXGI_FORMAT_R16G16_FLOAT:
  case DXGI_FORMAT_R16G16_UNORM:
  case DXGI_FORMAT_R16G16_UINT:
  case DXGI_FORMAT_R16G16_SNORM:
  case DXGI_FORMAT_R16G16_SINT:
    myChannelElementSize = sizeof(uint16);
    myNumberOfChannels   = 2;
    break;
  case DXGI_FORMAT_R32_TYPELESS:
  case DXGI_FORMAT_D32_FLOAT:
  case DXGI_FORMAT_R32_FLOAT:
  case DXGI_FORMAT_R32_UINT:
  case DXGI_FORMAT_R32_SINT:
    myChannelElementSize = sizeof(uint);
    myNumberOfChannels   = 1;
    break;
  case DXGI_FORMAT_R8G8_TYPELESS:
  case DXGI_FORMAT_R8G8_UNORM:
  case DXGI_FORMAT_R8G8_UINT:
  case DXGI_FORMAT_R8G8_SNORM:
  case DXGI_FORMAT_R8G8_SINT:
    myChannelElementSize = sizeof(uint8);
    myNumberOfChannels   = 1;
    break;
  case DXGI_FORMAT_R16_TYPELESS:
  case DXGI_FORMAT_R16_FLOAT:
  case DXGI_FORMAT_D16_UNORM:
  case DXGI_FORMAT_R16_UNORM:
  case DXGI_FORMAT_R16_UINT:
  case DXGI_FORMAT_R16_SNORM:
  case DXGI_FORMAT_R16_SINT:
    myChannelElementSize = sizeof(uint16);
    myNumberOfChannels   = 1;
    break;
  case DXGI_FORMAT_R8_TYPELESS:
  case DXGI_FORMAT_R8_UNORM:
  case DXGI_FORMAT_R8_UINT:
  case DXGI_FORMAT_R8_SNORM:
  case DXGI_FORMAT_R8_SINT:
  case DXGI_FORMAT_A8_UNORM:
    myChannelElementSize = sizeof(uint8);
    myNumberOfChannels   = 1;
    break;
  default:
    ASSERT_STR(false, "Unsuported format, please rethink your life...\n");
    break;
  }
}
