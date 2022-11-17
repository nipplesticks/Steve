#include <Render/Window/Window.h>
#include <Render/Render/Renderer.h>
#include <Render/Render/Mesh/MeshLoader.h>
#include <Render/Render/Objects/Drawable.h>
#include <Render/Render/Camera/Camera.h>
#include <iostream>
#include "Timer.h"

int main()
{
  Render::Window wnd(1280, 720);
  Render::Renderer::Init(wnd, false);
  Render::Renderer* gRenderer_p = Render::Renderer::GetInstance();

  Render::MeshLoader::LoadMesh("assets/hot-girl/source/model.obj", "girl");
  Render::GraphicalPipelineState state;
  //state.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
  state.SetVertexShader(Render::GraphicalPipelineState::DEFAULT_VERTEX_SHADER);
  state.SetPixelShader(Render::GraphicalPipelineState::DEFAULT_PIXEL_SHADER);
  state.GenerateInputElementDesc();
  state.CreatePipelineState("womanState");

  Render::Drawable woman;
  woman.SetMesh(Render::MeshLoader::GetMesh("girl"));
  woman.SetGraphicalPipelineState(&state);
  woman.CreateGPUData();

  //woman.SetScale(1, -1, 1);

  Render::Camera cam;;
  cam.SetPosition(0, 0, -2);
  
  Timer timer;
  timer.Start();


  float rSpeedD = 90.0f;
  float mSpeedD = 1.f;

  while (wnd.IsOpen())
  {
    float dt = timer.Stop();
    wnd.PollEvents();
    gRenderer_p->BeginFrame(&cam);

    float rSpeed = rSpeedD * dt;
    float mSpeed = mSpeedD * dt;

    if (GetAsyncKeyState('D'))
      cam.Rotate(0, rSpeed, 0);
    if (GetAsyncKeyState('A'))
      cam.Rotate(0, -rSpeed, 0);
    if (GetAsyncKeyState('S'))
      cam.Rotate(rSpeed, 0, 0);
    if (GetAsyncKeyState('W'))
      cam.Rotate(-rSpeed, 0, 0);
    if (GetAsyncKeyState('E'))
      cam.Rotate(0, 0, rSpeed);
    if (GetAsyncKeyState('Q'))
      cam.Rotate(0, 0, -rSpeed);

    if (GetAsyncKeyState(VK_LEFT))
      cam.Move(-mSpeed, 0, 0);
    if (GetAsyncKeyState(VK_RIGHT))
      cam.Move(mSpeed, 0, 0);
    if (GetAsyncKeyState(VK_UP))
      cam.Move(0, 0, mSpeed);
    if (GetAsyncKeyState(VK_DOWN))
      cam.Move(0.0f, 0, -mSpeed);
    if (GetAsyncKeyState(VK_SPACE))
      cam.Move(0, mSpeed, 0);
    if (GetAsyncKeyState(VK_LCONTROL))
      cam.Move(0.0f, -mSpeed, 0);

    std::cout << "\rfor: " << cam.GetForward().ToString()
              << " pos: " << cam.GetPosition().ToString() << "up: " << cam.GetUp().ToString();


    woman.Draw();

    gRenderer_p->EndFrame();
  }

  return 0;
}