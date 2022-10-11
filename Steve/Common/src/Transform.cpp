#include "pch.h"
#include "Transform.h"

DM::Vec4f Transform::DEFAULT_FORWARD = DM::Vec4f(0, 0, 1, 0);
DM::Vec4f Transform::DEFAULT_UP      = DM::Vec4f(0, 1, 0, 0);

Transform::Transform()
{
  myPosition    = DM::Vec4f(0, 0, 0, 1);
  myRotation    = DirectX::XMQuaternionIdentity();
  myScale       = DM::Vec4f(1.0f, 1.0f, 1.0f, 0.0f);
  myOrigin      = DM::Vec4f(0);
  myCustomUp    = DEFAULT_UP;
  myUseCustomUp = false;
}

Transform::~Transform() { }

void Transform::SetPosition(float x, float y, float z)
{
  SetPosition(DM::Vec3f(x, y, z));
}

void Transform::SetPosition(const DM::Vec3f& position)
{
  myPosition   = position;
  myPosition.w = 1.0f;
}

void Transform::SetRotation(float x, float y, float z)
{
  SetRotation(DM::Vec3f(x, y, z));
}

void Transform::SetRotation(const DM::Vec3f& axis)
{
  myRotation = DirectX::XMQuaternionRotationRollPitchYawFromVector(DM::ToRad(axis).Load());
}

void Transform::SetRotation(const DM::Vec4f& quaternion)
{
  myRotation = quaternion;
}

void Transform::SetScale(float x, float y, float z)
{
  SetScale(DM::Vec3f(x, y, z));
}

void Transform::SetScale(const DM::Vec3f& scale)
{
  myScale   = scale;
  myScale.w = 0.0f;
}

void Transform::SetOrigin(float x, float y, float z)
{
  SetOrigin(DM::Vec3f(x, y, z));
}

void Transform::SetOrigin(const DM::Vec3f& origin)
{
  myOrigin   = origin;
  myOrigin.w = 1.0f;
}

void Transform::Move(float x, float y, float z)
{
  Move(DM::Vec3f(x, y, z));
}

void Transform::Move(const DM::Vec3f& translation)
{
  SetPosition(myPosition + translation);
}

void Transform::Rotate(float x, float y, float z)
{
  Rotate(DM::Vec3f(x, y, z));
}

void Transform::Rotate(const DM::Vec3f& axis)
{
  myRotation = DirectX::XMQuaternionMultiply(
      myRotation.Load(), DirectX::XMQuaternionRotationRollPitchYawFromVector(DM::ToRad(axis).Load()));
}

void Transform::Scale(float x, float y, float z)
{
  Scale(DM::Vec3f(x, y, z));
}

void Transform::Scale(const DM::Vec3f& scale)
{
  myScale = myScale + scale;
}

void Transform::UseCustomUp(bool flag)
{
  myUseCustomUp = flag;
}

void Transform::SetCustomUp(float x, float y, float z)
{
  SetCustomUp(DM::Vec3f(x, y, z));
}

void Transform::SetCustomUp(const DM::Vec3f& up)
{
  myCustomUp   = up;
  myCustomUp.w = 0;
}

void Transform::SetForward(float x, float y, float z)
{
  SetForward(DM::Vec3f(x, y, z));
}

void Transform::SetForward(const DM::Vec3f& forward)
{
  DM::Vec3f   defaultForward = DEFAULT_FORWARD;
  DM::Mat3x3f rotM           = defaultForward.GetRotationFrom(forward);
  if (DirectX::XMMatrixIsIdentity(rotM.Load()))
  {
    SetRotation(0, 180, 0);
  }
  else
  {
    DM::Vec4f q = DirectX::XMQuaternionRotationMatrix(rotM.Load());
    SetRotation(q);
  }
}

const DM::Vec4f& Transform::GetPosition() const
{
  return myPosition;
}

const DM::Vec4f& Transform::GetRotation() const
{
  return myRotation;
}

const DM::Vec4f& Transform::GetScale() const
{
  return myScale;
}

DM::Vec4f Transform::GetForward() const
{
  if (!myUseCustomUp)
    return DirectX::XMVector3Rotate(DEFAULT_FORWARD.Load(), myRotation.Load());
  else
  {
    DM::Vec3f defaultUp = DEFAULT_UP;
    DM::Vec3f up        = myCustomUp;
    DM::Mat3x3f rotM = defaultUp.GetRotationFrom(up);
    DM::Vec3f forward = (DEFAULT_FORWARD * rotM).Normalize();
    forward = DirectX::XMVector3Rotate(forward.Load(), myRotation.Load());
    return forward;
  }
}

DM::Vec4f Transform::GetRight() const
{
  DM::Vec3f f = GetForward();
  DM::Vec3f u = GetUp();
  return f.Cross(u).Normalize();
}

DM::Vec4f Transform::GetUp() const
{
  if (!myUseCustomUp)
    return DirectX::XMVector3Rotate(DEFAULT_UP.Load(), myRotation.Load());
  return myCustomUp;
}

DM::Mat4x4f Transform::GetWorldMatrix() const
{
  DM::Mat4x4f w = DirectX::XMMatrixTransformation(myOrigin.Load(),
                                                  DirectX::XMQuaternionIdentity(),
                                                  myScale.Load(),
                                                  myOrigin.Load(),
                                                  myRotation.Load(),
                                                  myPosition.Load());

  return w;
}

DM::Mat4x4f Transform::GetInverseWorldMatrix() const
{
  return GetWorldMatrix().Inverse();
}

DM::Vec3f Transform::TransformToLocal(const DM::Vec3f& v)
{
  DM::Vec3f out = DirectX::XMVector3Transform(v.Load(), GetWorldMatrix().Load());
  return out;
}

float Transform::Distance(const Transform& other)
{
  return sqrt(DistanceSq(other));
}

float Transform::DistanceSq(const Transform& other)
{
  DM::Vec3f dir = other.myPosition - myPosition;
  return dir.Length();
}

DM::Vec3f Transform::Direction(const Transform& other, float& length)
{
  DM::Vec3f dir = other.myPosition - myPosition;
  length        = dir.Length();
  return dir.Normalize();
}
