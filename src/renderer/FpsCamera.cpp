#include "FpsCamera.h"

const DM::Vec3f& FpsCamera::GetForward() const
{
  return myLookTo;
}

const DM::Vec3f& FpsCamera::GetRight() const
{
  DM::Vec3f dir = GetForward();
  DM::Vec3f up = GetUp();
  return dir.Cross(up).Normalize();
}

const DM::Vec3f& FpsCamera::GetUp() const
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
  DM::Vec3f  up;
  DM::Vec3f  dir;

  up.Store(DirectX::XMVector3Rotate(GetUp().Load(), myRotationQuat.Load()));
  dir.Store(DirectX::XMVector3Rotate(GetForward().Load(), myRotationQuat.Load()));

  viewMat.Store(DirectX::XMMatrixLookToRH(myPosition.Load(), dir.Load(), up.Load()));
  return viewMat;
}

void FpsCamera::SetLookTo(float x, float y, float z)
{
  SetLookTo(DM::Vec3f(x, y, z));
}

void FpsCamera::SetLookTo(const DM::Vec3f& lookTo)
{
  myLookTo = lookTo.Normalize();
}
