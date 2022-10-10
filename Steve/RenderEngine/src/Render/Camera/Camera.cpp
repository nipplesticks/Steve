#include "pch.h"
#include "Render/Camera/Camera.h"

using namespace Render;

Camera::Camera()
  : Transform()
{
  SetView(myView);
}

Camera::~Camera()
{

}

DM::Mat4x4f Camera::GetViewMatrix() const
{
  return DM::Mat4x4f();
}

DM::Mat4x4f Camera::GetProjectionMatrix() const
{
  return DM::Mat4x4f();
}

DM::Mat4x4f Camera::GetViewProjectionMatrix() const
{
  return DM::Mat4x4f();
}

void Camera::SetView(const View& view)
{
  myView = view;
  // Build projectionM,atrix;
}

const View& Render::Camera::GetView() const
{
  return myView;
}
