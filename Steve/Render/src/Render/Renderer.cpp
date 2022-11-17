#include "pch.h"
#include "Render/Renderer.h"
#include "Render/DeferredPass.h"
#include "Render/Objects/Drawable.h"

using namespace Render;
Renderer Renderer::gRenderer;

struct CameraViewProjection
{
  DM::Mat4x4f viewMatrix;
  DM::Mat4x4f projectionMatrix;
  DM::Vec4f   position;
};

static inline std::string RenderTargetTypeToString(RenderTargetType type)
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
  Rootsignature::Init();
  ImguiContext::Init(window.GetHwnd(), NUM_SWAP_BUFFERS);
  gRenderer._Init(window.GetHwnd(), window.GetSize().x, window.GetSize().y);
}

Renderer* Render::Renderer::GetInstance()
{
  return &gRenderer;
}

void Render::Renderer::BeginFrame(Camera* camera_p, const DM::Vec4f& clearColor)
{
  myCamera_p = camera_p;
  ImGui_ImplDX12_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
  myGraphicsCommands.Reset();

  myGraphicsCommands.ResourceTransitionBarrier(myDeferredRendertargets[myCurrentBufferIndex],
                                               RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES,
                                               D3D12_RESOURCE_STATE_RENDER_TARGET);
  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleRtv = myDeferredRendertargetHeap.GetCpuDescHandle(
      myCurrentBufferIndex, RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES);

  D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleDsv =
      myDepthBufferHeap.GetCpuDescHandle(myCurrentBufferIndex);

  myGraphicsCommands.SetRenderTargets(
      RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES, &cpuDescHandleRtv, &cpuDescHandleDsv);

  _Clear(clearColor);
}

void Render::Renderer::EndFrame()
{
  if (myCamera_p)
  {
    CameraViewProjection cvp;
    cvp.viewMatrix       = myCamera_p->GetViewMatrix();
    cvp.projectionMatrix = myCamera_p->GetProjectionMatrix();
    cvp.position         = myCamera_p->GetPosition();
    myCameraConstantbuffer.Update(&cvp, D3D12_RESOURCE_STATE_GENERIC_READ, sizeof(cvp));
  }

  for (auto& drawable : Drawable::gDrawQueue)
  {
    Draw(drawable);
  }

  Drawable::gDrawQueue.clear();

  myGraphicsCommands.Close();
  myGraphicsCommands.Execute();
  myGraphicsCommands.HardWait();
  myGraphicsCommands.Reset();
  myGraphicsCommands.ResourceTransitionBarrier(myDeferredRendertargets[myCurrentBufferIndex],
                                               RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES,
                                               D3D12_RESOURCE_STATE_GENERIC_READ);

  // DeferredPass
  myGraphicsCommands.ResourceTransitionBarrier(myRenderTargets_pp[myCurrentBufferIndex],
                                               1,
                                               {D3D12_RESOURCE_STATE_PRESENT},
                                               D3D12_RESOURCE_STATE_RENDER_TARGET);

  auto handle = myRendertargetHeap.GetCpuDescHandle(myCurrentBufferIndex);

  myGraphicsCommands.SetRenderTargets(1, &handle, nullptr);
  myGraphicsCommands.ClearRtv(handle);

  Draw(DeferredPass::GetVertexBuffer(),
       DeferredPass::GetIndexBuffer(),
       DeferredPass::GetResourceDescHeap(myCurrentBufferIndex),
       DeferredPass::GetPipelineState());

  ImguiContext::Render(myGraphicsCommands.GetCommandList());

  myGraphicsCommands.ResourceTransitionBarrier(myRenderTargets_pp[myCurrentBufferIndex],
                                               1,
                                               {D3D12_RESOURCE_STATE_RENDER_TARGET},
                                               D3D12_RESOURCE_STATE_PRESENT);

  myGraphicsCommands.Close();
  myGraphicsCommands.Execute();
  mySwapChain.Display();
  myGraphicsCommands.HardWait();

  myCurrentBufferIndex = mySwapChain.GetSwapBufferIndex();
}

void Render::Renderer::BeginCompute() { }

void Render::Renderer::EndCompute() { }

void Render::Renderer::_Clear(const DM::Vec4f& clearColor)
{
  auto handle = myDepthBufferHeap.GetCpuDescHandle(myCurrentBufferIndex);
  myGraphicsCommands.ClearDsv(handle);

  handle = myDeferredRendertargetHeap.GetCpuDescHandle(
      myCurrentBufferIndex, RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES);

  myGraphicsCommands.ClearRtv(handle, clearColor, RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES);
}

