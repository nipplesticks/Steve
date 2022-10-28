#pragma once

#include <string>
#include <dxgi1_6.h>

namespace Render
{
  class SwapChain : public DXGI_SWAP_CHAIN_DESC1
  {
  public:
    SwapChain();
    void Create(HWND               hwnd,
                uint32             width,
                uint32             height,
                uint32             numSwapBuffers,
                ID3D12CommandQueue* commandList_p);

    uint16                GetSwapBufferIndex() const;
    IDXGISwapChain4*      GetSwapChain() const;
    const D3D12_VIEWPORT& GetViewport() const;
    const D3D12_RECT&     GetScissorRect() const;

  private:
    IDXGISwapChain4* mySwapChain_p   = nullptr;
    uint16           myBackBufferIdx = 0;
    D3D12_VIEWPORT   myViewport      = {};
    D3D12_RECT       myRect          = {};
  };
} // namespace Render