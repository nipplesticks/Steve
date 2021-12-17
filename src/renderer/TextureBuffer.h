#pragma once
#pragma once
#include "../utility/Typedef.h"
#include <d3d12.h>

class Renderer;

class TextureBuffer
{
public:
  TextureBuffer()  = default;
  ~TextureBuffer() = default;

  void Init(uint width, uint height, uint channels = 4u);
  void Update(Renderer* renderer_p, void* data_p);
  uint GetHeight() const;
  uint GetWidth() const;

  ID3D12Resource* GetResource() const;
  ID3D12DescriptorHeap* GetHeap() const;

private:
  ID3D12Resource*       myTextureBuffer_p = nullptr;
  ID3D12DescriptorHeap* myHeap_p          = nullptr;
  uint                  myWidth = 0u;
  uint                  myHeight = 0u;
};