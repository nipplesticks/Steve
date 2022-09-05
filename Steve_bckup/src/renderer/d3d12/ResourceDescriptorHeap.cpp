#include "ResourceDescriptorHeap.h"
#include "../../utility/RenderUtility.h"
#include "../buffers/Resource.h"
#include "myRenderer.h"

#include <d3d12.h>

void ResourceDescriptorHeap::Create(const std::vector<Resource*>& cbvBuffers,
                                    const std::vector<Resource*>& srvBuffers,
                                    const std::vector<Resource*>& uavBuffers)
{
  myNumberOfCbvs = (uint)cbvBuffers.size();
  myNumberOfSrvs = (uint)srvBuffers.size();
  myNumberOfUavs = (uint)uavBuffers.size();

  MyRenderer* renderer_p = MyRenderer::GetInstance();

  D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
  heapDesc.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  heapDesc.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  heapDesc.NumDescriptors =
      (UINT)cbvBuffers.size() + (UINT)srvBuffers.size() + (uint)uavBuffers.size();

  HR_ASSERT(renderer_p->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&myHeap_p)));

  D3D12_CPU_DESCRIPTOR_HANDLE handle = myHeap_p->GetCPUDescriptorHandleForHeapStart();
  const uint                  SrvUavCbvDescriptorSize = renderer_p->GetSrvUavCbvDescritorSize();

  for (auto& cbv : cbvBuffers)
  {
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation                  = cbv->GetResource()->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes                     = AlignAs256(cbv->GetBufferSize());
    renderer_p->GetDevice()->CreateConstantBufferView(&cbvDesc, handle);
    handle.ptr += SrvUavCbvDescriptorSize;
  }
  for (auto& srv : srvBuffers)
  {
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping         = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format                          = srv->GetFormat();
    srvDesc.ViewDimension                   = Resource::GetSRVDimension(srv);
    switch (srvDesc.ViewDimension)
    {
    case D3D12_SRV_DIMENSION_UNKNOWN:
    case D3D12_SRV_DIMENSION_BUFFER:
      srvDesc.Buffer.Flags               = D3D12_BUFFER_SRV_FLAG_NONE;
      srvDesc.Buffer.NumElements         = srv->GetElementCount();
      srvDesc.Buffer.StructureByteStride = srv->GetElementSize();
      break;
    case D3D12_SRV_DIMENSION_TEXTURE1D:
      srvDesc.Texture1D.MipLevels = 1;
      break;
    case D3D12_SRV_DIMENSION_TEXTURE1DARRAY:
      srvDesc.Texture1DArray.ArraySize = srv->GetDimention().z;
      srvDesc.Texture1DArray.MipLevels = 1;
      break;
    case D3D12_SRV_DIMENSION_TEXTURE2D:
      srvDesc.Texture2D.MipLevels = 1;
      break;
    case D3D12_SRV_DIMENSION_TEXTURE2DARRAY:
      srvDesc.Texture2DArray.ArraySize = srv->GetDimention().z;
      srvDesc.Texture2DArray.MipLevels = 1;
      break;
    case D3D12_SRV_DIMENSION_TEXTURE3D:
      srvDesc.Texture3D.MipLevels = 1;
      break;
    }
    renderer_p->GetDevice()->CreateShaderResourceView(srv->GetResource(), &srvDesc, handle);
    handle.ptr += SrvUavCbvDescriptorSize;
  }

  for (auto& uav : uavBuffers)
  {
    D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
    uavDesc.Format                           = uav->GetFormat();
    uavDesc.ViewDimension                    = Resource::GetUAVDimension(uav);
    switch (uavDesc.ViewDimension)
    {
    case D3D12_UAV_DIMENSION_UNKNOWN:
    case D3D12_UAV_DIMENSION_BUFFER:
      uavDesc.Buffer.Flags                = D3D12_BUFFER_UAV_FLAG_NONE;
      uavDesc.Buffer.NumElements          = uav->GetElementCount();
      uavDesc.Buffer.CounterOffsetInBytes = 0;
      uavDesc.Buffer.StructureByteStride  = uav->GetElementSize();
      break;
    case D3D12_UAV_DIMENSION_TEXTURE1D:
      break;
    case D3D12_UAV_DIMENSION_TEXTURE1DARRAY:
      uavDesc.Texture1DArray.ArraySize = uav->GetDimention().z;
      break;
    case D3D12_UAV_DIMENSION_TEXTURE2DARRAY:
      uavDesc.Texture2DArray.ArraySize = uav->GetDimention().z;
      break;
    }
    renderer_p->GetDevice()->CreateUnorderedAccessView(
        uav->GetResource(), nullptr, &uavDesc, handle);
    handle.ptr += SrvUavCbvDescriptorSize;
  }
}

ID3D12DescriptorHeap* ResourceDescriptorHeap::GetDescriptorHeap() const
{
  return myHeap_p;
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetSrvHeapLocationStart() const
{
  D3D12_GPU_DESCRIPTOR_HANDLE handle = myHeap_p->GetGPUDescriptorHandleForHeapStart();
  handle.ptr += myNumberOfCbvs * MyRenderer::GetInstance()->GetSrvUavCbvDescritorSize();

  return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetCbvHeapLocationStart() const
{
  return myHeap_p->GetGPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetUavBufferHeapLocationStart() const
{
  D3D12_GPU_DESCRIPTOR_HANDLE handle = myHeap_p->GetGPUDescriptorHandleForHeapStart();
  handle.ptr +=
      (myNumberOfCbvs + myNumberOfSrvs) * MyRenderer::GetInstance()->GetSrvUavCbvDescritorSize();

  return handle;
}

bool ResourceDescriptorHeap::HasUavs() const
{
  return myNumberOfUavs > 0;
}

bool ResourceDescriptorHeap::HasCbvs() const
{
  return myNumberOfCbvs > 0;
}

bool ResourceDescriptorHeap::HasSrvs() const
{
  return myNumberOfSrvs > 0;
}
