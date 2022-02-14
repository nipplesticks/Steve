#pragma once
#include "../../utility/Typedef.h"
#include <d3d12.h>

class Resource : public D3D12_RESOURCE_DESC
{
public:
  Resource()
      : D3D12_RESOURCE_DESC{}{};
  virtual ~Resource() = default;

  virtual void Update(void* data_p) = 0;

private:
  ID3D12Resource* myResource_p = nullptr;
  ID3D12DescriptorHeap* myHeap_p     = nullptr;
  uint                  myBufferSize = 0u;
  uint                  myElementSize = 0u;

};