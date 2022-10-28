#include "pch.h"
#include "Render.h"

Render Render::gRender;

Render::Render()
{
  myU64 = 123132;
}

void Render::Print()
{
  myTransform.SetPosition(DM::Vec3f(1, 2, 3));
  std::cout << myTransform.GetPosition().ToString() << std::endl;
  std::cout << gRender.myU64 << std::endl;
}
