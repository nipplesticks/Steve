#include "Input/KeyboardInput.h"
#include "World/Planet.h"
#include "events/EventHandler.h"
#include "renderer/Camera2.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/FpsCamera.h"
#include "renderer/GraphicsPipelineState.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/ResourceDescriptorHeap.h"
#include "renderer/TextureBuffer.h"
#include "renderer/TextureLoader.h"
#include "renderer/VertexBuffer.h"
#include "utility/Timer.h"
#include "utility/UtilityFuncs.h"
#include "window/Window.h"
#include <iostream>

int main()
{
  Window   wnd(1280, 720, "aTitle");
  Renderer::Init(1280, 720, wnd.GetHwnd());
  Camera::InitViewProjectionCb();

  Renderer* ren_p = Renderer::GetInstance();

  FpsCamera fpsCam;
  fpsCam.SetPosition(0, 0, 11);
  fpsCam.SetLookTo(0.0f, 0.0f, -1.0f);
  auto up    = fpsCam.GetUp();
  auto right = fpsCam.GetRight();

  GraphicsPipelineState planetPipelineState;
  planetPipelineState.SetVertexShader("assets/shaders/VertexHelloTriangle.hlsl");
  planetPipelineState.SetPixelShader("assets/shaders/PixelHelloTriangle.hlsl");
  planetPipelineState.GenerateInputElementDesc();
  planetPipelineState.GenerateRootSignature();
  planetPipelineState.CreatePipelineState();

  GraphicsPipelineState skyboxPipelineState;
  skyboxPipelineState.SetVertexShader("assets/shaders/VertexSkybox.hlsl");
  skyboxPipelineState.SetPixelShader("assets/shaders/PixelSkybox.hlsl");
  skyboxPipelineState.GenerateInputElementDesc();
  skyboxPipelineState.GenerateRootSignature();
  skyboxPipelineState.CreatePipelineState();

  Planet planet;
  Drawable skybox;
  planet.Create(1.0f, 3, 1.0f);
  planet.SetGraphicsPipelineState(&planetPipelineState);
  planet.Bind();
  
  Mesh skyboxMesh;
  skyboxMesh.LoadMesh("assets/models/Skybox/skybox.obj", false);
  TextureLoader::Image img = TextureLoader::LoadImageData("assets/models/Skybox/skybox.jpg");
  TextureBuffer        skyboxTextureBuff;
  skyboxTextureBuff.Init(img.width, img.height);
  skyboxTextureBuff.Update(ren_p, img.pixels.data());
  skyboxMesh.CreateBuffers();

  skybox.SetGraphicsPipelineState(&skyboxPipelineState);
  skybox.SetMesh(&skyboxMesh);
  skybox.SetTexture(&skyboxTextureBuff);
  skybox.Bind();

  float speed     = 0.001f;
  float zoomSpeed = 0.1f;
  float rollSpeed = 0.5f;
  Timer t;
  t.Start();

  ConstantBuffer viewProjCbSkybox;
  viewProjCbSkybox.Init(sizeof(DM::Mat4x4));
  DM::Mat4x4 viewProjSkybox;
  viewProjSkybox.Store(DirectX::XMMatrixIdentity());
  viewProjCbSkybox.Update(&viewProjSkybox, sizeof(viewProjSkybox));

  ConstantBuffer viewProjCb;
  viewProjCb.Init(sizeof(DM::Mat4x4));
  DM::Mat4x4 viewProj;
  viewProj.Store(DirectX::XMMatrixIdentity());
  viewProjCb.Update(&viewProj, sizeof(viewProj));

  ConstantBuffer worldCb;
  worldCb.Init(sizeof(DM::Mat4x4));
  DM::Mat4x4 worldMat;
  worldMat.Store(DirectX::XMMatrixIdentity());
  worldCb.Update(&worldMat, sizeof(worldMat));

  float rotation      = 0.0f;
  float rotationSpeed = 0.01f;

  bool goForward = false;

  KeyboardInput::SetAnActionToKey("forward", (uint16)'W');
  KeyboardInput::SetAnActionToKey("back", (uint16)'S');
  KeyboardInput::SetAnActionToKey("right", (uint16)'D');
  KeyboardInput::SetAnActionToKey("left", (uint16)'A');
  KeyboardInput::SetAnActionToKey("up", 32); // space
  KeyboardInput::SetAnActionToKey("down", 17); // LCtrl
  KeyboardInput::SetAnActionToKey("rollLeft", (uint16)'Q');
  KeyboardInput::SetAnActionToKey("rollRight", (uint16)'E');
  KeyboardInput::SetAnActionToKey("toggleLockMouse", (uint16)'F');

  bool lockMouse = false;
  DM::Vec2i mpLast;

  while (wnd.IsOpen())
  {
    float dt = (float)t.Stop();

    wnd.PollEvents();
    KeyboardInput::Update();

    if (KeyboardInput::IsKeyFirstPressedThisFrame("toggleLockMouse"))
    {
      lockMouse = !lockMouse;
      if (lockMouse)
        ShowCursor(false);
      else
        ShowCursor(true);
    }

    {
      {
        std::vector<Event*> events = EventHandler::GetEvents(Event::Type::MouseMoved);
        EventHandler::ClearEvents(Event::Type::MouseMoved);
        if (!events.empty())
        {
          for (Event* event_p : events)
          {
            EventMouseMoved* mouseEvent_p = (EventMouseMoved*)event_p;
            float            dx           = ((float)mouseEvent_p->MouseDelta.x) * speed;
            float            dy           = ((float)mouseEvent_p->MouseDelta.y) * speed;
            if (!lockMouse)
            {
              mpLast                        = mouseEvent_p->MousePosition;
              if (mouseEvent_p->MButtonPressed)
              {
                //cam.Roll((-(float)mouseEvent_p->MouseDelta.x) * rollSpeed * dt);
                fpsCam.Rotate(0, 0, mouseEvent_p->MouseDelta.x * rollSpeed * dt);
              }
              if (mouseEvent_p->LButtonPressed)
                fpsCam.Rotate(dy, dx, 0.0f);
            }
            else
            {
              int x = mpLast.x;
              int y = mpLast.y;

              dx = ((float)mouseEvent_p->MousePosition.x - x) * -speed;
              dy = ((float)mouseEvent_p->MousePosition.y - y) * -speed;
              fpsCam.Rotate(dy, dx, 0.0f);
              wnd.SetMousePosition(mpLast.x, mpLast.y);
            }
          }
          for (uint i = 0; i < events.size(); i++)
            delete events[i];
        }
      }
    }
    {
      std::vector<Event*> events = EventHandler::GetEvents(Event::Type::MouseWheel);
      EventHandler::ClearEvents(Event::Type::MouseWheel);
      if (!events.empty())
      {

        for (uint i = 0; i < events.size(); i++)
        {
          EventMouseWheel* mouseEvent_p = (EventMouseWheel*)events[i];
          if (mouseEvent_p->Delta)
          {
            float z = (float)mouseEvent_p->Delta * zoomSpeed * dt;
            //cam.Zoom(z);
          }
          delete events[i];
        }
      }
    }

    if (KeyboardInput::IsKeyPressed("forward"))
      fpsCam.Move(fpsCam.GetRelativeForward() * dt);
    if (KeyboardInput::IsKeyPressed("back"))
      fpsCam.Move(fpsCam.GetRelativeForward() * -dt);
    if (KeyboardInput::IsKeyPressed("right"))
      fpsCam.Move(fpsCam.GetRelativeRight() * dt);
    if (KeyboardInput::IsKeyPressed("left"))
      fpsCam.Move(fpsCam.GetRelativeRight() * -dt);
    if (KeyboardInput::IsKeyPressed("up"))
      fpsCam.Move(fpsCam.GetRelativeUp() * dt);
    if (KeyboardInput::IsKeyPressed("down"))
      fpsCam.Move(fpsCam.GetRelativeUp() * -dt);

    if (KeyboardInput::IsKeyPressed("rollRight"))
      fpsCam.Rotate(0, 0, dt);
    if (KeyboardInput::IsKeyPressed("rollLeft"))
      fpsCam.Rotate(0, 0, -dt);

    planet.Rotate(0, rotationSpeed* dt* DirectX::XM_PI, 0);
    planet.UpdateConstantBuffer();
    fpsCam.SetAsMainCameraAndUpdate();
    skybox.SetPosition(fpsCam.GetPosition());
    skybox.UpdateConstantBuffer();

    // Must be first
    ren_p->BeginFrame();
    ren_p->Clear(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
    planet.Draw();
    skybox.Draw();

    // Must be last
    ren_p->EndFrame();
  }

  return 0;
}