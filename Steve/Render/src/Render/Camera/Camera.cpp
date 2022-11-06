#include "pch.h"
#include "Render/Camera/Camera.h"

using namespace Render;

Camera::Camera()
    : Transform()
{
  SetView(myView);
}

Camera::~Camera() { }

DM::Mat4x4f Camera::GetViewMatrix() const
{
  return DirectX::XMMatrixLookToLH(myPosition.Load(), GetForward().Load(), GetUp().Load());
}

const DM::Mat4x4f& Camera::GetProjectionMatrix() const
{
  return myProjectionMatrix;
}

DM::Mat4x4f Camera::GetViewProjectionMatrix() const
{
  return GetViewMatrix() * GetProjectionMatrix();
}

void Camera::SetView(const View& view)
{
  myView = view;
  if (myView.isPerspective)
  {
    myProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
        DM::ToRad(myView.fov), myView.width / myView.height, myView.nearPlane, myView.farPlane);
  }
  else
  {
    myProjectionMatrix = DirectX::XMMatrixOrthographicLH(
        myView.width, myView.height, myView.nearPlane, myView.farPlane);
  }
}

const View& Render::Camera::GetView() const
{
  return myView;
}
