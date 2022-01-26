#include "Camera.h"
#include "../utility/Typedef.h"
Camera::Camera()
{
  myPosition.z = 2;
  _calcAxis();
}

Camera::~Camera() { }

void Camera::SetView(const View& view)
{
  myProjectionMatrix.Store(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(view.fov),
                                                             view.width / view.height,
                                                             view.nearPlane,
                                                             view.farPlane));
}

void Camera::SetPosition(float x, float y, float z, bool calcAxis)
{
  SetPosition(DM::Vec3f(x, y, z), calcAxis);
}

void Camera::SetPosition(const DM::Vec3f& position, bool calcAxis)
{
  myPosition = position;
  if (calcAxis)
    _calcAxis();
}

void Camera::SetLookAt(float x, float y, float z, bool calcAxis)
{
  SetLookAt(DM::Vec3f(x, y, z), calcAxis);
}

void Camera::SetLookAt(const DM::Vec3f& lookAt, bool calcAxis)
{
  myLookAt = lookAt;
  if (calcAxis)
    _calcAxis();
}

void Camera::Rotate(float dx, float dy)
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

void Camera::Zoom(float factor)
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

void Camera::Roll(float d)
{
  DirectX::XMVECTOR rot = DirectX::XMQuaternionRotationAxis((myPosition - myLookAt).Normalize().Load(), d);

  myTranslatedUp.Store(DirectX::XMVector3Rotate(myTranslatedUp.Load(), rot));
  myTranslatedUp = myTranslatedUp.Normalize();

  myTranslatedRight.Store(DirectX::XMVector3Rotate(myTranslatedRight.Load(), rot));
  myTranslatedRight = myTranslatedRight.Normalize();
}

void Camera::SetMaxZoom(float z)
{
  myMaxZoom = z;
}

const DM::Vec3f& Camera::GetPosition() const
{
  return myPosition;
}

const DM::Vec3f& Camera::GetLookAt() const
{
  return myLookAt;
}

const DM::Vec3f& Camera::GetUp() const
{
  return myTranslatedUp;
}

const DM::Vec3f& Camera::GetRight() const
{
  return myTranslatedRight;
}

DM::Mat4x4 Camera::GetViewProjection()
{
  myViewMatrix.Store(
      DirectX::XMMatrixLookAtRH(myPosition.Load(), myLookAt.Load(), myTranslatedUp.Load()));

  return myViewMatrix * myProjectionMatrix;
}

void Camera::_calcAxis()
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

void Camera::_rotateAxis(float dx, float dy)
{
  DirectX::XMVECTOR dxRot = DirectX::XMQuaternionRotationAxis(myTranslatedUp.Load(), dx);
  DirectX::XMVECTOR dyRot = DirectX::XMQuaternionRotationAxis(myTranslatedRight.Load(), dy);

  myTranslatedUp.Store(DirectX::XMVector3Rotate(myTranslatedUp.Load(), dyRot));
  myTranslatedUp = myTranslatedUp.Normalize();

  myTranslatedRight.Store(DirectX::XMVector3Rotate(myTranslatedRight.Load(), dxRot));
  myTranslatedRight = myTranslatedRight.Normalize();
}
