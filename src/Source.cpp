#include "Input/KeyboardInput.h"
#include "World/Map.h"
#include "World/Star.h"
#include "events/EventHandler.h"
#include "renderer/buffers/Resource.h"
#include "renderer/camera/FpsCamera.h"
#include "renderer/d3d12/ResourceDescriptorHeap.h"
#include "renderer/d3d12/myRenderer.h"
#include "renderer/mesh/MeshLoader.h"
#include "renderer/textureLoader/TextureHandler.h"
#include "utility/Timer.h"
#include "window/Window.h"
#include <iostream>

Map* map_p = nullptr;

void SetupInput();
bool HandleInput(Camera* camera_p, float dt, Window* wnd_p);
bool PlanetGeneration(Noise& heightNoise,
                      Noise& diffuseNoise,
                      float& waterLevel,
                      float& planetScale);

int main()
{
  Window wnd(1280, 720, "Steve in the house");
  //MyRenderer::ENABLE_DEBUG_CONTROLLER = true;
  MyRenderer::Init(wnd.GetHwnd());
  Camera::InitViewProjectionCb();
  MyRenderer* renderer_p = MyRenderer::GetInstance();
  SetupInput();
  MeshLoader::LoadMesh("assets/models/Skybox/sphere.obj", "skybox", true);
  MeshLoader::LoadMesh("assets/models/Skybox/sphere.obj", "star", false);
  TextureHandler::LoadTexture("assets/textures/skybox.jpg", "skybox");
  GraphicsPipelineState skyboxPipeline;
  skyboxPipeline.SetVertexShader("assets/shaders/VertexSkybox.hlsl");
  skyboxPipeline.SetPixelShader("assets/shaders/PixelSkybox.hlsl");
  skyboxPipeline.GenerateInputElementDesc();
  skyboxPipeline.CreatePipelineState();
  Drawable skybox;
  skybox.SetMesh(MeshLoader::GetMesh("skybox"));
  skybox.SetTexture(TextureHandler::GetTexture("skybox"));
  skybox.SetGraphicsPipelineState(&skyboxPipeline);
  skybox.BindWithDefaultResourceDescHeap();

  FpsCamera camera;
  camera.SetLookTo(0.0f, 0.0f, -1.0f);
  camera.SetPosition(0, 0, 10);

  Star mainStar;
  {
    Light     l   = mainStar.GetLight();
    DM::Vec3f dir = l.direction;
    mainStar.SetPosition(dir * -100);
    mainStar.SetScale(10, 10, 10);
  }

  Noise heightMapGenerator  = {};
  Noise diffuseMapGenerator = {};
  float waterLevel          = 0.4f;
  float planetScale         = 1.0f;

  Map planet;
  map_p = &planet;
  planet.Create(8, 10);
  planet.SetWaterLevel(waterLevel);
  planet.GenerateMap(heightMapGenerator, diffuseMapGenerator);

  Timer frameTimer;
  frameTimer.Start();
  uint c = 0;
  while (wnd.IsOpen() && !KeyboardInput::IsKeyPressed("close"))
  {
    float dt = (float)frameTimer.Stop();
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    wnd.PollEvents();
    KeyboardInput::Update();
    if (HandleInput(&camera, dt, &wnd))
    {
      if (PlanetGeneration(heightMapGenerator, diffuseMapGenerator, waterLevel, planetScale))
      {
        planet.SetWaterLevel(waterLevel);
        planet.GenerateMap(heightMapGenerator, diffuseMapGenerator);
      }
      planet.SetScale(planetScale, planetScale, planetScale);
    }

    mainStar.UpdateWorldMatrixConstantBuffer();

    planet.Update(dt, &camera);
    renderer_p->BeginFrame();
    renderer_p->Clear();
    planet.Draw();
    mainStar.Draw();
    //skybox.Draw();
    renderer_p->EndFrame();
    c++;
  }

  return 0;
}

