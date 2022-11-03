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

    void BeginFrame(const DM::Vec4f& clearColor = DM::Vec4f(0, 0, 0, 0));
    void EndFrame();
    void BeginCompute();
    void EndCompute();
    void Draw(Drawable* drawable_p);
    void Draw(Resource*               vertexBuffer_p,
              Resource*               indexBuffer_p,
              ResourceDescriptorHeap* rdh_p,
              GraphicalPipelineState* gps_p);
    void Compute(Computational* computational_p);

    virtual void HandleEvent(const Event::Message& message) override;

    void ResourceUpdate(Resource*             resource_p,
                        void*                 data_p,
                        uint64                dataSize,
                        uint64                offset,
                        D3D12_RESOURCE_STATES afterState);
    void CopyResource(void* outData_p, Resource* resource_p, uint64 dataSize = 0, uint64 offset = 0);

  private:
    void _Clear(const DM::Vec4f& clearColor);
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
    CommandHandler myGraphicsCommands;
    CommandHandler myUploadCommands;
    SwapChain      mySwapChain;
    uint16         myCurrentBufferIndex = 0;
  };
} // namespace Render