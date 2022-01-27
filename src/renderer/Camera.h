#pragma once

#include "../utility/DMath.h"

class Camera
{
  struct View
  {
    float fov;
    float height;
    float width;
    float nearPlane;
    float farPlane;
    bool  isPerspective;
  };

public:
  Camera();
  Camera(const View& view);

  virtual ~Camera() = default;

  virtual void SetView(const View& view);
  virtual void SetPosition(float x, float y, float z);
  virtual void SetPosition(const DM::Vec3f& position);
  virtual void Move(const DM::Vec3f& translation);
  virtual void Move(float x, float y, float z);
  virtual void Rotate(float x, float y, float z);
  virtual void Rotate(const DM::Vec3f& rot);
  virtual void SetRotation(float x, float y, float z);
  virtual void SetRotation(const DM::Vec3f& axis);
  virtual void UseCustomUpVector(bool flag);
  virtual void SetCustomUpVector(const DM::Vec3f& up);
  virtual void SetCustomUpVector(float x, float y, float z);

  virtual const View&      GetView() const;
  virtual const DM::Vec3f& GetPosition() const;
  virtual const DM::Vec3f& GetForward() const = 0;
  virtual const DM::Vec3f& GetRight() const   = 0;
  virtual const DM::Vec3f& GetUp() const      = 0;
  virtual const DM::Vec4f& GetRotation() const;

  virtual DM::Mat4x4        GetViewMatrix() const = 0;
  virtual const DM::Mat4x4& GetProjectionMatrix() const;
  virtual DM::Mat4x4        GetViewProjectionMatrix() const;
  static Camera::View       GetDefaultView();

private:
  void _buildProjection();
  void _init();

protected:
  View       myView;
  DM::Mat4x4 myProjectionMatrix;
  DM::Vec3f  myPosition;
  DM::Vec3f  myCustomUp;
  DM::Vec4f  myRotationQuat;
  bool       myUseCustomUp = false;
};