void SetupInput()
{
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
  KeyboardInput::SetAnActionToKey("toggleCaptureMouse", (uint16)'M');
  KeyboardInput::SetAnActionToKey("rotatePlanetRight", (uint16)'H');
  KeyboardInput::SetAnActionToKey("rotatePlanetLeft", (uint16)'G');
}

void CreateRay(const DM::Vec2f& mousePos, Camera* camera_p)
{
  Camera::View view        = camera_p->GetView();
  float        aspectRatio = view.width / view.height;

  float px = (2.0f * ((mousePos.x + 0.5) / view.width) - 1) *
             tan(view.fov / 2 * DirectX::XM_PI / 180.0f) * aspectRatio;
  float py = (1.0f - 2.0f * ((mousePos.y + 0.5f) / view.height)) *
             tan(view.fov / 2 * DirectX::XM_PI / 180.0f);

  DM::Vec3f   origin(0);
  DM::Mat4x4f viewMatrixInverse = camera_p->GetViewMatrix().Inverse();

  origin           = origin * viewMatrixInverse;
  DM::Vec3f p      = DM::Vec3f(px, py, -1) * viewMatrixInverse;
  DM::Vec3f rayDir = (p - origin).Normalize();

  float r = 2.0f * map_p->GetScale().x;

  DM::Vec3f m = origin - map_p->GetPosition();
  float     b = m.Dot(rayDir);
  float     c = m.Dot(m) - r * r;
  if (c > 0.0f && b > 0.0f)
    return;

  float discr = b * b - c;
  if (discr < 0.0f)
    return;

  float t = -b - sqrt(discr);
  if (t < 0.0f)
    t = 0.0f;

  DM::Vec3f intersectionPoint = origin + (rayDir * t);

  std::cout << "Hit at: " << intersectionPoint.ToString() << std::endl;
}

