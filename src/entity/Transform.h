#pragma once
#define NOMINMAX
#include "../utility/DMath.h"

class Transform
{
public:
  Transform(const DM::Vec3f& position  = DM::Vec3f(0.0f, 0.0f, 0.0f));
  virtual ~Transform() = default;

  virtual void SetPosition(const DM::Vec3f& position);
  virtual void SetPosition(float x, float y, float z);
  virtual void SetScale(const DM::Vec3f& scale);
  virtual void SetScale(float x, float y, float z);
  virtual void SetRotation(const DM::Vec3f& pitchYawRoll);
  virtual void SetRotation(float x, float y, float z);

  virtual void Move(const DM::Vec3f& translation);
  virtual void Move(float x, float y, float z);
  virtual void Scale(const DM::Vec3f& relativeScale);
  virtual void Scale(float x, float y, float z);
  virtual void Rotate(const DM::Vec3f& pitchYawRoll);
  virtual void Rotate(float x, float y, float z);

  virtual const DM::Vec3f& GetPosition() const;
  virtual const DM::Vec3f& GetScale() const;
  virtual const DM::Vec4f& GetRotation() const;
  virtual DM::Mat4x4       GetWorldMatrix() const;

private:
  DM::Vec3f myPosition;
  DM::Vec4f myRotation;
  DM::Vec3f myScale;
};