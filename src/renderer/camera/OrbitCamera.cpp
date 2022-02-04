#include "OrbitCamera.h"
#include "../../utility/UtilityFuncs.h"
OrbitCamera::OrbitCamera()
    : Camera()
{
  ASSERT_STR(false, "Do not use this class, its shit...");
}

DM::Vec3f OrbitCamera::GetRelativeForward() const
{
  return GetForward();
}

DM::Vec3f OrbitCamera::GetRelativeUp() const
{
  DM::Vec3f u;
  u.Store(DirectX::XMVector3Rotate(GetUp().Load(), myRotationQuat.Load()));
  return u;
}

DM::Vec3f OrbitCamera::GetRelativeRight() const
{
  DM::Vec3f r;
  r.Store(DirectX::XMVector3Rotate(GetRight().Load(), myRotationQuat.Load()));
  return r;
}

DM::Vec3f OrbitCamera::GetForward() const
{
  return (myLookAt - myPosition).Normalize();
}

DM::Vec3f OrbitCamera::GetRight() const
{
  DM::Vec3f dir = GetForward();
  DM::Vec3f up  = GetUp();
  return dir.Cross(up).Normalize();
}

DM::Vec3f OrbitCamera::GetUp() const
{

  if (myUseCustomUp)
    return myCustomUp;
  else
  {
    DM::Vec3f dir = GetForward();
    DM::Vec3f up(0, 1, 0);
    float     d = up.Dot(dir);

    if (fabs(d) > 0.999f)
    {
      DM::Vec3f r(1, 0, 0);
      up = r.Cross(dir).Normalize();
    }

    return dir.Cross(up).Normalize().Cross(dir).Normalize();
  }
}

DM::Mat4x4 OrbitCamera::GetViewMatrix() const
{
  DM::Mat4x4 viewMat;
  viewMat.Store(DirectX::XMMatrixLookAtRH(myPosition.LoadAsVec4(1.0f), myLookAt.Load(), GetRelativeUp().Load()));
  return viewMat;
}

const DM::Vec3f& OrbitCamera::GetLookAt() const
{
  return myLookAt;
}

void OrbitCamera::SetLookAt(const DM::Vec3f& lookAt)
{
  myLookAt = lookAt;
}

void OrbitCamera::SetLookAt(float x, float y, float z)
{
  SetLookAt(DM::Vec3f(x, y, z));
}
