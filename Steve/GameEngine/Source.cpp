#include <RenderEngine/Window/Window.h>
#include <RenderEngine/Render/Renderer.h>

int main()
{
  Render::Window wnd(1280, 720);
  Render::Renderer::Init(wnd);



  return 0;
}