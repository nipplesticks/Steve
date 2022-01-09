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
  myPosition        = position;
  myRotatedPosition = position;
  myPitchJawRoll    = DM::Vec3f();
}

void Camera::SetLookAt(const DM::Vec4f& point)
{
  myLookAt = point;
}

void Camera::SetUp(const DM::Vec4f& up)
{
  myUp        = up;
  myRotatedUp = up;
}

void Camera::Rotate(const DM::Vec3f& pitchJawRoll)
{
  DM::Vec3f temp = pitchJawRoll;
  if (myRotatedUp.y < 0)
    temp.y *= -1;
  if (myFlipUp)
    temp.x *= -1;

  temp = temp * myPosition.Length(true);

  myPitchJawRoll         = myPitchJawRoll + temp;
  DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationRollPitchYaw(
      myPitchJawRoll.x, myPitchJawRoll.y, myPitchJawRoll.z);

  DM::Vec3f pos(myPosition.x, myPosition.y, myPosition.z);
  DM::Vec3f rotPos = pos.Normalize();
  rotPos.Store(DirectX::XMVector3Rotate(rotPos.Load(), quat));
  rotPos              = rotPos * pos.Length();
  myRotatedPosition.x = rotPos.x;
  myRotatedPosition.y = rotPos.y;
  myRotatedPosition.z = rotPos.z;
  myRotatedPosition.w = 1.0f;

  DM::Vec3f up(myUp.x, myUp.y, myUp.z);
  up.Store(DirectX::XMVector3Rotate(up.Load(), quat));
  up            = up.Normalize();
  myRotatedUp.x = up.x;
  myRotatedUp.y = up.y;
  myRotatedUp.z = up.z;
  myRotatedUp.w = 0.0f;
}

void Camera::FlipUp()
{
  myUp   = myUp * -1.0f;
  myUp   = myUp.Normalize();
  myUp.w = 0.0f;
  myFlipUp = !myFlipUp;
  Rotate(DM::Vec3f());
}

void Camera::Zoom(float factor)
{
  DM::Vec3f pos(myPosition.x, myPosition.y, myPosition.z);

  DM::Vec3f dir = (pos * -1).Normalize();

  DM::Vec3f newPos = pos + dir * factor;

  float d = newPos.Normalize().Dot(pos.Normalize());
  if (d < 0.0f || newPos.Length() < .1f)
  {
    newPos = pos.Normalize() * .1f;
  }
  myPosition = newPos.AsXmFloat4();
  myPosition.w = 1.0f;
  Rotate(DM::Vec3f());
}

const DM::Vec4f& Camera::GetPosition() const
{
  return myRotatedPosition;
}

const DM::Vec4f& Camera::GetLookAt() const
{
  return myLookAt;
}

const DM::Vec4f& Camera::GetUp() const
{
  return myRotatedUp;
}

DM::Mat4x4 Camera::GetViewProjection()
{
  myViewMatrix.Store(
      DirectX::XMMatrixLookAtRH(myRotatedPosition.Load(), myLookAt.Load(), myRotatedUp.Load()));

  return myViewMatrix * myProjectionMatrix;
}
