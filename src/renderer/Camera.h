#pragma once

#include "../utility/DMath.h"

class Camera
{
public:
  struct View
  {
    float fov;
    float height;
    float width;
    float nearPlane;
    float farPlane;
  };

public:
  Camera();
  ~Camera();

  void             SetView(const View& view);
  void             SetPosition(const DM::Vec4f& position);
  void             SetLookAt(const DM::Vec4f& point);
  void             SetUp(const DM::Vec4f& up);

  const DM::Vec4f& GetPosition() const;
  const DM::Vec4f& GetLookAt() const;
  const DM::Vec4f& GetUp() const;

  DM::Mat4x4 GetViewProjection();

private:
  DM::Mat4x4 myViewMatrix;
  DM::Mat4x4 myProjectionMatrix;
  DM::Vec4f  myPosition;
  DM::Vec4f  myLookAt;
  DM::Vec4f  myUp;
};