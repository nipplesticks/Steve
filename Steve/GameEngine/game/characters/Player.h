#pragma once

#include <Render/Window/WindowEvent.h>
#include <Render/Render/Camera/Camera.h>

class Player : public Render::Camera, public Render::Event::Subscriber
{
public:
  Player();
  ~Player();

  // Inherited via Subscriber
  virtual void HandleEvent(const Render::Event::Message& message) override;

  void Update(float dt);

private:
  void _handleMouseMovedEvent(const Render::Event::Message& message);
  void _handleInputEvent(const Render::Event::Message& message);
  void _handleInputReleaseEvent(const Render::Event::Message& message);

private:
  bool myCameraLocked = false;
  uint16 myMovement;
  float  mySpeed = 1.0f;
  float  mySpeedMultiplier = 2.0f;
};