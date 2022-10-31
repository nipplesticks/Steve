#include "pch.h"
#include "Render/ImguiContext.h"

Render::DescriptorHeap Render::ImguiContext::gDescHeap;
bool                   Render::ImguiContext::gImguiEnabled = false;
;

void Render::ImguiContext::Init(HWND hwnd, uint16 numSwapBuffers)
{
  gDescHeap.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  gDescHeap.NumDescriptors = 1;
  gDescHeap.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  gDescHeap.Create("ImguiDescriptorHeap");

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  ImGui::StyleColorsDark();
  ASSERT(ImGui_ImplWin32_Init(hwnd));
  ASSERT(ImGui_ImplDX12_Init(Device::GetDevice(),
                             numSwapBuffers,
                             DXGI_FORMAT_R8G8B8A8_UNORM,
                             gDescHeap.GetDescHeap(),
                             gDescHeap.GetCpuDescHandle(),
                             gDescHeap.GetGpuDescHandle()));

  gImguiEnabled = true;
}

bool Render::ImguiContext::ImguiEnabled()
{
  return gImguiEnabled;
}

Render::DescriptorHeap* Render::ImguiContext::GetDescHeap()
{
  return &gDescHeap;
}

void Render::ImguiContext::Render(ID3D12GraphicsCommandList* commandList_p)
{
  ImGui::Render();
  ID3D12DescriptorHeap* heap_p = gDescHeap.GetDescHeap();
  commandList_p->SetDescriptorHeaps(1, &heap_p);
  ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList_p);
}
