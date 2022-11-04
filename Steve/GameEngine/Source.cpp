#include <Render/Window/Window.h>
#include <Render/Render/Renderer.h>

int main()
{
  Render::Window wnd(1280, 720);
  Render::Renderer::Init(wnd, false);
  Render::Renderer* gRenderer_p = Render::Renderer::GetInstance();

  while (wnd.IsOpen())
  {
    wnd.PollEvents();
    gRenderer_p->BeginFrame();




    gRenderer_p->EndFrame();
  }



  return 0;
}