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

void Camera::Update()
{
  DM::Vec3f dir;
  {
    DM::Vec4f tDir = (myLookAt - myPosition);
    dir            = DM::Vec3f(tDir.x, tDir.y, tDir.z);
  }
  float invert = 1.0f;
  dir          = dir.Normalize();
  DM::Vec3f up(0.0f, 1.0f, 0.0f);
  DM::Vec3f right = up.Cross(dir).Normalize();
  up     = dir.Cross(right).Normalize();
  if (myUp.Dot(up) < 0)
    invert = -1.0f;
  myUp.x = up.x * invert;
  myUp.y = up.y * invert;
  myUp.z = up.z * invert;
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
