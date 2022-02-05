#pragma once
#pragma once
#include "../../utility/Typedef.h"
#include <d3d12.h>

class Renderer;

class TextureBuffer
{
public:
  TextureBuffer()  = default;
  ~TextureBuffer() = default;

  void Init(uint width, uint height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
  void Update(Renderer* renderer_p, void* data_p);
  uint GetHeight() const;
  uint GetWidth() const;

  ID3D12Resource*       GetResource() const;
  ID3D12DescriptorHeap* GetHeap() const;
  D3D12_RESOURCE_STATES GetBeforeState() const;
  void                  SetState(D3D12_RESOURCE_STATES state);
  DXGI_FORMAT           GetFormat() const;
  uint                  GetNumberOfChannels() const;
  uint                  GetChannelEllementSize() const;
  uint                  GetRowPitch() const;

private:
  void _setChannelInfo();

private:
  ID3D12Resource*       myTextureBuffer_p    = nullptr;
  ID3D12DescriptorHeap* myHeap_p             = nullptr;
  uint                  myWidth              = 0u;
  uint                  myHeight             = 0u;
  D3D12_RESOURCE_STATES myStateBefore        = D3D12_RESOURCE_STATE_COPY_DEST;
  DXGI_FORMAT           myFormat             = DXGI_FORMAT_UNKNOWN;
  uint                  myNumberOfChannels   = 4;
  uint                  myChannelElementSize = 1;
};