#pragma once

#include "../utility/DMath.h"

class Camera2
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
  Camera2();
  ~Camera2();

  void SetView(const View& view);
  void SetPosition(float x, float y, float z);
  void SetPosition(const DM::Vec3f& position);
  void SetLookAt(float x, float y, float z);
  void SetLookAt(const DM::Vec3f& lookAt);
  void Rotate(float dx, float dy);
  void Zoom(float factor);
  void Roll(float d);
  void SetMaxZoom(float z);

  const DM::Vec3f& GetPosition() const;
  const DM::Vec3f& GetLookAt() const;
  const DM::Vec3f& GetUp() const;
  const DM::Vec3f& GetRight() const;

  DM::Mat4x4 GetViewProjection();

private:
  void _calcAxis();
  void _rotateAxis(float dx, float dy);

private:
  DM::Mat4x4 myViewMatrix;
  DM::Mat4x4 myProjectionMatrix;

  DM::Vec3f myPosition;

  DM::Vec3f myLookAt;

  DM::Vec3f myTranslatedUp;
  DM::Vec3f myTranslatedRight;
  float     myMaxZoom = 1.0f;

};