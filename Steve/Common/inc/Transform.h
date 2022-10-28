#pragma once

#include "DMath.h"

class Transform
{
public:
  static DM::Vec4f DEFAULT_FORWARD;
  static DM::Vec4f DEFAULT_UP;

  Transform();
  virtual ~Transform();

  virtual void SetPosition(float x, float y, float z);
  virtual void SetPosition(const DM::Vec3f& position);

  virtual void SetRotation(float x, float y, float z);
  virtual void SetRotation(const DM::Vec3f& axis);
  virtual void SetRotation(const DM::Vec4f& quaternion);

  virtual void SetScale(float x, float y, float z);
  virtual void SetScale(const DM::Vec3f& scale);

  virtual void SetOrigin(float x, float y, float z);
  virtual void SetOrigin(const DM::Vec3f& origin);

  virtual void Move(float x, float y, float z);
  virtual void Move(const DM::Vec3f& translation);

  virtual void Rotate(float x, float y, float z);
  virtual void Rotate(const DM::Vec3f& axis);

  virtual void Scale(float x, float y, float z);
  virtual void Scale(const DM::Vec3f& scale);

  virtual void UseCustomUp(bool flag);
  virtual void SetCustomUp(float x, float y, float z);
  virtual void SetCustomUp(const DM::Vec3f& up);

  virtual void SetForward(float x, float y, float z);
  virtual void SetForward(const DM::Vec3f& forwrad);

  virtual const DM::Vec4f& GetPosition() const;
  virtual const DM::Vec4f& GetRotation() const;
  virtual const DM::Vec4f& GetScale() const;

  virtual DM::Vec4f GetForward() const;
  virtual DM::Vec4f GetRight() const;
  virtual DM::Vec4f GetUp() const;

  virtual DM::Mat4x4f GetWorldMatrix() const;
  virtual DM::Mat4x4f GetInverseWorldMatrix() const;

  DM::Vec3f TransformToLocal(const DM::Vec3f& v);
  float     Distance(const Transform& other);
  float     DistanceSq(const Transform& other);
  DM::Vec3f Direction(const Transform& other, float& length);

protected:
  DM::Vec4f myPosition;
  DM::Vec4f myRotation;
  DM::Vec4f myScale;
  DM::Vec4f myOrigin;
  DM::Vec4f myCustomUp;
  bool      myUseCustomUp;
};