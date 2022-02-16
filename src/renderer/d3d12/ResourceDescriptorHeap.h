#pragma once

#include "../../utility/Typedef.h"
#include <d3d12.h>
#include <vector>

struct ID3D12DescriptorHeap;
class TextureBuffer;
class ConstantBuffer;
class Resource;

class ResourceDescriptorHeap
{
public:
  void Create(const std::vector<Resource*>& constantBuffers,
              const std::vector<Resource*>& srvBuffers,
              const std::vector<Resource*>& uavBuffers);

  ID3D12DescriptorHeap*       GetDescriptorHeap() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetSrvHeapLocationStart() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetCbvHeapLocationStart() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetUavBufferHeapLocationStart() const;

  bool HasUavs() const;
  bool HasCbvs() const;
  bool HasSrvs() const;

private:
  ID3D12DescriptorHeap* myHeap_p       = nullptr;
  uint                  myNumberOfCbvs = 0u;
  uint                  myNumberOfSrvs = 0u;
  bool                  myUavExist     = false;
  bool                  myCbvExist     = false;
  bool                  mySrvExist     = false;
};