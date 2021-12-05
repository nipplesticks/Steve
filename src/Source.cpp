#include "renderer/Camera.h"
#include "renderer/Renderer.h"
#include "window/Window.h"
#include <iostream>
#include "renderer/Mesh.h"
#include "renderer/VertexBuffer.h"

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
    view.farPlane  = 100.0f;
    cam.SetPosition(DM::Vec4f(0, 3.0f, 3.0f, 1.0f));
    cam.SetLookAt(DM::Vec4f(0, 0.0, 0.0, 1.0f));
    cam.SetUp(DM::Vec4f(0.0f, 1.0f, 0.0f, 0.0f));
    cam.SetView(view);
  }

  Mesh m;
  m.LoadMesh("assets/models/Cube.fbx");
  VertexBuffer vb;
  vb.Init(m.GetByteSize(), sizeof(Vertex));

  std::cout << cam.GetViewProjection().ToString() << std::endl;

  float c = 0.01f;

  while (wnd.IsOpen())
  {
    wnd.PollEvents();
    //Sleep(100);
    DM::Vec4f camPos = cam.GetPosition();
    float x         = camPos.x * cos(c) + camPos.z * sin(c);
    float z         = camPos.x * -sin(c) + camPos.z * cos(c);
    camPos.x            = x;
    camPos.z            = z;
    
    cam.SetPosition(camPos);

    // Must be first
    ren.BeginFrame();
    ren.Clear(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
    vb.Update(m.GetRawVertices(), m.GetByteSize());
    ren.UpdateViewProjection(cam.GetViewProjection());
    ren.DrawVertexBuffer(vb);

    // Must be last
    ren.EndFrame();
  }

  return 0;
}