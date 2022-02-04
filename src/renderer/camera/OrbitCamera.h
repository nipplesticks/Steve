#pragma once

#include "Camera.h"

class OrbitCamera : public Camera
{
public:
  OrbitCamera();
  // Inherited via Camera
  virtual DM::Vec3f  GetRelativeForward() const override;
  virtual DM::Vec3f  GetRelativeUp() const override;
  virtual DM::Vec3f  GetRelativeRight() const override;
  virtual DM::Vec3f  GetForward() const override;
  virtual DM::Vec3f  GetRight() const override;
  virtual DM::Vec3f  GetUp() const override;
  virtual DM::Mat4x4 GetViewMatrix() const override;
  const DM::Vec3f&   GetLookAt() const;
  void               SetLookAt(const DM::Vec3f& lookAt);
  void               SetLookAt(float x, float y, float z);

private:
  
private:
  DM::Vec3f myLookAt;
};