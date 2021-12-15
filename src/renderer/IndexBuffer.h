#pragma once
#include "../utility/Typedef.h"
#include <d3d12.h>

class IndexBuffer
{
public:
  IndexBuffer()  = default;
  ~IndexBuffer() = default;

  void Init(uint indexCount);
  void Update(void* data);

  ID3D12Resource*                GetResource();
  const D3D12_INDEX_BUFFER_VIEW& GetIBV() const;
  uint                           GetIndexCount() const;

private:
  ID3D12Resource*         myIndexBuffer_p  = nullptr;
  D3D12_INDEX_BUFFER_VIEW myIndexBufferView = {};
  uint                    myNumIndices      = 0u;
};