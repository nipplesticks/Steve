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

    ren.Clear(Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
    ren.DrawTriangle();

    // Must be last
    ren.EndFrame();
  }

  return 0;
}