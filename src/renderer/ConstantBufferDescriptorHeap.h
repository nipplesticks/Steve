#pragma once

#include "ConstantBuffer.h"
#include <vector>

struct ID3D12DescriptorHeap;
class TextureBuffer;

class ConstantBufferDescriptorHeap
{
public:
  ConstantBufferDescriptorHeap() = default;
  ~ConstantBufferDescriptorHeap() = default;

  void Create(const std::vector<ConstantBuffer*>& constantBuffers, TextureBuffer* textureBuffer_p = nullptr);
  ID3D12DescriptorHeap* GetDescriptorHeap() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetTextureHeapLocationStart() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetConstantBufferHeapLocationStart() const;

private:
  ID3D12DescriptorHeap* myHeap_p = nullptr;
  uint                  myNumberOfConstantBuffers = 0u;
};