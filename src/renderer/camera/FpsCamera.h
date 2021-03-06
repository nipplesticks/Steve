#pragma once
#include "Camera.h"

class FpsCamera : public Camera
{
public:
  // Inherited via Camera
  virtual DM::Vec3f  GetForward() const override;
  virtual DM::Vec3f  GetRight() const override;
  virtual DM::Vec3f  GetUp() const override;
  virtual DM::Mat4x4f GetViewMatrix() const override;
  virtual DM::Vec3f  GetRelativeForward() const override;
  virtual DM::Vec3f  GetRelativeUp() const override;
  virtual DM::Vec3f  GetRelativeRight() const override;

  void SetLookTo(float x, float y, float z);
  void SetLookTo(const DM::Vec3f& lookTo);

private:
  DM::Vec3f myLookTo;
};