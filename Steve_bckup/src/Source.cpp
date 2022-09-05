#include "Input/InputRouter.h"
#include "World/Map.h"
#include "World/Star.h"
#include "events/EventHandler.h"
#include "renderer/buffers/Resource.h"
#include "renderer/camera/FpsCamera.h"
#include "renderer/d3d12/ResourceDescriptorHeap.h"
#include "renderer/d3d12/myRenderer.h"
#include "renderer/mesh/MeshLoader.h"
#include "renderer/textureLoader/TextureHandler.h"
#include "tools/WorldMeshGen.h"
#include "utility/Timer.h"
#include "window/Window.h"
#include <iostream>
#include "player/LocalPlayer.h"

Map* map_p = nullptr;

bool PlanetGeneration(Noise& heightNoise,
                      Noise& diffuseNoise,
                      float& waterLevel,
                      float& planetScale);


int main()
{
  InputRouter::GetInstance();

  // Earth area
  // 510100000 * 1000000 m2
  // A = 4*Pi*r^2
  // r = sqrt(A / (4*Pi))
  uint64 earthScale = 8000;
  uint64 earthAreaKm2  = 510100000;
  uint64 targetAreaKm2 = earthAreaKm2 / earthScale;

  float planetRadiusMeters = (1000.f * (float)sqrt(targetAreaKm2 / (double)(4.0f * DM::PI)));
  planetRadiusMeters       = 500;
  Window wnd(1920, 1080, "Steve in the house");
  //MyRenderer::ENABLE_DEBUG_CONTROLLER = true;
  MyRenderer::Init(wnd.GetHwnd());
  Camera::InitViewProjectionCb();
  MyRenderer* renderer_p = MyRenderer::GetInstance();
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

  LocalPlayer player;
  player.SetPosition(0.0f, planetRadiusMeters, 0);

  Star mainStar;
  {
    Light     l   = mainStar.GetLight();
    DM::Vec3f dir = l.direction;
    mainStar.SetPosition(dir * -planetRadiusMeters*1.5f);
    mainStar.SetScale(10, 10, 10);
  }

  Noise heightMapGenerator  = {};
  Noise diffuseMapGenerator = {};
  float waterLevel          = 0.4f;
  float planetScale         = planetRadiusMeters;

  Map planet;
  map_p = &planet;
  planet.Create();
  planet.GenerateMap(heightMapGenerator, diffuseMapGenerator);
  planet.SetScale(planetScale, planetScale, planetScale);

  Timer frameTimer;
  frameTimer.Start();
  uint c = 0;
  while (wnd.IsOpen())
  {
    float dt = (float)frameTimer.Stop();
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    wnd.PollEvents();
    EventHandler::HandleEvents();

//    float h = planet.GetHightLevelAt(player.GetPosition());

    player.Update(dt, planet.GetScale().x);
    wnd.SetMousePosition(player.mpLast.x, player.mpLast.y);

    mainStar.UpdateWorldMatrixConstantBuffer();

    planet.Update(dt, player.GetCamera());
    renderer_p->BeginFrame();
    renderer_p->Clear();
    planet.Draw();
    mainStar.Draw();
    skybox.Draw();
    renderer_p->EndFrame();
    c++;
  }

  return 0;
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

bool PlanetGeneration(Noise& heightNoise,
                      Noise& diffuseNoise,
                      float& waterLevel,
                      float& planetScale)
{
  bool somethingChanged = false;
  ImGui::Begin("Planet Generation Modifier");

  ImGui::Text("Generic");
  ImGui::SliderFloat("planet size", &planetScale, 1, 100000);
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