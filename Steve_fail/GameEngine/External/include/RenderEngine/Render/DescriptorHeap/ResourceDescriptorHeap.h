#pragma once

#include "DescriptorHeap.h"
#include <vector>

namespace Render
{
  class Resource;

  class ResourceDescriptorHeap : public DescriptorHeap
  {
  public:
    ResourceDescriptorHeap();
    virtual ~ResourceDescriptorHeap();

    void CreateAndBindResources(const std::string&            name,
                                const std::vector<Resource*>& cbvs,
                                const std::vector<Resource*>& srvs,
                                const std::vector<Resource*>& uavs);

    D3D12_GPU_DESCRIPTOR_HANDLE GetCbvDescHandle() const;
    D3D12_GPU_DESCRIPTOR_HANDLE GetSrvDescHandle() const;
    D3D12_GPU_DESCRIPTOR_HANDLE GetUavDescHandle() const;

    bool HasCbvs() const;
    bool HasSrvs() const;
    bool HasUavs() const;

  private:
    uint32 myNumCbvs = 0u;
    uint32 myNumSrvs = 0u;
    uint32 myNumUavs = 0u;
  };

} // namespace Render