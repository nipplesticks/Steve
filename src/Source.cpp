#include "World/Planet.h"
#include "events/EventHandler.h"
#include "renderer/Camera.h"
#include "renderer/ConstantBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/TextureBuffer.h"
#include "renderer/TextureLoader.h"
#include "renderer/VertexBuffer.h"
#include "utility/Timer.h"
#include "utility/UtilityFuncs.h"
#include "window/Window.h"
#include <iostream>
#include "renderer/GraphicsPipelineState.h"
#include "renderer/ConstantBufferDescriptorHeap.h"

int main()
{
  Window       wnd(1280, 720, "aTitle");
  Renderer     ren(1280, 720, wnd.GetHwnd());
  GraphicsPipelineState lol;
  lol.SetVertexShader("assets/shaders/VertexHelloTriangle.hlsl");
  lol.SetPixelShader("assets/shaders/PixelHelloTriangle.hlsl");
  lol.GenerateInputElementDesc();
  lol.GenerateRootSignature();
  lol.CreatePipelineState();

  ConstantBufferDescriptorHeap planetCBVHD;
  ConstantBufferDescriptorHeap ViewProjCBVHD;

  Camera::View view;
  view.fov       = 45.0f;
  view.height    = 720.0f;
  view.width     = 1280.0f;
  view.nearPlane = 0.01f;
  view.farPlane  = 1000.0f;
  Camera cam;
  cam.SetMaxZoom(1.f + view.nearPlane);
  cam.SetPosition(0, 0, 2.0f);
  cam.SetLookAt(0, 0, 0);
  cam.SetView(view);

  Planet p;
  p.Create(1.0f, 8, 1.0f);
  Mesh                      m = p.GetMesh();
  std::vector<VertexBuffer> vbs;
  std::vector<IndexBuffer>  ibs;
  TextureBuffer             texBuff;
  vbs.resize(m.GetMeshesCount());
  ibs.resize(m.GetMeshesCount());

  Mesh skyBox;
  skyBox.LoadMesh("assets/models/cube/Cube.obj", false);
  TextureLoader::Image img = TextureLoader::LoadImageData("assets/models/cube/Skybox.png");
  TextureBuffer        skyboxTextureBuff;
  skyboxTextureBuff.Init(img.width, img.height);
  skyboxTextureBuff.Update(&ren, img.pixels.data());
  DM::Mat4x4 skyBoxTranslation;
  skyBoxTranslation.Store(DirectX::XMMatrixScaling(100, 100, 100));
  std::vector<VertexBuffer> skyBoxVertexBuffer(skyBox.GetMeshesCount());
  std::vector<IndexBuffer>  skyBoxIndexBuffer(skyBox.GetMeshesCount());
  ConstantBuffer            skyBoxConstantBuffer;
  skyBoxConstantBuffer.Init(sizeof(DM::Mat4x4));
  skyBoxConstantBuffer.Update(&skyBoxTranslation, sizeof(DM::Mat4x4));

  for (uint i = 0; i < skyBox.GetMeshesCount(); i++)
  {
    skyBoxVertexBuffer[i].Init(skyBox.GetByteSizeOfVertices(i), sizeof(Vertex));
    skyBoxVertexBuffer[i].Update(skyBox.GetRawVertices(i), skyBox.GetByteSizeOfVertices(i));
    skyBoxIndexBuffer[i].Init(skyBox.GetNumberOfIndices(i));
    skyBoxIndexBuffer[i].Update(skyBox.GetRawIndices(i));
  }

  for (uint i = 0; i < m.GetMeshesCount(); i++)
  {
    vbs[i].Init(m.GetByteSizeOfVertices(i), sizeof(Vertex));
    vbs[i].Update(m.GetRawVertices(i), m.GetByteSizeOfVertices(i));
    ibs[i].Init(m.GetNumberOfIndices(i));
    ibs[i].Update(m.GetRawIndices(i));
  }
  uint   w, h;
  uint8* rawImg = m.GetRawImage(0, &w, &h);
  texBuff.Init(w, h);
  texBuff.Update(&ren, rawImg);

  float speed     = 0.1f;
  float zoomSpeed = 0.1f;
  float rollSpeed = 0.5f;
  Timer t;
  t.Start();

  ConstantBuffer cb;
  cb.Init(sizeof(DM::Mat4x4));
  DM::Mat4x4 worldMat;
  worldMat.Store(DirectX::XMMatrixIdentity());
  cb.Update(&worldMat, sizeof(worldMat));
  planetCBVHD.Create({&cb}, &texBuff);
  float rotation      = 0.0f;
  float rotationSpeed = 0.01f;
  while (wnd.IsOpen())
  {
    float dt = t.Stop();
    wnd.PollEvents();
    {
      std::vector<Event*> events = EventHandler::GetEvents(Event::Type::MouseMoved);
      EventHandler::ClearEvents(Event::Type::MouseMoved);
      if (!events.empty())
      {
        EventMouseMoved* mouseEvent_p = (EventMouseMoved*)events.back();
        float            dx           = ((float)mouseEvent_p->MouseDelta.x) * speed * dt;
        float            dy           = ((float)mouseEvent_p->MouseDelta.y) * speed * dt;

        if (mouseEvent_p->MButtonPressed)
        {
          cam.Roll((-(float)mouseEvent_p->MouseDelta.x) * rollSpeed * dt);
        }
        if (mouseEvent_p->LButtonPressed)
        {
          cam.Rotate(-dx, -dy);
        }
        for (uint i = 0; i < events.size(); i++)
        {
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
            cam.Zoom(z);
          }
          delete events[i];
        }
      }
    }

    rotation += rotationSpeed * dt * DirectX::XM_PI;

    worldMat.Store(DirectX::XMMatrixRotationY(rotation));

    cb.Update(&worldMat, sizeof(worldMat));

    

    // Must be first
    ren.BeginFrame();
    ren.Clear(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
    ren.UpdateViewProjection(cam.GetViewProjection());
    //ren.DrawVertexBuffer(vb);
    /*for (uint i = 0; i < m.GetMeshesCount(); i++)
      ren.DrawVertexAndIndexBuffer(vbs[i], ibs[i]);*/
    /*for (uint i = 0; i < m.GetMeshesCount(); i++)
      ren.DrawVertexAndIndexAndTextureBuffer(vbs[i], ibs[i], texBuff);*/

    /*for (uint i = 0; i < skyBox.GetMeshesCount(); i++)
      ren.DrawVertexAndIndexAndTextureBufferAndConstantBuffer(
          skyBoxVertexBuffer[i], skyBoxIndexBuffer[i], skyboxTextureBuff, skyBoxConstantBuffer);*/

    /*for (uint i = 0; i < m.GetMeshesCount(); i++)
    {
      ren.DrawVertexAndIndexAndTextureBufferAndConstantBuffer(
          vbs[i], ibs[i], texBuff, cb);
    }*/
    for (uint i = 0; i < m.GetMeshesCount(); i++)
    {
      ren.DrawShitLoad(vbs[i], ibs[i], texBuff, planetCBVHD);
    }

    // Must be last
    ren.EndFrame();
  }

  return 0;
}