#include "Transform.h"

Transform::Transform(const DM::Vec3f& position)
{
  myPosition = position;
  myScale    = DM::Vec3f(1.0f, 1.0f, 1.0f);
  myRotation.Store(DirectX::XMQuaternionIdentity());
}

void Transform::SetPosition(const DM::Vec3f& position)
{
  myPosition = position;
}

void Transform::SetPosition(float x, float y, float z)
{
  SetPosition(DM::Vec3f(x, y, z));
}

void Transform::SetScale(const DM::Vec3f& scale)
{
  myScale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
  SetScale(DM::Vec3f(x, y, z));
}

void Transform::SetRotation(const DM::Vec3f& pitchYawRoll)
{
  myRotation.Store(
      DirectX::XMQuaternionRotationRollPitchYaw(pitchYawRoll.x, pitchYawRoll.y, pitchYawRoll.z));
}

void Transform::SetRotation(float x, float y, float z)
{
  SetRotation(DM::Vec3f(x, y, z));
}

void Transform::Move(const DM::Vec3f& translation)
{
  SetPosition(myPosition + translation);
}

void Transform::Move(float x, float y, float z)
{
  Move(DM::Vec3f(x, y, z));
}

void Transform::Scale(const DM::Vec3f& relativeScale)
{
  SetScale(myScale + relativeScale);
}

void Transform::Scale(float x, float y, float z)
{
  Scale(DM::Vec3f(x, y, z));
}

void Transform::Rotate(const DM::Vec3f& pitchYawRoll)
{
  DM::Vec4f rotation;
  rotation.Store(
      DirectX::XMQuaternionRotationRollPitchYaw(pitchYawRoll.x, pitchYawRoll.y, pitchYawRoll.z));

  myRotation.Store(DirectX::XMQuaternionMultiply(myRotation.Load(), rotation.Load()));
}

void Transform::Rotate(float x, float y, float z)
{
  Rotate(DM::Vec3f(x, y, z));
}

const DM::Vec3f& Transform::GetPosition() const
{
  return myPosition;
}

const DM::Vec3f& Transform::GetScale() const
{
  return myScale;
}

const DM::Vec4f& Transform::GetRotation() const
{
  return myRotation;
}

DM::Mat4x4f Transform::GetWorldMatrix() const
{
  DM::Mat4x4f s, r, t;

  r.Store(DirectX::XMMatrixRotationQuaternion(myRotation.Load()));
  s.Store(DirectX::XMMatrixScaling(myScale.x, myScale.y, myScale.z));
  t.Store(DirectX::XMMatrixTranslation(myPosition.x, myPosition.y, myPosition.z));

  return s * r * t;
}
