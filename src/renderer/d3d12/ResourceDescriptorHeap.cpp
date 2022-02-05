#include "ResourceDescriptorHeap.h"
#include "../../utility/RenderUtility.h"
#include "../buffers/TextureBuffer.h"
#include "../buffers/ConstantBuffer.h"
#include "Renderer.h"

#include <d3d12.h>

void ResourceDescriptorHeap::Create(const std::vector<ConstantBuffer*>& constantBuffers,
                                    const std::vector<TextureBuffer*>&  textureBuffers,
                                    const std::vector<TextureBuffer*>&  uavBuffers)
{
  ID3D12Device* gDevice_p             = Renderer::GetDevice();
  myNumberOfConstantBuffers           = (uint)constantBuffers.size();
  myNumberOfTextureBuffers            = (uint)textureBuffers.size();
  D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
  heapDesc.Type                       = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  heapDesc.Flags                      = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  heapDesc.NumDescriptors             = (UINT)constantBuffers.size() + (UINT)textureBuffers.size() + (uint)uavBuffers.size();

  HR_ASSERT(gDevice_p->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&myHeap_p)));

  D3D12_CPU_DESCRIPTOR_HANDLE handle = myHeap_p->GetCPUDescriptorHandleForHeapStart();
  const uint                  SrvUavCbvDescriptorSize = Renderer::GetSrvUavCbvDescriptorSize();

  for (auto& cb : constantBuffers)
  {
    myHasCbs                                = true;
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation                  = cb->GetResource()->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes                     = AlignAs256(cb->GetByteSize());
    gDevice_p->CreateConstantBufferView(&cbvDesc, handle);
    handle.ptr += SrvUavCbvDescriptorSize;
  }
  for (auto& tx : textureBuffers)
  {
    myHasText                               = true;
    D3D12_SHADER_RESOURCE_VIEW_DESC rsvDesc = {};
    rsvDesc.Shader4ComponentMapping         = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    rsvDesc.Format                          = tx->GetFormat();
    rsvDesc.ViewDimension                   = D3D12_SRV_DIMENSION_TEXTURE2D;
    rsvDesc.Texture2D.MipLevels             = 1;
    gDevice_p->CreateShaderResourceView(tx->GetResource(), &rsvDesc, handle);
    handle.ptr += SrvUavCbvDescriptorSize;
  }

  for (auto& uav : uavBuffers)
  {
    myHasUavs                                = true;
    D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
    uavDesc.Format                           = uav->GetFormat();
    uavDesc.ViewDimension                    = D3D12_UAV_DIMENSION_TEXTURE2D;
    gDevice_p->CreateUnorderedAccessView(uav->GetResource(), nullptr, &uavDesc, handle);
    handle.ptr += SrvUavCbvDescriptorSize;
  }
}

void ResourceDescriptorHeap::CreateWithConstantBuffers(
    const std::vector<ConstantBuffer*>& constantBuffers)
{
  Create(constantBuffers, {}, {});
}

void ResourceDescriptorHeap::CreateWithTextureBuffers(
    const std::vector<TextureBuffer*>& textureBuffers)
{
  Create({}, textureBuffers, {});
}

void ResourceDescriptorHeap::CreateWithUAVBuffers(const std::vector<TextureBuffer*>& uavBuffers)
{
  Create({}, {}, uavBuffers);
}

ID3D12DescriptorHeap* ResourceDescriptorHeap::GetDescriptorHeap() const
{
  return myHeap_p;
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetTextureHeapLocationStart() const
{
  D3D12_GPU_DESCRIPTOR_HANDLE handle = myHeap_p->GetGPUDescriptorHandleForHeapStart();
  handle.ptr += myNumberOfConstantBuffers * Renderer::GetSrvUavCbvDescriptorSize();

  return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetConstantBufferHeapLocationStart() const
{
  return myHeap_p->GetGPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE ResourceDescriptorHeap::GetUAVBufferHeapLocationStart() const
{
  D3D12_GPU_DESCRIPTOR_HANDLE handle = myHeap_p->GetGPUDescriptorHandleForHeapStart();
  handle.ptr += (myNumberOfConstantBuffers + myNumberOfTextureBuffers) * Renderer::GetSrvUavCbvDescriptorSize();

  return handle;
}

bool ResourceDescriptorHeap::HasUavs() const
{
  return myHasUavs;
}

bool ResourceDescriptorHeap::HasConstantBuffers() const
{
  return myHasCbs;
}

bool ResourceDescriptorHeap::HasTextures() const
{
  return myHasText;
}
