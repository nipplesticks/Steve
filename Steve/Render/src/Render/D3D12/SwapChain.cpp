#include "pch.h"
#include "Render/D3D12/SwapChain.h"

using namespace Render;

Render::SwapChain::SwapChain()
    : DXGI_SWAP_CHAIN_DESC1 {}
{
  Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
  Stereo             = FALSE;
  SampleDesc.Count   = 1;
  SampleDesc.Quality = 0;
  BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  Scaling            = DXGI_SCALING_NONE;
  SwapEffect         = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  Flags              = 0;
  AlphaMode          = DXGI_ALPHA_MODE_UNSPECIFIED;
}

void Render::SwapChain::Create(HWND               hwnd,
                               uint32             width,
                               uint32             height,
                               uint32             numSwapBuffers,
                               ID3D12CommandQueue* commandQueue_p)
{
  IDXGISwapChain1* swapChain1_p = nullptr;
  Width                         = width;
  Height                        = height;
  BufferCount                   = numSwapBuffers;

  IDXGIFactory5* factory_p = nullptr;
  HR_ASSERT(CreateDXGIFactory(IID_PPV_ARGS(&factory_p)));
  HR_ASSERT(factory_p->CreateSwapChainForHwnd(
      commandQueue_p, hwnd, this, nullptr, nullptr, &swapChain1_p));
  HR_ASSERT(swapChain1_p->QueryInterface(IID_PPV_ARGS(&mySwapChain_p)));
  SafeRelease(&swapChain1_p);
  myBackBufferIdx = mySwapChain_p->GetCurrentBackBufferIndex();
  SafeRelease(&factory_p);
  
  myViewport.Width    = (float)width;
  myViewport.Height   = (float)height;
  myViewport.MinDepth = D3D12_MIN_DEPTH;
  myViewport.MaxDepth = D3D12_MAX_DEPTH;
  myRect.right        = (long)INT_MAX;
  myRect.bottom       = (long)INT_MAX;




}

uint16 Render::SwapChain::GetSwapBufferIndex() const
{
  return myBackBufferIdx;
}

IDXGISwapChain4* Render::SwapChain::GetSwapChain() const
{
  return mySwapChain_p;
}

const D3D12_VIEWPORT& Render::SwapChain::GetViewport() const
{
  return myViewport;
}

const D3D12_RECT& Render::SwapChain::GetScissorRect() const
{
  return myRect;
}
