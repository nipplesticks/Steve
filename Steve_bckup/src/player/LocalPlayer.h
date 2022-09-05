#pragma once

#include "../entity/Drawable.h"
#include "../entity/Transform.h"
#include "../events/Subscriber.h"
#include "../renderer/camera/FpsCamera.h"

class LocalPlayer : public Drawable, public Subscriber
{
public:
  LocalPlayer();
  ~LocalPlayer() = default;
  // Inherited via Subscriber
  virtual void HandleEvent(const Event::Message& message) override;

  DM::Vec3f GetUp();
  void Update(float dt, float height);

  Camera* GetCamera();

  DM::Vec2i mpLast;

private:
  void _subscribeAllInputEvents();

private:
  FpsCamera myCamera;
  float     mySpeed            = 1.0f;
  float     mySprintMultiplier = 100.0f;
  bool      myMouseLocked      = true;
  bool      isSprinting        = false;
  uint16     myMovement;
};