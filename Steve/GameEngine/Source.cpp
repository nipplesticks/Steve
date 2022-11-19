#include "pch.h"
#include <Render/Window/Window.h>
#include <Render/Render/Renderer.h>
#include <Render/Render/Mesh/MeshLoader.h>
#include <Render/Render/Objects/Drawable.h>
#include <Render/Render/Camera/Camera.h>
#include <iostream>
#include "Timer.h"
#include "game/characters/Player.h"

void CenterMouse(Render::Window* wnd)
{
  wnd->SetMousePosition(DM::Vec2i(1280, 720) / 2);
}

int main()
{
  Render::Window wnd(1280, 720);
  Render::Renderer::Init(wnd, false);
  Render::Renderer* gRenderer_p = Render::Renderer::GetInstance();
  Render::MeshLoader::LoadMesh("assets/cat/12221_Cat_v1_l3.obj", "model");
  Render::GraphicalPipelineState state;
  state.SetVertexShader(Render::GraphicalPipelineState::DEFAULT_VERTEX_SHADER);
  state.SetPixelShader(Render::GraphicalPipelineState::DEFAULT_PIXEL_SHADER);
  state.GenerateInputElementDesc();
  state.CreatePipelineState("modelState");
  Render::Drawable model;
  model.SetMesh(Render::MeshLoader::GetMesh("model"));
  model.SetGraphicalPipelineState(&state);
  model.CreateGPUData();
  model.SetScale(.01f);
  model.SetRotation(90, 0, 0);
  {
    SettingsContext::GetInstance()->SetClientCenter(DM::Vec2i(1280, 720) / 2);
  }

  Player player;

  Timer timer;
  timer.Start();
  while (wnd.IsOpen() && !GetAsyncKeyState('O'))
  {
    float dt = timer.Stop();
    wnd.PollEvents();
    Render::Event::EventHandler::HandleEvents();
    player.Update(dt);

    gRenderer_p->BeginFrame(&player);
    model.Draw();
    gRenderer_p->EndFrame();
    CenterMouse(&wnd);
  }

  return 0;
}