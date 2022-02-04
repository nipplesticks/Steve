#pragma once

#include "../buffers/ConstantBuffer.h"
#include <vector>

struct ID3D12DescriptorHeap;
class TextureBuffer;

class ResourceDescriptorHeap
{
public:
  void Create(const std::vector<ConstantBuffer*>& constantBuffers,
              const std::vector<TextureBuffer*>  textureBuffers);

  void Create(const std::vector<ConstantBuffer*>& constantBuffers);

  void Create(const std::vector<TextureBuffer*> textureBuffers);

  ID3D12DescriptorHeap*       GetDescriptorHeap() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetTextureHeapLocationStart() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetConstantBufferHeapLocationStart() const;

private:
  ID3D12DescriptorHeap* myHeap_p                  = nullptr;
  uint                  myNumberOfConstantBuffers = 0u;
};