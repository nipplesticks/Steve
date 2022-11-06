#include <Render/Window/Window.h>
#include <Render/Render/Renderer.h>
#include <Render/Render/Mesh/MeshLoader.h>
#include <Render/Render/Objects/Drawable.h>
#include <Render/Render/Camera/Camera.h>


int main()
{
  Render::Window wnd(1280, 720);
  Render::Renderer::Init(wnd, true);
  Render::Renderer* gRenderer_p = Render::Renderer::GetInstance();

  Render::MeshLoader::LoadMesh("assets/hot-girl/source/model.obj", "girl");
  Render::GraphicalPipelineState state;
  state.SetVertexShader(Render::GraphicalPipelineState::DEFAULT_VERTEX_SHADER);
  state.SetPixelShader(Render::GraphicalPipelineState::DEFAULT_PIXEL_SHADER);
  state.GenerateInputElementDesc();
  state.CreatePipelineState("womanState");

  Render::Drawable woman;
  woman.SetMesh(Render::MeshLoader::GetMesh("girl"));
  woman.SetGraphicalPipelineState(&state);
  woman.CreateGPUData();

  Render::Camera cam;
  cam.SetPosition(0, 0.5f, -3);
  
  while (wnd.IsOpen())
  {
    wnd.PollEvents();
    gRenderer_p->BeginFrame(&cam);

    woman.Draw();

    gRenderer_p->EndFrame();
  }

  return 0;
}