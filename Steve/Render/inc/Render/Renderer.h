#pragma once

#include "DescriptorHeap/ResourceDescriptorHeap.h"
#include "Resource/Rendertarget.h"
#include "D3D12/CommandHandler.h"
#include "D3D12/SwapChain.h"
#include "D3D12/Fence.h"
#include "Resource/DepthBuffer.h"
#include "../Window/WindowEvent.h"
#include "ImguiContext.h"

namespace Render
{
  constexpr uint32 NUM_SWAP_BUFFERS = 2;

  class Resource;
  class Drawable;
  class Computational;
  class Window;

  class Renderer : public Event::Subscriber
  {
  private:
    static Renderer gRenderer;
    Renderer()  = default;
    ~Renderer() = default;

  public:
    static void      Init(const Window& window, bool enableDebug = false);
    static Renderer* GetInstance();

    void BeginFrame();
    void EndFrame();
    void BeginCompute();
    void EndCompute();
    void Clear(const DM::Vec4f& color = DM::Vec4f());
    void Draw(Drawable* drawable_p);
    void Compute(Computational* computational_p);

    virtual void HandleEvent(const Event::Message& message) override;

  private:
    void _Init(HWND hwnd, uint16 width, uint16 height);
    void _CreateRenderTargets(const DM::Vec2u& res);
    void _CreateDepthBuffers(const DM::Vec2u& res);

  private:
    HWND             myTargetWindow = NULL;
    DescriptorHeap   myRendertargetHeap;
    DescriptorHeap   myDeferredRendertargetHeap;
    DescriptorHeap   myDepthBufferHeap;
    DepthBuffer      myDepthBuffers[NUM_SWAP_BUFFERS];
    ID3D12Resource1* myRenderTargets_pp[NUM_SWAP_BUFFERS];
    RenderTarget     myDeferredRendertargets[NUM_SWAP_BUFFERS]
                                        [RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES];
    ResourceDescriptorHeap myDeferredResourceDescHeap[NUM_SWAP_BUFFERS];
    CommandHandler         myGraphicsCommands;
    SwapChain              mySwapChain;
    Fence                  myFence;
  };
} // namespace Render