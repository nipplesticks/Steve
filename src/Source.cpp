#include "renderer/Camera.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/VertexBuffer.h"
#include "utility/Timer.h"
#include "window/Window.h"
#include "World/Planet.h"
#include <iostream>

int main()
{
  Window   wnd(1280, 720, "aTitle");
  Renderer ren(1280, 720, wnd.GetHwnd());
  Camera   cam;
  {
    Camera::View view;
    view.fov       = 45.0f;
    view.height    = 720.0f;
    view.width     = 1280.0f;
    view.nearPlane = 0.01f;
    view.farPlane  = 1000.0f;
    cam.SetPosition(DM::Vec4f(0, 0, 2.0f, 1.0f));
    //cam.SetPosition(DM::Vec4f(0, 300.0f, 200.0f, 1.0f));
    cam.SetLookAt(DM::Vec4f(0, 0, 0.0, 1.0f));
    cam.SetUp(DM::Vec4f(0.0f, 1.0f, 0.0f, 0.0f));
    /*
    cam.SetPosition(DM::Vec4f(0, -25.0f, 25.0f, 1.0f));
    cam.SetLookAt(DM::Vec4f(0, 25.0, 0.0, 1.0f));
    cam.SetUp(DM::Vec4f(0.0f, 0.0f, 1.0f, 0.0f));
    */
    cam.SetView(view);
  }

  //Mesh m;
  //m.LoadMesh("assets/models/DunkaDennis/DunkaDennis.obj");
  //m.LoadMesh("assets/models/Spider/Spider_3.fbx");
  Planet   p;
  p.Create(1.0f, 300);
  Mesh                      m = p.GetMesh();
  std::vector<VertexBuffer> vbs;
  std::vector<IndexBuffer>  ibs;
  vbs.resize(m.GetMeshesCount());
  ibs.resize(m.GetMeshesCount());

  for (uint i = 0; i < m.GetMeshesCount(); i++)
  {
    vbs[i].Init(m.GetByteSizeOfVertices(i), sizeof(Vertex));
    vbs[i].Update(m.GetRawVertices(i), m.GetByteSizeOfVertices(i));
    ibs[i].Init(m.GetNumberOfIndices(i));
    ibs[i].Update(m.GetRawIndices(i));
  }

  float speed = 0.5f;
  Timer t;
  t.Start();
  while (wnd.IsOpen())
  {
    float dt = t.Stop();
    wnd.PollEvents();
    DM::Vec4f camPos = cam.GetPosition();
    float     x      = camPos.x * cos(speed * dt) + camPos.z * sin(speed * dt);
    float     z      = camPos.x * -sin(speed * dt) + camPos.z * cos(speed * dt);
    camPos.x         = x;
    camPos.z         = z;
    float y  = camPos.y * cos(speed * dt) + camPos.z * sin(speed * dt);
    //float z  = camPos.y * -sin(speed * dt) + camPos.z * cos(speed * dt);
    camPos.y = y;
    //camPos.z = z;*/

    cam.SetPosition(camPos);
    cam.Update();

    // Must be first
    ren.BeginFrame();
    ren.Clear(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
    ren.UpdateViewProjection(cam.GetViewProjection());
    //ren.DrawVertexBuffer(vb);
    for (uint i = 0; i < m.GetMeshesCount(); i++)
      ren.DrawVertexAndIndexBuffer(vbs[i], ibs[i]);

    // Must be last
    ren.EndFrame();
  }

  return 0;
}