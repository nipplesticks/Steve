#pragma once
#include "../utility/Typedef.h"
#include <d3d12.h>

class VertexBuffer
{
public:
  VertexBuffer()  = default;
  ~VertexBuffer() = default;

  void Init(uint size, uint stride);
  void Update(void* data, uint size);

  ID3D12Resource*                 GetResource();
  const D3D12_VERTEX_BUFFER_VIEW& GetVBV() const;
  uint                            GetVertexCount() const;

private:
  ID3D12Resource*          myVertexBuffer_p   = nullptr;
  D3D12_VERTEX_BUFFER_VIEW myVertexBufferView = {};
  uint                     myNumVertices      = 0u;
};