bool HandleInput(Camera* camera_p, float dt, Window* wnd_p)
{
  static bool      lockMouse           = false;
  static bool      disableMouseCapture = false;
  static float     speed               = 0.001f;
  static float     zoomSpeed           = 0.1f;
  static float     rollSpeed           = 0.5f;
  static DM::Vec2i mpLast;

  if (KeyboardInput::IsKeyFirstPressedThisFrame("toggleLockMouse"))
  {
    lockMouse = !lockMouse;
  }
  if (KeyboardInput::IsKeyFirstPressedThisFrame("toggleCaptureMouse"))
  {
    ShowCursor(true);
    lockMouse           = false;
    disableMouseCapture = !disableMouseCapture;
  }
  {
    std::vector<Event*> events = EventHandler::GetEvents(Event::Type::MouseMoved);
    EventHandler::ClearEvents(Event::Type::MouseMoved);
    if (!events.empty())
    {
      if (!disableMouseCapture)
      {
        for (Event* event_p : events)
        {
          EventMouseMoved* mouseEvent_p = (EventMouseMoved*)event_p;
          if (mouseEvent_p->RButtonPressed)
            CreateRay(mouseEvent_p->MousePosition, camera_p);
          float dx = ((float)mouseEvent_p->MouseDelta.x) * speed;
          float dy = ((float)mouseEvent_p->MouseDelta.y) * speed;
          if (!lockMouse)
          {
            mpLast = mouseEvent_p->MousePosition;
            if (mouseEvent_p->MButtonPressed)
            {
              camera_p->Rotate(0, 0, mouseEvent_p->MouseDelta.x * rollSpeed * dt);
            }
            if (mouseEvent_p->LButtonPressed)
              camera_p->Rotate(dy, dx, 0.0f);
          }
          else
          {
            int x = mpLast.x;
            int y = mpLast.y;

            dx = ((float)mouseEvent_p->MousePosition.x - x) * -speed;
            dy = ((float)mouseEvent_p->MousePosition.y - y) * -speed;
            camera_p->Rotate(dy, dx, 0.0f);
            wnd_p->SetMousePosition(mpLast.x, mpLast.y);
          }
        }
      }
      for (uint i = 0; i < events.size(); i++)
        delete events[i];
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
    camera_p->Move(camera_p->GetRelativeForward() * dt * speedModifier);
  if (KeyboardInput::IsKeyPressed("back"))
    camera_p->Move(camera_p->GetRelativeForward() * -dt * speedModifier);
  if (KeyboardInput::IsKeyPressed("right"))
    camera_p->Move(camera_p->GetRelativeRight() * dt * speedModifier);
  if (KeyboardInput::IsKeyPressed("left"))
    camera_p->Move(camera_p->GetRelativeRight() * -dt * speedModifier);
  if (KeyboardInput::IsKeyPressed("up"))
    camera_p->Move(camera_p->GetRelativeUp() * dt * speedModifier);
  if (KeyboardInput::IsKeyPressed("down"))
    camera_p->Move(camera_p->GetRelativeUp() * -dt * speedModifier);

  if (KeyboardInput::IsKeyPressed("rollRight"))
    camera_p->Rotate(0, 0, dt);
  if (KeyboardInput::IsKeyPressed("rollLeft"))
    camera_p->Rotate(0, 0, -dt);

  camera_p->SetAsMainCameraAndUpdate();

  return disableMouseCapture;
}

bool PlanetGeneration(Noise& heightNoise,
                      Noise& diffuseNoise,
                      float& waterLevel,
                      float& planetScale)
{
  bool somethingChanged = false;
  ImGui::Begin("Planet Generation Modifier");

  ImGui::Text("Generic");
  ImGui::SliderFloat("planet size", &planetScale, 1, 10);
  somethingChanged |= ImGui::SliderFloat("waterLevel", &waterLevel, 0.0f, 2.0f);
  ImGui::Checkbox("WireFrame: ", &GraphicsPipelineState::WIRE_FRAME);

  ImGui::Text("Height");
  {
    int _seedH = static_cast<int>(heightNoise.seed);
    int _it    = static_cast<int>(heightNoise.iterations);
    somethingChanged |= ImGui::SliderInt("height_seed", &_seedH, 0, INT_MAX / 2);
    somethingChanged |= ImGui::SliderFloat("height_exponent", &heightNoise.expnoent, 0.0f, 10.0f);
    somethingChanged |= ImGui::SliderFloat("height_frequency", &heightNoise.frequency, 0.0f, 10.0f);
    somethingChanged |=
        ImGui::SliderFloat("height_fudgeFactor", &heightNoise.fudgeFactor, 0.0f, 2.0f);
    somethingChanged |= ImGui::SliderInt("height_iterations", &_it, 0, 100);
    heightNoise.seed       = static_cast<uint>(_seedH);
    heightNoise.iterations = static_cast<uint>(_it);
  }
  ImGui::Text("Diffuse");
  {
    int _seedH = static_cast<int>(diffuseNoise.seed);
    int _it    = static_cast<int>(diffuseNoise.iterations);
    somethingChanged |= ImGui::SliderInt("diffuse_seed", &_seedH, 0, INT_MAX / 2);
    somethingChanged |= ImGui::SliderFloat("diffuse_exponent", &diffuseNoise.expnoent, 0.0f, 10.0f);
    somethingChanged |=
        ImGui::SliderFloat("diffuse_frequency", &diffuseNoise.frequency, 0.0f, 10.0f);
    somethingChanged |=
        ImGui::SliderFloat("diffuse_fudgeFactor", &diffuseNoise.fudgeFactor, 0.0f, 2.0f);
    somethingChanged |= ImGui::SliderInt("diffuse_iterations", &_it, 0, 100);
    diffuseNoise.seed       = static_cast<uint>(_seedH);
    diffuseNoise.iterations = static_cast<uint>(_it);
  }

  ImGui::End();
  return somethingChanged;
}