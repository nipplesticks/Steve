#include "Input/KeyboardInput.h"
#include "World/Planet.h"
#include "events/EventHandler.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/FpsCamera.h"
#include "renderer/OrbitCamera.h"
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

DM::Mat3x3 FindRotationMatrix2(const DM::Vec3f& A, const DM::Vec3f& B)
{
  DM::Vec3f axis = A.Cross(B);

  const float cosA = A.Dot(B);
  const float k    = 1.0f / (1.0f + cosA);

  DM::Mat3x3 result;
  result._11 = (axis.x * axis.x * k) + cosA;
  result._12 = (axis.y * axis.x * k) - axis.z;
  result._13 = (axis.z * axis.x * k) + axis.y;
  result._21 = (axis.x * axis.y * k) + axis.z;
  result._22 = (axis.y * axis.y * k) + cosA;
  result._23 = (axis.z * axis.y * k) - axis.x;
  result._31 = (axis.x * axis.z * k) - axis.y;
  result._32 = (axis.y * axis.z * k) + axis.x;
  result._33 = (axis.z * axis.z * k) + cosA;

  return result;
}


int main()
{
  Window   wnd(1280, 720, "aTitle");
  Renderer::Init(1280, 720, wnd.GetHwnd());
  Camera::InitViewProjectionCb();

  Renderer* ren_p = Renderer::GetInstance();

  FpsCamera camera;
  camera.SetLookTo(0.0f, 0.0f, -20.0f);
  camera.SetPosition(0, 0, 11);

  GraphicsPipelineState planetPipelineState;
  //planetPipelineState.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
  planetPipelineState.SetVertexShader("assets/shaders/PlanetVertexShader.hlsl");
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
  Planet::GenerationType genType;
  genType.height.frequency  = 0.8;
  genType.height.exponent = 2.3;
  genType.moisture.exponent = 0.8;
  genType.moisture.frequency = 6.3;
  planet.Create(1.0f, 8, 1.0f, genType);
  planet.SetScale(10, 10, 10);
  planet.SetGraphicsPipelineState(&planetPipelineState);
  planet.Bind();
  
  Mesh skyboxMesh;
  skyboxMesh.LoadMesh("assets/models/Skybox/skybox.obj", false);
  TextureLoader::Image img = TextureLoader::LoadImageData("assets/models/Skybox/skybox.jpg");
  TextureBuffer        skyboxTextureBuff;
  skyboxTextureBuff.Init(img.width, img.height);
  skyboxTextureBuff.Update(ren_p, img.pixels.data());
  skyboxMesh.CreateBuffers();

  Drawable skybox;
  skybox.SetGraphicsPipelineState(&skyboxPipelineState);
  skybox.SetMesh(&skyboxMesh);
  skybox.SetTexture(&skyboxTextureBuff);
  skybox.Bind();

  float speed     = 0.001f;
  float zoomSpeed = 0.1f;
  float rollSpeed = 0.5f;
  Timer t;
  t.Start();

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
  KeyboardInput::SetAnActionToKey("close", (uint16)0x1B); // escape
  KeyboardInput::SetAnActionToKey("speed", (uint16)0x10); // shift

  bool lockMouse = false;
  DM::Vec2i mpLast;

  while (wnd.IsOpen() && !KeyboardInput::IsKeyPressed("close"))
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
                camera.Rotate(0, 0, mouseEvent_p->MouseDelta.x * rollSpeed * dt);
              }
              if (mouseEvent_p->LButtonPressed)
                camera.Rotate(dy, dx, 0.0f);
            }
            else
            {
              int x = mpLast.x;
              int y = mpLast.y;

              dx = ((float)mouseEvent_p->MousePosition.x - x) * -speed;
              dy = ((float)mouseEvent_p->MousePosition.y - y) * -speed;
              camera.Rotate(dy, dx, 0.0f);
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
          }
          delete events[i];
        }
      }
    }

    float speedModifier = 1.0f;
    if (KeyboardInput::IsKeyPressed("speed"))
    {
      speedModifier = 10.0f;
    }

    if (KeyboardInput::IsKeyPressed("forward"))
      camera.Move(camera.GetRelativeForward() * dt * speedModifier);
    if (KeyboardInput::IsKeyPressed("back"))
      camera.Move(camera.GetRelativeForward() * -dt * speedModifier);
    if (KeyboardInput::IsKeyPressed("right"))
      camera.Move(camera.GetRelativeRight() * dt * speedModifier);
    if (KeyboardInput::IsKeyPressed("left"))
      camera.Move(camera.GetRelativeRight() * -dt * speedModifier);
    if (KeyboardInput::IsKeyPressed("up"))
      camera.Move(camera.GetRelativeUp() * dt * speedModifier);
    if (KeyboardInput::IsKeyPressed("down"))
      camera.Move(camera.GetRelativeUp() * -dt * speedModifier);

    if (KeyboardInput::IsKeyPressed("rollRight"))
      camera.Rotate(0, 0, dt);
    if (KeyboardInput::IsKeyPressed("rollLeft"))
      camera.Rotate(0, 0, -dt);

    planet.Rotate(0, rotationSpeed* dt* DirectX::XM_PI, 0);
    planet.UpdateConstantBuffer();
    
    skybox.SetPosition(camera.GetPosition());
    skybox.UpdateConstantBuffer();

    // Must be first
    ren_p->BeginFrame();

    ren_p->Clear(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
    camera.SetAsMainCameraAndUpdate();
    planet.Draw();
    skybox.Draw();

    // Must be last
    ren_p->EndFrame();
  }

  return 0;
}