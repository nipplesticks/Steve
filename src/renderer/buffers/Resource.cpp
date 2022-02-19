#include "Resource.h"
#include "../../utility/RenderUtility.h"
#include "../d3d12/myRenderer.h"


void Resource::Init(Resource_Type resourceType,
                    uint          width,
                    DXGI_FORMAT   format,
                    uint          height,
                    uint          depth,
                    uint          nrOfElements)
{
  myResourceType = resourceType;
  myDimention.x  = width;
  myDimention.y  = height;
  myDimention.z  = depth;
  myElementSize  = (width * height * depth) / nrOfElements;
  myBufferSize   = AlignAs256(myElementSize * nrOfElements);
  myRowPitch     = width;
  myFormat       = format;
  myNumberOfElements = nrOfElements;

  uint channelElementSize = 0;
  uint nrOfChannels       = 0;
  if (GetChannelInformation(format, &channelElementSize, &nrOfChannels))
  {
    myElementSize = channelElementSize * nrOfChannels;
    myBufferSize = AlignAs(256,((width * height * depth) * channelElementSize * nrOfChannels));
    myRowPitch = channelElementSize * nrOfChannels * width;
  }

  D3D12_HEAP_PROPERTIES heapProp = {};
  heapProp.Type                  = D3D12_HEAP_TYPE_DEFAULT;
  heapProp.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

  D3D12_RESOURCE_DESC desc = {};
  desc.Dimension           = _GetResourceDimension(resourceType);
  if (desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
    width = AlignAs256(width);
  desc.Width            = width;
  desc.Height           = height;
  desc.Flags            = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
  desc.DepthOrArraySize = depth;
  desc.Format           = format;
  if (desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
    desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  desc.MipLevels          = 1;
  desc.SampleDesc.Count   = 1;
  desc.SampleDesc.Quality = 0;
  
  myState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
  
  Init(&heapProp, &desc, D3D12_HEAP_FLAG_NONE, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

  if (resourceType == Resource_Type::VertexBuffer)
  {
    myResourceView.vbv.BufferLocation = myResource_p->GetGPUVirtualAddress();
    myResourceView.vbv.SizeInBytes    = (uint)desc.Width;
    myResourceView.vbv.StrideInBytes  = myElementSize;
  }
  else if (resourceType == Resource_Type::IndexBuffer)
  {
    myResourceView.ibv.BufferLocation = myResource_p->GetGPUVirtualAddress();
    myResourceView.ibv.SizeInBytes    = (uint)desc.Width;
    myResourceView.ibv.Format         = DXGI_FORMAT_R32_UINT;
  }
}

D3D12_UAV_DIMENSION Resource::GetUAVDimension(Resource* resource_p)
{
  D3D12_UAV_DIMENSION uavDimension = D3D12_UAV_DIMENSION_UNKNOWN;
  switch (resource_p->myResourceType)
  {
  case Resource::Resource_Type::IndexBuffer:
  case Resource::Resource_Type::VertexBuffer:
  case Resource::Resource_Type::StructuredBuffer:
  case Resource::Resource_Type::ConstantBuffer:
    uavDimension = D3D12_UAV_DIMENSION_BUFFER;
    break;
  case Resource::Resource_Type::Texture1D:
    if (resource_p->myDimention.z > 1)
      uavDimension = D3D12_UAV_DIMENSION_TEXTURE1DARRAY;
    else
      uavDimension = D3D12_UAV_DIMENSION_TEXTURE1D;
    break;
  case Resource::Resource_Type::Texture2D:
    if (resource_p->myDimention.z > 1)
      uavDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
    else
      uavDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
    break;
  case Resource::Resource_Type::Texture3D:
    uavDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
    break;
  }

  return uavDimension;
}

D3D12_SRV_DIMENSION Resource::GetSRVDimension(Resource* resource_p)
{
  D3D12_SRV_DIMENSION srvDimension = D3D12_SRV_DIMENSION_UNKNOWN;
  switch (resource_p->myResourceType)
  {
  case Resource::Resource_Type::IndexBuffer:
  case Resource::Resource_Type::VertexBuffer:
  case Resource::Resource_Type::StructuredBuffer:
  case Resource::Resource_Type::ConstantBuffer:
    srvDimension = D3D12_SRV_DIMENSION_BUFFER;
    break;
  case Resource::Resource_Type::Texture1D:
    if (resource_p->myDimention.z > 1)
      srvDimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
    else
      srvDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
    break;
  case Resource::Resource_Type::Texture2D:
    if (resource_p->myDimention.z > 1)
      srvDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
    else
      srvDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    break;
  case Resource::Resource_Type::Texture3D:
    srvDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
    break;
  }
  return srvDimension;
}

void Resource::Init(D3D12_HEAP_PROPERTIES* heapProperties,
                    D3D12_RESOURCE_DESC*   resourceDesc,
                    D3D12_HEAP_FLAGS       heapFlags,
                    D3D12_RESOURCE_STATES  initialState,
                    D3D12_CLEAR_VALUE*     clearValue)
{
  MyRenderer* renderer_p = MyRenderer::GetInstance();
  HR_ASSERT(renderer_p->GetDevice()->CreateCommittedResource(heapProperties,
                                                             heapFlags,
                                                             resourceDesc,
                                                             initialState,
                                                             clearValue,
                                                             IID_PPV_ARGS(&myResource_p)));
}

void Resource::UpdateNow(void*                 data_p,
                         D3D12_RESOURCE_STATES stateAfter,
                         uint64                sizeofData,
                         uint64                offset)
{
  MyRenderer::GetInstance()->ResourceUpdate(data_p, sizeofData, offset, stateAfter, this);
  myState = stateAfter;
}

void Resource::UpdateForGraphic(void*                 data_p,
                                D3D12_RESOURCE_STATES stateAfter,
                                uint64                sizeofData,
                                uint64                offset)
{
  ASSERT(false);
}
void Resource::UpdateForCompute(void*                 data_p,
                                D3D12_RESOURCE_STATES stateAfter,
                                uint64                sizeofData,
                                uint64                offset)
{
  ASSERT(false);
}

const DM::Vec3u& Resource::GetDimention() const
{
  return myDimention;
}

ID3D12Resource* Resource::GetResource() const
{
  return myResource_p;
}

uint64 Resource::GetRowPitch()
{
  return myRowPitch;
}

void Resource::SetState(D3D12_RESOURCE_STATES state)
{
  MyRenderer::GetInstance()->ChangeResourceStateNow(GetResource(), myState, state);
  myState = state;
}


D3D12_RESOURCE_STATES Resource::GetState() const
{
  return myState;
}

const Resource::Resource_View& Resource::GetView() const
{
  return myResourceView;
}

DXGI_FORMAT Resource::GetFormat() const
{
  return myFormat;
}

uint64 Resource::GetBufferSize() const
{
  return myBufferSize;
}

uint Resource::GetElementSize() const
{
  return myElementSize;
}

uint Resource::GetElementCount() const
{
  return myNumberOfElements;
}

Resource::Resource_Type Resource::GetResourceType() const
{
  return myResourceType;
}

D3D12_RESOURCE_DIMENSION Resource::_GetResourceDimension(Resource_Type resourceType)
{
  switch (resourceType)
  {
  case Resource::Resource_Type::Unknown:
    return D3D12_RESOURCE_DIMENSION_UNKNOWN;
  case Resource::Resource_Type::ConstantBuffer:
    return D3D12_RESOURCE_DIMENSION_BUFFER;
  case Resource::Resource_Type::Texture1D:
    return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
  case Resource::Resource_Type::Texture2D:
    return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  case Resource::Resource_Type::Texture3D:
    return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
  case Resource::Resource_Type::StructuredBuffer:
    return D3D12_RESOURCE_DIMENSION_BUFFER;
  case Resource::Resource_Type::VertexBuffer:
    return D3D12_RESOURCE_DIMENSION_BUFFER;
  case Resource::Resource_Type::IndexBuffer:
    return D3D12_RESOURCE_DIMENSION_BUFFER;
  default:
    ASSERT_STR(false, "Unsupported resource type\n");
    break;
  }
  return D3D12_RESOURCE_DIMENSION_UNKNOWN;
}
