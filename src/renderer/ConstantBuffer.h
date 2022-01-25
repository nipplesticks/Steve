#pragma once

#include "../utility/Typedef.h"
#include <d3d12.h>

class ConstantBuffer
{
public:
  ConstantBuffer() = default;
  ~ConstantBuffer() = default;

  void Init(uint dataByteSize);
  void Update(void* data_p, uint dataByteSize);
  uint GetByteSize() const;

  ID3D12Resource* GetResource() const;

private:
  ID3D12Resource* myConstantBuffer_p = nullptr;
  uint            myByteSize       = 0u;
};