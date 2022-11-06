#include "pch.h"
#include "Render/DescriptorHeap/ResourceDescriptorHeap.h"
#include "Render/Resource/Resource.h"

using namespace Render;

static void _setupSrvDesc(D3D12_SHADER_RESOURCE_VIEW_DESC& desc, Resource* srv_p)
{
  desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  desc.Format                  = srv_p->GetFormat();
  desc.ViewDimension           = Resource::GetSRVDimension(srv_p);
  switch (desc.ViewDimension)
  {
  case D3D12_SRV_DIMENSION_UNKNOWN:
  case D3D12_SRV_DIMENSION_BUFFER:
    desc.Buffer.Flags               = D3D12_BUFFER_SRV_FLAG_NONE;
    desc.Buffer.NumElements         = srv_p->GetElementCount();
    desc.Buffer.StructureByteStride = srv_p->GetElementSize();
    break;
  case D3D12_SRV_DIMENSION_TEXTURE1D:
    desc.Texture1D.MipLevels = 1;
    break;
  case D3D12_SRV_DIMENSION_TEXTURE1DARRAY:
    desc.Texture1DArray.ArraySize = srv_p->GetDimention().z;
    desc.Texture1DArray.MipLevels = 1;
    break;
  case D3D12_SRV_DIMENSION_TEXTURE2D:
    desc.Texture2D.MipLevels = 1;
    break;
  case D3D12_SRV_DIMENSION_TEXTURE2DARRAY:
    desc.Texture2DArray.ArraySize = srv_p->GetDimention().z;
    desc.Texture2DArray.MipLevels = 1;
    break;
  case D3D12_SRV_DIMENSION_TEXTURE3D:
    desc.Texture3D.MipLevels = 1;
    break;
  }
}
static void _setupUavDesc(D3D12_UNORDERED_ACCESS_VIEW_DESC& desc, Resource* uav_p)
{
  desc.Format        = uav_p->GetFormat();
  desc.ViewDimension = Resource::GetUAVDimension(uav_p);
  switch (desc.ViewDimension)
  {
  case D3D12_UAV_DIMENSION_UNKNOWN:
  case D3D12_UAV_DIMENSION_BUFFER:
    desc.Buffer.Flags                = D3D12_BUFFER_UAV_FLAG_NONE;
    desc.Buffer.NumElements          = uav_p->GetElementCount();
    desc.Buffer.CounterOffsetInBytes = 0;
    desc.Buffer.StructureByteStride  = uav_p->GetElementSize();
    break;
  case D3D12_UAV_DIMENSION_TEXTURE1D:
    break;
  case D3D12_UAV_DIMENSION_TEXTURE1DARRAY:
    desc.Texture1DArray.ArraySize = uav_p->GetDimention().z;
    break;
  case D3D12_UAV_DIMENSION_TEXTURE2DARRAY:
    desc.Texture2DArray.ArraySize = uav_p->GetDimention().z;
    break;
  }
}

ResourceDescriptorHeap::ResourceDescriptorHeap()
    : DescriptorHeap()
{ }

ResourceDescriptorHeap::~ResourceDescriptorHeap() { }

void ResourceDescriptorHeap::CreateAndBindResources(const std::string&            name,
                                                    const std::vector<Resource*>& cbvs,
                                                    const std::vector<Resource*>& srvs,
                                                    const std::vector<Resource*>& uavs)
{
  myNumCbvs      = (uint32)cbvs.size();
  myNumSrvs      = (uint32)srvs.size();
  myNumUavs      = (uint32)uavs.size();
  Type           = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  NumDescriptors = (UINT)cbvs.size() + (UINT)srvs.size() + (UINT)uavs.size();
  Create(name);

  auto         handle        = GetCpuDescHandle();
  const uint32 cbvSrvUavSize = Device::GetSrvUavCbvDescriptorSize();

  for (auto& cbv : cbvs)
  {
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};

    uint64 bufSizeAligned  = AlignAs256(cbv->GetBufferSize());
    cbvDesc.BufferLocation = cbv->GetResource()->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes    = (uint32)bufSizeAligned;

    Device::GetDevice()->CreateConstantBufferView(&cbvDesc, handle);
    handle.ptr += cbvSrvUavSize;
  }
  for (auto& srv : srvs)
  {
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    _setupSrvDesc(srvDesc, srv);
    Device::GetDevice()->CreateShaderResourceView(srv->GetResource(), &srvDesc, handle);
    handle.ptr += cbvSrvUavSize;
  }
  for (auto& uav : uavs)
  {
    D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
    _setupUavDesc(uavDesc, uav);
    Device::GetDevice()->CreateUnorderedAccessView(uav->GetResource(), nullptr, &uavDesc, handle);
    handle.ptr += cbvSrvUavSize;
  }
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetCbvDescHandle() const
{
  return GetGpuDescHandle();
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetSrvDescHandle() const
{
  auto handle = GetGpuDescHandle();
  handle.ptr += static_cast<uint64>(myNumCbvs) * Device::GetSrvUavCbvDescriptorSize();
  return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetUavDescHandle() const
{
  auto handle = GetGpuDescHandle();
  handle.ptr += (static_cast<uint64>(myNumCbvs) + myNumSrvs) * Device::GetSrvUavCbvDescriptorSize();
  return handle;
}

bool ResourceDescriptorHeap::HasCbvs() const
{
  return myNumCbvs;
}

bool ResourceDescriptorHeap::HasSrvs() const
{
  return myNumSrvs;
}

bool ResourceDescriptorHeap::HasUavs() const
{
  return myNumUavs;
}
