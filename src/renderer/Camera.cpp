#include "Camera.h"
#include <DirectXMath.h>

Camera::Camera() { }

Camera::~Camera() { }

void Camera::SetView(const View& view)
{
  myProjectionMatrix.Store(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(view.fov),
                                                             view.width / view.height,
                                                             view.nearPlane,
                                                             view.farPlane));
}

void Camera::SetPosition(const DM::Vec4f& position)
{
  myPosition = position;
}

void Camera::SetLookAt(const DM::Vec4f& point)
{
  myLookAt = point;
}

void Camera::SetUp(const DM::Vec4f& up)
{
  myUp = up;
}

const DM::Vec4f& Camera::GetPosition() const
{
  return myPosition;
}

const DM::Vec4f& Camera::GetLookAt() const
{
  return myLookAt;
}

const DM::Vec4f& Camera::GetUp() const
{
  return myUp;
}

DM::Mat4x4 Camera::GetViewProjection()
{
  myViewMatrix.Store(DirectX::XMMatrixLookAtRH(myPosition.Load(), myLookAt.Load(), myUp.Load()));

  return myViewMatrix * myProjectionMatrix;
}
