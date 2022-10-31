#pragma once

#include "DescriptorHeap/ResourceDescriptorHeap.h"
#include "Resource/Rendertarget.h"
#include "D3D12/CommandHandler.h"

namespace Render
{
  class ImguiContext
  {
  private:
    ImguiContext()  = default;
    ~ImguiContext() = default;

  public:
    static void            Init(HWND hwnd, uint16 numSwapBuffers);
    static bool            ImguiEnabled();
    static DescriptorHeap* GetDescHeap();

  private:
    static DescriptorHeap gDescHeap;
    static bool           gImguiEnabled;
  };

} // namespace Render