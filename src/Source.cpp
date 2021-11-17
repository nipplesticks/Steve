#include "window/Window.h"
#include "renderer/Renderer.h"

int main()
{
  Window wnd(1280, 720, "aTitle");
  Renderer ren(1280, 720, wnd.GetHwnd());

  while (wnd.IsOpen())
  {
    wnd.PollEvents();

    // Must be first
    ren.BeginFrame();
    ren.Clear();

    // Must be last
    ren.EndFrame();
  }

  return 0;
}