#include "Camera2.h"
#include "../utility/Typedef.h"
Camera2::Camera2()
{
  myPosition.z = 2;
  _calcAxis();
}

Camera2::~Camera2() { }

void Camera2::SetView(const View& view)
{
  myProjectionMatrix.Store(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(view.fov),
                                                             view.width / view.height,
                                                             view.nearPlane,
                                                             view.farPlane));
}

void Camera2::SetPosition(float x, float y, float z)
{
  SetPosition(DM::Vec3f(x, y, z));
}

void Camera2::SetPosition(const DM::Vec3f& position)
{
  myPosition = position;
  _calcAxis();
}

void Camera2::SetLookAt(float x, float y, float z)
{
  SetLookAt(DM::Vec3f(x, y, z));
}

void Camera2::SetLookAt(const DM::Vec3f& lookAt)
{
  myLookAt = lookAt;
  _calcAxis();
}

void Camera2::Rotate(float dx, float dy)
{
  float l = myPosition.Length();
  if (l <= FLT_EPSILON)
    return;

  float speed = l * 0.5f;

  dx *= speed * speed;
  dy *= speed * speed;

  _rotateAxis(dx, dy);

  myPosition = myPosition.Normalize();
  DM::Vec4f dxRot;
  dxRot.Store(DirectX::XMQuaternionRotationAxis(myTranslatedUp.Load(), dx));

  DM::Vec4f dyRot;
  dyRot.Store(DirectX::XMQuaternionRotationAxis(myTranslatedRight.Load(), dy));

  myPosition.Store(DirectX::XMVector3Rotate(myPosition.Load(), dxRot.Load()));
  myPosition = myPosition.Normalize();
  myPosition.Store(DirectX::XMVector3Rotate(myPosition.Load(), dyRot.Load()));
  myPosition = myPosition.Normalize();

  myPosition = myPosition * l;
}

void Camera2::Zoom(float factor)
{
  DM::Vec3f dir = (myLookAt - myPosition);
  float     l   = dir.Length();
  dir           = dir.Normalize();
  DM::Vec3f tempPos = myPosition + dir * factor;
  if (myPosition.Dot(tempPos) < 0.0f || tempPos.Length() < myMaxZoom)
  {
    myPosition = myPosition.Normalize() * myMaxZoom;
  }
  else
  {
    myPosition = tempPos;
  }
}

void Camera2::Roll(float d)
{
  DirectX::XMVECTOR rot = DirectX::XMQuaternionRotationAxis((myPosition - myLookAt).Normalize().Load(), d);

  myTranslatedUp.Store(DirectX::XMVector3Rotate(myTranslatedUp.Load(), rot));
  myTranslatedUp = myTranslatedUp.Normalize();

  myTranslatedRight.Store(DirectX::XMVector3Rotate(myTranslatedRight.Load(), rot));
  myTranslatedRight = myTranslatedRight.Normalize();
}

void Camera2::SetMaxZoom(float z)
{
  myMaxZoom = z;
}

const DM::Vec3f& Camera2::GetPosition() const
{
  return myPosition;
}

const DM::Vec3f& Camera2::GetLookAt() const
{
  return myLookAt;
}

const DM::Vec3f& Camera2::GetUp() const
{
  return myTranslatedUp;
}

const DM::Vec3f& Camera2::GetRight() const
{
  return myTranslatedRight;
}

DM::Mat4x4 Camera2::GetViewProjection()
{
  myViewMatrix.Store(
      DirectX::XMMatrixLookAtRH(myPosition.Load(), myLookAt.Load(), myTranslatedUp.Load()));

  return myViewMatrix * myProjectionMatrix;
}

void Camera2::_calcAxis()
{
  DM::Vec3f up;
  DM::Vec3f right;
  DM::Vec3f forward = (myLookAt - myPosition).Normalize();
  up                = DM::Vec3f(0, 1, 0);
  right             = forward.Cross(up).Normalize();
  up                = right.Cross(forward).Normalize();

  myTranslatedRight = right;
  myTranslatedUp    = up;
}

void Camera2::_rotateAxis(float dx, float dy)
{
  DirectX::XMVECTOR dxRot = DirectX::XMQuaternionRotationAxis(myTranslatedUp.Load(), dx);
  DirectX::XMVECTOR dyRot = DirectX::XMQuaternionRotationAxis(myTranslatedRight.Load(), dy);

  myTranslatedUp.Store(DirectX::XMVector3Rotate(myTranslatedUp.Load(), dyRot));
  myTranslatedUp = myTranslatedUp.Normalize();

  myTranslatedRight.Store(DirectX::XMVector3Rotate(myTranslatedRight.Load(), dxRot));
  myTranslatedRight = myTranslatedRight.Normalize();
}
