#include "pch.h"
#include "Render/Renderer.h"

using namespace Render;
Renderer Renderer::gRenderer;

static std::string RenderTargetTypeToString(RenderTargetType type)
{
  switch (type)
  {
  case Render::Position:
    return "Position";
  case Render::Normal:
    return "Normal";
  case Render::Color:
    return "Color";
  case Render::NUMBER_OF_RENDER_TARGET_TYPES:
  default:
    return "Unknown";
  }
}

void Render::Renderer::Init(const Window& window, bool enableDebug)
{
  Device::Init((Device::ENABLE_DEBUG_CONTROLLER | Device::ENABLE_DEBUG_LAYER) * enableDebug);
  gRenderer._Init(window.GetHwnd(), window.GetSize().x, window.GetSize().y);
}

Renderer* Render::Renderer::GetInstance()
{
  return &gRenderer;
}

void Render::Renderer::BeginFrame() { }

void Render::Renderer::EndFrame() { }

void Render::Renderer::BeginCompute() { }

void Render::Renderer::EndCompute() { }

void Render::Renderer::Clear(const DM::Vec4f& color) { }

void Render::Renderer::Draw(Drawable* drawable_p) { }

void Render::Renderer::Compute(Computational* computational_p) { }

void Render::Renderer::HandleEvent(const Event::Message& message) { }

void Render::Renderer::_Init(HWND hwnd, uint16 width, uint16 height)
{
  myTargetWindow = hwnd;
  myGraphicsCommands.Create("GraphicsCommand", D3D12_COMMAND_LIST_TYPE_DIRECT);
  mySwapChain.Create(hwnd, width, height, NUM_SWAP_BUFFERS, myGraphicsCommands.GetCommandQueue());
  myFence.Create("BasicFence");

  myRendertargetHeap.NumDescriptors = NUM_SWAP_BUFFERS;
  myRendertargetHeap.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  myRendertargetHeap.Create("RendertargetHeap");

  myDeferredRendertargetHeap.NumDescriptors =
      NUM_SWAP_BUFFERS * RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES;
  myDeferredRendertargetHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  myDeferredRendertargetHeap.Create("DeferredRendertargetHeap");

  _CreateRenderTargets(DM::Vec2u(width, height));
  _CreateDepthBuffers(DM::Vec2u(width, height));
}

void Render::Renderer::_CreateRenderTargets(const DM::Vec2u& res)
{
  auto                          renCdh = myRendertargetHeap.GetCpuDescHandle();
  auto                          defCdh = myDeferredRendertargetHeap.GetCpuDescHandle();
  D3D12_RENDER_TARGET_VIEW_DESC rtvd   = {};
  rtvd.ViewDimension                   = D3D12_RTV_DIMENSION_TEXTURE2D;

  auto swapChain_p = mySwapChain.GetSwapChain();

  for (uint32 i = 0; i < NUM_SWAP_BUFFERS; i++)
  {
    std::vector<Resource*> renderTargets(RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES);
    HR_ASSERT(swapChain_p->GetBuffer(i, IID_PPV_ARGS(&myRenderTargets_pp[i])));
    Device::GetDevice()->CreateRenderTargetView(myRenderTargets_pp[i], nullptr, renCdh);
    myRenderTargets_pp[i]->SetName(String::ToWString("RenderTarget_" + std::to_string(i)).c_str());
    renCdh.ptr += Device::GetRtvDescriptorHeapSize();

    for (uint16 j = 0; j < RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES; j++)
    {
      rtvd.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      myDeferredRendertargets[i][j].Create("deferredTarget_" +
                                               RenderTargetTypeToString(RenderTargetType(j)) + "_" +
                                               std::to_string(i),
                                           res.x,
                                           res.y,
                                           RenderTargetType(j),
                                           rtvd.Format);
      Device::GetDevice()->CreateRenderTargetView(
          myDeferredRendertargets[i][j].GetResource(), &rtvd, defCdh);
      defCdh.ptr += Device::GetRtvDescriptorHeapSize();
      renderTargets[j] = &myDeferredRendertargets[i][j];
    }
    myDeferredResourceDescHeap[i].CreateAndBindResources(
        "deferredResourceHeap_" + std::to_string(i), {}, renderTargets, {});
  }
}

void Render::Renderer::_CreateDepthBuffers(const DM::Vec2u& res)
{
  myDepthBufferHeap.NumDescriptors = NUM_SWAP_BUFFERS;
  myDepthBufferHeap.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
  myDepthBufferHeap.Create("DepthBufferHeap");


  D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
  dsvDesc.Format                        = DXGI_FORMAT_D32_FLOAT;
  dsvDesc.ViewDimension                 = D3D12_DSV_DIMENSION_TEXTURE2D;

  auto cdh = myDepthBufferHeap.GetCpuDescHandle();

  for (uint16 i = 0; i < NUM_SWAP_BUFFERS; i++)
  {
    myDepthBuffers[i].Create("DepthBuffer_" + std::to_string(i), res.x, res.y);
    Device::GetDevice()->CreateDepthStencilView(myDepthBuffers[i].GetResource(), &dsvDesc, cdh);
    cdh.ptr += Device::GetDsvDescriptorHeapSize();
  }
}
