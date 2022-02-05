#pragma once

#include "../../utility/Typedef.h"
#include <d3d12.h>
#include <vector>

struct ID3D12DescriptorHeap;
class TextureBuffer;
class ConstantBuffer;

class ResourceDescriptorHeap
{
public:
  void Create(const std::vector<ConstantBuffer*>& constantBuffers,
              const std::vector<TextureBuffer*>&  textureBuffers,
              const std::vector<TextureBuffer*>&  uavBuffers);

  void CreateWithConstantBuffers(const std::vector<ConstantBuffer*>& constantBuffers);

  void CreateWithTextureBuffers(const std::vector<TextureBuffer*>& textureBuffers);

  void CreateWithUAVBuffers(const std::vector<TextureBuffer*>& uavBuffers);

  ID3D12DescriptorHeap*       GetDescriptorHeap() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetTextureHeapLocationStart() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetConstantBufferHeapLocationStart() const;
  D3D12_GPU_DESCRIPTOR_HANDLE GetUAVBufferHeapLocationStart() const;

  bool HasUavs() const;
  bool HasConstantBuffers() const;
  bool HasTextures() const;

private:
  ID3D12DescriptorHeap* myHeap_p                  = nullptr;
  uint                  myNumberOfConstantBuffers = 0u;
  uint                  myNumberOfTextureBuffers  = 0u;
  bool                  myHasUavs                 = false;
  bool                  myHasCbs                  = false;
  bool                  myHasText                 = false;
};