void Render::Renderer::Draw(Drawable* drawable_p)
{
  drawable_p->UpdateConstantbuffer();
  Mesh*                   m_p   = drawable_p->GetMesh();
  ResourceDescriptorHeap* rdh_p = drawable_p->GetResourceDescriptorHeap();
  GraphicalPipelineState* gps_p = drawable_p->GetGraphicalPipelineState();
  Draw(m_p->GetVertexBuffer(), m_p->GetIndexBuffer(), rdh_p, gps_p);
}

void Render::Renderer::Draw(Resource*               vertexBuffer_p,
                            Resource*               indexBuffer_p,
                            ResourceDescriptorHeap* rdh_p,
                            GraphicalPipelineState* gps_p)
{
  ID3D12GraphicsCommandList4* cmd_p = myGraphicsCommands.GetCommandList();
  cmd_p->SetPipelineState(gps_p->GetPipelineState());
  auto& viewport = mySwapChain.GetViewport();
  auto& sciRect  = mySwapChain.GetScissorRect();
  cmd_p->RSSetViewports(1, &viewport);
  cmd_p->RSSetScissorRects(1, &sciRect);
  cmd_p->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  cmd_p->IASetVertexBuffers(0, 1, &vertexBuffer_p->GetView().vbv);
  cmd_p->IASetIndexBuffer(&indexBuffer_p->GetView().ibv);

  ID3D12DescriptorHeap* arr[1] = {rdh_p->GetDescHeap()};

  cmd_p->SetDescriptorHeaps(1, arr);
  if (rdh_p->HasCbvs())
    cmd_p->SetGraphicsRootDescriptorTable(0, rdh_p->GetCbvDescHandle());
  if (rdh_p->HasSrvs())
    cmd_p->SetGraphicsRootDescriptorTable(1, rdh_p->GetSrvDescHandle());
  if (rdh_p->HasUavs())
    cmd_p->SetGraphicsRootDescriptorTable(2, rdh_p->GetUavDescHandle());

  cmd_p->DrawIndexedInstanced(indexBuffer_p->GetElementCount(), 1, 0, 0, 0);
}

void Render::Renderer::Compute(Computational* computational_p) { }

void Render::Renderer::HandleEvent(const Event::Message& message) { }

void Render::Renderer::ResourceUpdate(Resource*             resource_p,
                                      void*                 data_p,
                                      uint64                dataSize,
                                      uint64                offset,
                                      D3D12_RESOURCE_STATES afterState)
{
  ID3D12Resource*       tmpResource_p = nullptr;
  D3D12_HEAP_PROPERTIES heapProp      = {};
  heapProp.Type                       = D3D12_HEAP_TYPE_UPLOAD;
  heapProp.CPUPageProperty            = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heapProp.MemoryPoolPreference       = D3D12_MEMORY_POOL_UNKNOWN;

  //D3D12_RESOURCE_DESC resDesc  = resource_p->GetResource()->GetDesc();
  UINT64              byteSize = resource_p->GetBufferSize();
  UINT64              rowSize  = resource_p->GetRowPitch();
  UINT                numRows  = resource_p->GetNumberOfRows();
  D3D12_RESOURCE_DESC desc     = {};
  desc.Width                   = byteSize;
  desc.DepthOrArraySize        = 1;
  desc.Dimension               = D3D12_RESOURCE_DIMENSION_BUFFER;
  desc.Flags                   = D3D12_RESOURCE_FLAG_NONE;
  desc.Format                  = DXGI_FORMAT_UNKNOWN;
  desc.Height                  = 1;
  desc.Layout                  = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  desc.MipLevels               = 1;
  desc.SampleDesc.Count        = 1;
  desc.SampleDesc.Quality      = 0;
  HR_ASSERT(Device::GetDevice()->CreateCommittedResource(&heapProp,
                                                         D3D12_HEAP_FLAG_NONE,
                                                         &desc,
                                                         D3D12_RESOURCE_STATE_GENERIC_READ,
                                                         nullptr,
                                                         IID_PPV_ARGS(&tmpResource_p)));
  D3D12_SUBRESOURCE_DATA srdDesc = {};
  srdDesc.pData                  = data_p;
  srdDesc.RowPitch               = rowSize;
  srdDesc.SlicePitch             = srdDesc.RowPitch * numRows;

  if (resource_p->GetResourceType() == Resource::Resource_Type::StructuredBuffer && dataSize > 0)
  {
    srdDesc.RowPitch   = dataSize;
    srdDesc.SlicePitch = 1;
  }

  myUploadCommands.Reset();
  myUploadCommands.ResourceTransitionBarrier(resource_p, 1, D3D12_RESOURCE_STATE_COPY_DEST);
  ASSERT(UpdateSubresources(myUploadCommands.GetCommandList(),
                            resource_p->GetResource(),
                            tmpResource_p,
                            offset,
                            0,
                            1,
                            &srdDesc));
  myUploadCommands.ResourceTransitionBarrier(resource_p, 1, afterState);

  myUploadCommands.Close();
  myUploadCommands.Execute();
  myUploadCommands.HardWait();

  SafeRelease(&tmpResource_p);
}

