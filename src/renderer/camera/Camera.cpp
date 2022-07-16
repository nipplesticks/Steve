#include "Camera.h"
#include "../../utility/Typedef.h"

ConstantBuffer Camera::VIEW_PROJECTION_CB;
struct alignas(256) ViewProj
{
  DM::Mat4x4f        view;
  DM::Mat4x4f        projection;
  DirectX::XMFLOAT4A position;
};

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
  if (!myUseCustomUp)
  {
    DM::Vec4f xq;
    DM::Vec4f yq;
    DM::Vec4f zq;
    xq = GetRelativeRight().AsXmAsXmFloat4A(0.0f);
    yq = GetRelativeUp().AsXmAsXmFloat4A(0.0f);
    zq = GetRelativeForward().AsXmAsXmFloat4A(0.0f);

    xq.Store(DirectX::XMQuaternionRotationNormal(xq.Load(), axis.x));
    yq.Store(DirectX::XMQuaternionRotationNormal(yq.Load(), axis.y));
    zq.Store(DirectX::XMQuaternionRotationNormal(zq.Load(), axis.z));

    DM::Vec4f rot;
    rot.Store(DirectX::XMQuaternionMultiply(DirectX::XMQuaternionMultiply(xq.Load(), yq.Load()),
                                            zq.Load()));
    myRotationQuat.Store(DirectX::XMQuaternionMultiply(myRotationQuat.Load(), rot.Load()));
  }
  else
  {
    DM::Vec4f xq;
    DM::Vec4f yq;
    DM::Vec4f zq;
    xq = GetRelativeRight().AsXmAsXmFloat4A(0.0f);
    yq = GetRelativeUp().AsXmAsXmFloat4A(0.0f);
    zq = GetRelativeForward().AsXmAsXmFloat4A(0.0f);

    xq.Store(DirectX::XMQuaternionRotationNormal(xq.Load(), axis.x));
    yq.Store(DirectX::XMQuaternionRotationNormal(yq.Load(), axis.y));
    zq.Store(DirectX::XMQuaternionRotationNormal(zq.Load(), axis.z));

    DM::Vec4f rot;
    rot.Store(DirectX::XMQuaternionMultiply(DirectX::XMQuaternionMultiply(xq.Load(), yq.Load()),
                                            zq.Load()));

    DM::Vec4f tRotQuat = myRotationQuat;
    myRotationQuat.Store(DirectX::XMQuaternionMultiply(myRotationQuat.Load(), rot.Load()));
    DM::Vec3f f = GetRelativeForward();
    DM::Vec3f r = GetRelativeRight();
    DM::Vec3f lu = r.Cross(f).Normalize();
    if (lu.Dot(myCustomUp) < 0.13f)
    {
      myRotationQuat = tRotQuat;
      myRotationQuat.Store(DirectX::XMQuaternionMultiply(myRotationQuat.Load(), yq.Load()));
    }
  }
}

void Camera::RotateFromQuaternion(const DM::Vec4f& q)
{
  myRotationQuat.Store(DirectX::XMQuaternionMultiply(myRotationQuat.Load(), q.Load()));
}

void Camera::RotateFromRotationMatrix(const DM::Mat3x3f& m)
{
  DM::Vec4f q = DirectX::XMQuaternionRotationMatrix(m.Load());
  RotateFromQuaternion(q);
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

const DM::Mat4x4f& Camera::GetProjectionMatrix() const
{
  return myProjectionMatrix;
}

DM::Mat4x4f Camera::GetViewProjectionMatrix() const
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
  view.farPlane      = 100000.0f;
  view.isPerspective = true;
  return view;
}

void Camera::SetAsMainCameraAndUpdate() const
{
  ViewProj viewProjection;

  viewProjection.view = GetViewMatrix();
  viewProjection.projection = GetProjectionMatrix().AsXmFloat4x4A();
  viewProjection.position   = GetPosition().AsXmAsXmFloat4A(1.0f);


  VIEW_PROJECTION_CB.UpdateNow(&viewProjection, D3D12_RESOURCE_STATE_GENERIC_READ, sizeof(viewProjection));
}

void Camera::InitViewProjectionCb()
{
  VIEW_PROJECTION_CB.Create(sizeof(ViewProj));
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
  myCustomUp = DM::Vec3f(0,1,0);
  myRotationQuat.Store(DirectX::XMQuaternionRotationRollPitchYaw(0, 0, 0));
}
