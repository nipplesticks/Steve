#pragma once

#include "Window/WindowEvent.h"
#include "DescriptorHeap/ResourceDescriptorHeap.h"
#include "Resource/Rendertarget.h"

namespace Render
{
  constexpr uint32 NUM_SWAP_BUFFERS = 2;

  class Resource;
  class Drawable;
  class Computational;

  class Renderer : public Event::Subscriber
  {
  private:
    static Renderer gRenderer;
    Renderer()  = default;
    ~Renderer() = default;

  public:
    static Renderer* GetInstance();

    void BeginFrame();
    void EndFrame();
    void BeginCompute();
    void EndCompute();
    void Clear(const DM::Vec4f& color = DM::Vec4f());
    void Draw(Drawable* drawable_p);
    void Compute(Computational* computational_p);

    virtual void HandleEvent(const Event::Message& message);

  private:
    DescriptorHeap myRendertargetHeap;
    DescriptorHeap myDeferredRendertargetHeap;
    DescriptorHeap myDepthBufferHeap;
    DescriptorHeap myImguiHeap;
    RenderTarget   myDeferredRendertargets[NUM_SWAP_BUFFERS]
                                        [RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES];
    ResourceDescriptorHeap myDeferredResourceDescHeap[NUM_SWAP_BUFFERS];
  };
} // namespace Render