void Render::Renderer::CopyResource(void*     outData_p,
                                    Resource* resource_p,
                                    uint64    dataSize,
                                    uint64    offset)
{

  D3D12_HEAP_PROPERTIES readbackHeapProperties {CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK)};
  D3D12_RESOURCE_DESC   readbackBufferDesc {
      CD3DX12_RESOURCE_DESC::Buffer(resource_p->GetBufferSize())};
  ID3D12Resource1* readbackBuffer_p = nullptr;
  HR_ASSERT(Device::GetDevice()->CreateCommittedResource(&readbackHeapProperties,
                                                         D3D12_HEAP_FLAG_NONE,
                                                         &readbackBufferDesc,
                                                         D3D12_RESOURCE_STATE_COPY_DEST,
                                                         nullptr,
                                                         IID_PPV_ARGS(&readbackBuffer_p)));
  if (dataSize == 0)
    dataSize = resource_p->GetBufferSize() - offset;

  auto beforeState = resource_p->GetState();
  myUploadCommands.Reset();
  myUploadCommands.ResourceTransitionBarrier(resource_p, 1, D3D12_RESOURCE_STATE_COPY_SOURCE);
  myUploadCommands.GetCommandList()->CopyResource(readbackBuffer_p, resource_p->GetResource());
  myUploadCommands.ResourceTransitionBarrier(resource_p, 1, beforeState);
  myUploadCommands.Close();
  myUploadCommands.Execute();
  myUploadCommands.HardWait();

  D3D12_RANGE readbackBufferRange {offset, dataSize};
  HR_ASSERT(readbackBuffer_p->Map(0, &readbackBufferRange, &outData_p));
  D3D12_RANGE emptyRange {};
  readbackBuffer_p->Unmap(0, &emptyRange);
  SafeRelease(&readbackBuffer_p);
}

Render::ConstantBuffer* Render::Renderer::GetCameraConstantBuffer()
{
  return &myCameraConstantbuffer;
}

void Render::Renderer::_Init(HWND hwnd, uint16 width, uint16 height)
{
  myTargetWindow = hwnd;
  myGraphicsCommands.Create("GraphicsCommand", D3D12_COMMAND_LIST_TYPE_DIRECT);
  myUploadCommands.Create("UploadCommand", D3D12_COMMAND_LIST_TYPE_DIRECT);
  mySwapChain.Create(hwnd, width, height, NUM_SWAP_BUFFERS, myGraphicsCommands.GetCommandQueue());
  myCurrentBufferIndex = mySwapChain.GetSwapBufferIndex();

  myRendertargetHeap.NumDescriptors = NUM_SWAP_BUFFERS;
  myRendertargetHeap.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  myRendertargetHeap.Create("RendertargetHeap");

  myCameraConstantbuffer.Create("CameraConstantBuffer", sizeof(CameraViewProjection));

  myDeferredRendertargetHeap.NumDescriptors =
      NUM_SWAP_BUFFERS * RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES;
  myDeferredRendertargetHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  myDeferredRendertargetHeap.Create("DeferredRendertargetHeap");

  _CreateRenderTargets(DM::Vec2u(width, height));
  _CreateDepthBuffers(DM::Vec2u(width, height));


  // TODO init compute interface

  DeferredPass::Init();

#ifndef _DEBUG
  BeginFrame(nullptr);
  EndFrame();
#endif
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
    DeferredPass::AppendRenderTargets(renderTargets);
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
    cdh.ptr += myDepthBufferHeap.GetDescHeapSize();
  }
}
