#include "window/Window.h"
#include "renderer/Renderer.h"

int main()
{
  Window wnd(1280, 720, "aTitle");
  Renderer ren(1280, 720, wnd.GetHwnd());
  while (wnd.IsOpen())
  {
    wnd.PollEvents();

    ren.Clear();
  }


  return 0;
}