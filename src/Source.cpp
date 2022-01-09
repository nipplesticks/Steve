#include "World/Planet.h"
#include "events/EventHandler.h"
//#include "renderer/Camera.h"
#include "renderer/Camera2.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/TextureBuffer.h"
#include "renderer/TextureLoader.h"
#include "renderer/VertexBuffer.h"
#include "utility/Timer.h"
#include "window/Window.h"
#include <iostream>

int main()
{
  Window        wnd(1280, 720, "aTitle");
  Renderer      ren(1280, 720, wnd.GetHwnd());
  Camera2::View view;
  view.fov       = 45.0f;
  view.height    = 720.0f;
  view.width     = 1280.0f;
  view.nearPlane = 0.01f;
  view.farPlane  = 1000.0f;
  Camera2 cam;
  cam.SetMaxZoom(0.5f + view.nearPlane);
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

    // Must be first
    ren.BeginFrame();
    ren.Clear(Vector4f(0.1f, 0.1f, 0.1f, 1.0f));
    ren.UpdateViewProjection(cam.GetViewProjection());
    //ren.DrawVertexBuffer(vb);
    /*for (uint i = 0; i < m.GetMeshesCount(); i++)
      ren.DrawVertexAndIndexBuffer(vbs[i], ibs[i]);*/
    for (uint i = 0; i < m.GetMeshesCount(); i++)
      ren.DrawVertexAndIndexAndTextureBuffer(vbs[i], ibs[i], texBuff);

    // Must be last
    ren.EndFrame();
  }

  return 0;
}