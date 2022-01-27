#include "Camera.h"
#include "../utility/Typedef.h"

Camera::Camera()
{
  _init();
  SetView(GetDefaultView());
}

Camera::Camera(const View& view)
{
  _init();
  SetView(view);
}

void Camera::SetView(const View& view)
{
  myView = view;
  _buildProjection();
}

void Camera::SetPosition(float x, float y, float z)
{
  SetPosition(DM::Vec3f(x, y, z));
}

void Camera::SetPosition(const DM::Vec3f& position)
{
  myPosition = position;
}

void Camera::Move(const DM::Vec3f& translation)
{
  myPosition = myPosition + translation;
}

void Camera::Move(float x, float y, float z)
{
  Move(DM::Vec3f(x, y, z));
}

void Camera::Rotate(float x, float y, float z)
{
  Rotate(DM::Vec3f(x, y, z));
}

void Camera::Rotate(const DM::Vec3f& axis)
{
  DM::Vec4f xq, yq, zq;
  xq.Store(DirectX::XMVector3Rotate(GetRight().Load(), myRotationQuat.Load()));
  yq.Store(DirectX::XMVector3Rotate(GetUp().Load(), myRotationQuat.Load()));
  zq.Store(DirectX::XMVector3Rotate(GetForward().Load(), myRotationQuat.Load()));

  xq = xq.Normalize();
  yq = yq.Normalize();
  zq = zq.Normalize();

  xq.Store(DirectX::XMQuaternionRotationNormal(xq.Load(), axis.x));
  yq.Store(DirectX::XMQuaternionRotationNormal(yq.Load(), axis.y));
  zq.Store(DirectX::XMQuaternionRotationNormal(zq.Load(), axis.z));

  DM::Vec4f rot;
  rot.Store(DirectX::XMQuaternionMultiply(DirectX::XMQuaternionMultiply(xq.Load(), yq.Load()),
                                          zq.Load()));
  myRotationQuat.Store(DirectX::XMQuaternionMultiply(myRotationQuat.Load(), rot.Load()));
  //myRotationQuat = rot;
}

void Camera::SetRotation(float x, float y, float z)
{
  SetRotation(DM::Vec3f(x, y, z));
}

void Camera::SetRotation(const DM::Vec3f& axis)
{
  myRotationQuat.Store(DirectX::XMQuaternionRotationRollPitchYawFromVector(axis.Load()));
}

void Camera::UseCustomUpVector(bool flag)
{
  myUseCustomUp = flag;
}

void Camera::SetCustomUpVector(const DM::Vec3f& up)
{
  myCustomUp = up.Normalize();
}

void Camera::SetCustomUpVector(float x, float y, float z)
{
  SetCustomUpVector(DM::Vec3f(x, y, z));
}

const Camera::View& Camera::GetView() const
{
  return myView;
}

const DM::Vec3f& Camera::GetPosition() const
{
  return myPosition;
}

const DM::Vec4f& Camera::GetRotation() const
{
  return myRotationQuat;
}

const DM::Mat4x4& Camera::GetProjectionMatrix() const
{
  return myProjectionMatrix;
}

DM::Mat4x4 Camera::GetViewProjectionMatrix() const
{
  return GetViewMatrix() * myProjectionMatrix;
}

Camera::View Camera::GetDefaultView()
{
  Camera::View view  = {};
  view.fov           = 45.0f;
  view.height        = 720.0f;
  view.width         = 1280.0f;
  view.nearPlane     = 0.01f;
  view.farPlane      = 1000.0f;
  view.isPerspective = true;
  return view;
}

void Camera::_buildProjection()
{
  if (myView.isPerspective)
  {
    myProjectionMatrix.Store(
        DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(myView.fov),
                                          myView.width / myView.height,
                                          myView.nearPlane,
                                          myView.farPlane));
  }
  else
  {
    myProjectionMatrix.Store(DirectX::XMMatrixOrthographicRH(
        myView.width, myView.height, myView.nearPlane, myView.farPlane));
  }
}

void Camera::_init()
{
  SetView(GetDefaultView());
  myPosition = DM::Vec3f();
  myRotationQuat.Store(DirectX::XMQuaternionRotationRollPitchYaw(0, 0, 0));
}
