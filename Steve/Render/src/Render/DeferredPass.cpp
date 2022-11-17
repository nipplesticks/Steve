#include "pch.h"
#include "Render/DeferredPass.h"
#include "Render/Mesh/Vertex.h"

using namespace Render;

VertexBuffer                        DeferredPass::gVertexBuffer;
IndexBuffer                         DeferredPass::gIndexBuffer;
GraphicalPipelineState              DeferredPass::gGraphicalPipelineState;
std::vector<ResourceDescriptorHeap> DeferredPass::gResourceDescHeap;

void Render::DeferredPass::Init()
{
  VertexLight quad[] = {{{-1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                         {{-1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f}},
                         {{1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, -1.0f}},
                         {{1.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}};

  gVertexBuffer.Create("deferredVertexBuffer", sizeof(VertexLight), 4);
  gIndexBuffer.Create("deferredIndexBuffer", 6);
  gVertexBuffer.Update(quad);
  uint32 indices[] = {0, 1, 2, 0, 2, 3};
  gIndexBuffer.Update(indices);
  // TODO Get the relative path to the shaders
  gGraphicalPipelineState.SetVertexShader("D:/Projects/Steve/Steve/Render/Shaders/DeferredRendering/VertexShader.hlsl");
  gGraphicalPipelineState.SetPixelShader("D:/Projects/Steve/Steve/Render/Shaders/DeferredRendering/PixelShader.hlsl");
  gGraphicalPipelineState.GenerateInputElementDesc();

  gGraphicalPipelineState.NumRenderTargets                = 1;
  for (auto& rtvF : gGraphicalPipelineState.RTVFormats)
    rtvF = DXGI_FORMAT_UNKNOWN;
  gGraphicalPipelineState.RTVFormats[0]                   = DXGI_FORMAT_R8G8B8A8_UNORM;
  gGraphicalPipelineState.DepthStencilState.DepthEnable   = FALSE;
  gGraphicalPipelineState.DepthStencilState.StencilEnable = FALSE;
  gGraphicalPipelineState.AllowWireframe(false);

  gGraphicalPipelineState.CreatePipelineState("deferredPipelineState");
}

void Render::DeferredPass::AppendRenderTargets(const std::vector<Resource*>& renderTargets)
{
  static uint16 swapBuffer = 0;
  gResourceDescHeap.push_back(ResourceDescriptorHeap());
  gResourceDescHeap.back().CreateAndBindResources(
      "deferredDescHeap_" + std::to_string(swapBuffer),
      {Renderer::GetInstance()->GetCameraConstantBuffer()},
      renderTargets,
      {});
}

VertexBuffer* Render::DeferredPass::GetVertexBuffer()
{
  return &gVertexBuffer;
}

IndexBuffer* Render::DeferredPass::GetIndexBuffer()
{
  return &gIndexBuffer;
}

GraphicalPipelineState* Render::DeferredPass::GetPipelineState()
{
  return &gGraphicalPipelineState;
}

ResourceDescriptorHeap* Render::DeferredPass::GetResourceDescHeap(uint16 swapBufferIdx)
{
  return &gResourceDescHeap[swapBufferIdx];
}
