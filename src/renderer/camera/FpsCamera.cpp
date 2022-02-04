#include "FpsCamera.h"

DM::Vec3f FpsCamera::GetForward() const
{
  return myLookTo;
}

DM::Vec3f FpsCamera::GetRight() const
{
  DM::Vec3f dir = GetForward();
  DM::Vec3f up = GetUp();
  return dir.Cross(up).Normalize();
}

DM::Vec3f FpsCamera::GetUp() const
{
  DM::Vec3f dir = GetForward();

  if (myUseCustomUp)
    return myCustomUp;
  else
  {
    DM::Vec3f up(0, 1, 0);
    float     d = up.Dot(dir);

    if (fabs(d) > 0.999f)
    {
      DM::Vec3f r(1, 0, 0);
      return dir.Cross(r).Normalize();
    }
    else
    {
      return dir.Cross(up).Normalize().Cross(dir).Normalize();
    }
  }
}

DM::Mat4x4 FpsCamera::GetViewMatrix() const
{
  DM::Mat4x4 viewMat;
  viewMat.Store(DirectX::XMMatrixLookToRH(myPosition.LoadAsVec4(1.0f), GetRelativeForward().Load(), GetRelativeUp().Load()));
  return viewMat;
}

DM::Vec3f FpsCamera::GetRelativeForward() const
{
  DM::Vec3f f;
  f.Store(DirectX::XMVector3Rotate(GetForward().Load(), myRotationQuat.Load()));
  return f.Normalize();
}

DM::Vec3f FpsCamera::GetRelativeUp() const
{
  DM::Vec3f u;
  u.Store(DirectX::XMVector3Rotate(GetUp().Load(), myRotationQuat.Load()));
  return u;
}

DM::Vec3f FpsCamera::GetRelativeRight() const
{
  DM::Vec3f r;
  r.Store(DirectX::XMVector3Rotate(GetRight().Load(), myRotationQuat.Load()));
  return r;
}

void FpsCamera::SetLookTo(float x, float y, float z)
{
  SetLookTo(DM::Vec3f(x, y, z));
}

void FpsCamera::SetLookTo(const DM::Vec3f& lookTo)
{
  myLookTo = lookTo.Normalize();
}
