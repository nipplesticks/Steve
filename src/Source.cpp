#include "Input/KeyboardInput.h"
#include "Noise/PerlinNoise.h"
#include "World/Generation.h"
#include "World/Planet.h"
#include "events/EventHandler.h"
#include "renderer/buffers/ConstantBuffer.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/buffers/TextureBuffer.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/camera/FpsCamera.h"
#include "renderer/camera/OrbitCamera.h"
#include "renderer/d3d12/ComputationalPipeline.h"
#include "renderer/d3d12/GraphicsPipelineState.h"
#include "renderer/d3d12/Renderer.h"
#include "renderer/d3d12/ResourceDescriptorHeap.h"
#include "renderer/mesh/Mesh.h"
#include "renderer/textureLoader/TextureLoader.h"
#include "utility/Timer.h"
#include "utility/UtilityFuncs.h"
#include "window/Window.h"
#include <iostream>

void PlanetGenModifier(GenerationGPU& heightGeneration,
                       GenerationGPU& diffuseGeneration,
                       uint&          seed,
                       float&         waterLevel);

int main()
{
  Window wnd(1280, 720, "aTitle");
  Renderer::Init(1280, 720, wnd.GetHwnd());
  Camera::InitViewProjectionCb();

  Renderer* ren_p = Renderer::GetInstance();

  FpsCamera camera;
  camera.SetLookTo(0.0f, 0.0f, -1.0f);
  camera.SetPosition(0, 0, 101);

  GraphicsPipelineState planetPipelineState;
  //planetPipelineState.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
  //planetPipelineState.SetVertexShader("assets/shaders/PlanetVertexShader.hlsl");
  planetPipelineState.SetVertexShader("assets/shaders/PlanetVertexShaderWithOffset.hlsl");
  planetPipelineState.SetGeometryShader("assets/shaders/GeometryShaderCalcNormal.hlsl");
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

  Planet::GenerationType genType;
  genType.texWidth  = 512;
  genType.texHeight = 512;
  ASSERT(genType.texWidth % 32 == 0 && genType.texHeight % 32 == 0);

  Planet planet;
  planet.CreateOffsetGpu(1.0f, 8, 1.0f, genType);
  planet.SetScale(10, 10, 10);
  planet.SetGraphicsPipelineState(&planetPipelineState);
  planet.BindForOffsetGpu();

  uint          planetGenSeed       = 1337;
  float         planetGenWaterLevel = 0.1f;
  GenerationGPU planetHeightGeneration;
  planetHeightGeneration.generation.textureSize.x = genType.texWidth;
  planetHeightGeneration.generation.textureSize.y = genType.texHeight;
  planetHeightGeneration.GeneratePermutation(planetGenSeed);
  planetHeightGeneration.Upload();

  ResourceDescriptorHeap heightMapDescHeap;
  heightMapDescHeap.Create(
      {&planetHeightGeneration.generationCB, &planetHeightGeneration.permutationCB},
      {},
      {planet.GetHeightMap()});

  ComputationalPipeline heightMapCp;
  heightMapCp.SetComputeShader("assets/shaders/GenerateHightmap.hlsl");
  heightMapCp.GenerateRootSignature();
  heightMapCp.CreatePipelineState();

  GenerationGPU planetDiffuseGeneration;
  planetDiffuseGeneration.generation.textureSize.x = genType.texWidth;
  planetDiffuseGeneration.generation.textureSize.y = genType.texHeight;
  planetDiffuseGeneration.GeneratePermutation(planetGenSeed);
  planetDiffuseGeneration.Upload();

  ResourceDescriptorHeap diffuseDescHeap;
  diffuseDescHeap.Create({planet.GetWaterLevelCb(),
                          &planetDiffuseGeneration.generationCB,
                          &planetDiffuseGeneration.permutationCB},
                         {},
                         {planet.GetHeightMap(), planet.GetDiffuse()});

  ComputationalPipeline diffuseCp;
  diffuseCp.SetComputeShader("assets/shaders/GenerateDiffuse.hlsl");
  diffuseCp.GenerateRootSignature();
  diffuseCp.CreatePipelineState();

  ResourceDescriptorHeap bumpMapDescHeap;
  bumpMapDescHeap.Create({}, {}, {planet.GetHeightMap(), planet.GetBump()});
  ComputationalPipeline bumpMapCp;
  bumpMapCp.SetComputeShader("assets/shaders/GenerateBump.hlsl");
  bumpMapCp.GenerateRootSignature();
  bumpMapCp.CreatePipelineState();

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
  KeyboardInput::SetAnActionToKey("toggleCaptureMouse", (uint16)'M');

  bool      lockMouse           = false;
  bool      disableMouseCapture = false;
  DM::Vec2i mpLast;

  while (wnd.IsOpen() && !KeyboardInput::IsKeyPressed("close"))
  {
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

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
    if (KeyboardInput::IsKeyFirstPressedThisFrame("toggleCaptureMouse"))
    {
      ShowCursor(true);
      lockMouse           = false;
      disableMouseCapture = !disableMouseCapture;
    }

    {
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
              float            dx           = ((float)mouseEvent_p->MouseDelta.x) * speed;
              float            dy           = ((float)mouseEvent_p->MouseDelta.y) * speed;
              if (!lockMouse)
              {
                mpLast = mouseEvent_p->MousePosition;
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
          }
          for (uint i = 0; i < events.size(); i++)
            delete events[i];
        }
      }
    }
    if (disableMouseCapture)
    {
      PlanetGenModifier(
          planetHeightGeneration, planetDiffuseGeneration, planetGenSeed, planetGenWaterLevel);
    }
    planet.SetWaterLevel(planetGenWaterLevel);
    planetHeightGeneration.GeneratePermutation(planetGenSeed);
    planetHeightGeneration.Upload();
    planetDiffuseGeneration.GeneratePermutation(planetGenSeed);
    planetDiffuseGeneration.Upload();
    ren_p->ChangeResourceStateForCompute(planet.GetHeightMap()->GetResource(),
                                         D3D12_RESOURCE_STATE_GENERIC_READ,
                                         D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
    ren_p->ChangeResourceStateForCompute(planet.GetDiffuse()->GetResource(),
                                         D3D12_RESOURCE_STATE_GENERIC_READ,
                                         D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

    ren_p->ChangeResourceStateForCompute(planet.GetBump()->GetResource(),
                                         D3D12_RESOURCE_STATE_GENERIC_READ,
                                         D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
    ren_p->BeginCompute();
    ren_p->Compute(heightMapCp,
                   heightMapDescHeap,
                   DM::Vec3i(genType.texWidth / 32, genType.texHeight / 32, 1));
    ren_p->EndCompute();

    ren_p->BeginCompute();
    ren_p->Compute(
        diffuseCp, diffuseDescHeap, DM::Vec3i(genType.texWidth / 32, genType.texHeight / 32, 1));
    ren_p->Compute(
        bumpMapCp, bumpMapDescHeap, DM::Vec3i(genType.texWidth, genType.texHeight, 1));
    ren_p->EndCompute();

    ren_p->ChangeResourceStateForCompute(planet.GetHeightMap()->GetResource(),
                                         D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
                                         D3D12_RESOURCE_STATE_GENERIC_READ);
    ren_p->ChangeResourceStateForCompute(planet.GetDiffuse()->GetResource(),
                                         D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
                                         D3D12_RESOURCE_STATE_GENERIC_READ);
    ren_p->ChangeResourceStateForCompute(planet.GetBump()->GetResource(),
                                         D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
                                         D3D12_RESOURCE_STATE_GENERIC_READ);
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

    planet.Rotate(0, rotationSpeed * dt * DirectX::XM_PI, 0);
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

void PlanetGenModifier(GenerationGPU& heightGeneration,
                       GenerationGPU& diffuseGeneration,
                       uint&          seed,
                       float&         waterLevel)
{
  int _seed = static_cast<int>(seed);

  ImGui::Begin("Planet Generation Modifier");

  ImGui::Text("Generic");
  ImGui::SliderInt("Seed", &_seed, 0, INT_MAX / 2);

  seed = static_cast<uint>(_seed);
  ImGui::SliderFloat("waterLevel", &waterLevel, 0.0f, 1.0f);

  ImGui::Text("Height");
  {
    int _it = static_cast<int>(heightGeneration.generation.iterations);
    ImGui::SliderFloat("height_exponent", &heightGeneration.generation.exponent, 0.0f, 10.0f);
    ImGui::SliderFloat("height_frequency", &heightGeneration.generation.frequency, 0.0f, 10.0f);
    ImGui::SliderFloat("height_fudgeFactor", &heightGeneration.generation.fudgeFactor, 0.0f, 2.0f);
    ImGui::SliderInt("height_iterations", &_it, 0, 100);
    heightGeneration.generation.iterations = static_cast<uint>(_it);
  }
  ImGui::Text("Diffuse");
  {
    int _it = static_cast<int>(diffuseGeneration.generation.iterations);
    ImGui::SliderFloat("diffuse_exponent", &diffuseGeneration.generation.exponent, 0.0f, 10.0f);
    ImGui::SliderFloat("diffuse_frequency", &diffuseGeneration.generation.frequency, 0.0f, 10.0f);
    ImGui::SliderFloat(
        "diffuse_fudgeFactor", &diffuseGeneration.generation.fudgeFactor, 0.0f, 2.0f);
    ImGui::SliderInt("diffuse_iterations", &_it, 0, 100);
    diffuseGeneration.generation.iterations = static_cast<uint>(_it);
  }

  ImGui::End();
}