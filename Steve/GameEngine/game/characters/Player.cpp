#include "pch.h"
#include "Player.h"
#include <iostream>

using namespace Render;

enum MOVEMENT
{
  FORWARD = 0,
  BACKWARD,
  RIGHT,
  LEFT,
  SPRINT,
  JUMP,
  CROUCH,
  QUICK_INVENTORY,
  USE
};

static inline uint16 BIT(MOVEMENT m)
{
  return (uint16)1 << m;
}

Player::Player()
{
  Subscribe(Event::KeyDown);
  Subscribe(Event::KeyUp);
  Subscribe(Event::MouseMoved);
  Subscribe(Event::MousePressed);
  Subscribe(Event::MouseReleased);
  Subscribe(Event::MouseWheel);
  myMovement = 0;
}

Player::~Player() { }

void Player::HandleEvent(const Event::Message& message)
{
  switch (message.EventType)
  {
  case Event::MouseMoved:
    _handleMouseMovedEvent(message);
    break;
  case Event::KeyDown:
  case Event::MousePressed:
    _handleInputEvent(message);
    break;
  case Event::MouseReleased:
  case Event::KeyUp:
    _handleInputReleaseEvent(message);
    break;
  default:
    break;
  }
}

void Player::Update(float dt)
{
  DM::Vec3f movement(
      1.0f * (bool)(myMovement & BIT(RIGHT)) + -1.0f * (bool)(myMovement & BIT(LEFT)),
      1.0f * (bool)(myMovement & BIT(JUMP)) + -1.0f * (bool)(myMovement & BIT(CROUCH)),
      1.0f * (bool)(myMovement & BIT(FORWARD)) + -1.0f * (bool)(myMovement & BIT(BACKWARD)));
  if (movement.LengthSq() > 0.0f)
    movement = movement.Normalize();
  Move(movement * dt * ((myMovement & BIT(SPRINT)) ? mySpeed * mySpeedMultiplier : mySpeed));
  Rotate(
      0,
      0,
      (1.0f * (bool)(myMovement & BIT(QUICK_INVENTORY)) + -1.0f * (bool)(myMovement & BIT(USE))) *
          dt * 45.f);
}

void Player::_handleMouseMovedEvent(const Event::Message& message)
{
  if (!myCameraLocked)
  {
    DM::Vec2f sens = SettingsContext::GetInstance()->GetSettings().MouseSensitivity;
    DM::Vec2f delta =
        message.MouseEvent.MousePosition - SettingsContext::GetInstance()->GetClientCenter();
    float dx = delta.x * sens.x;
    float dy = delta.y * sens.y;
    Rotate(dy, dx, 0);
  }
}

void Player::_handleInputEvent(const Render::Event::Message& message)
{
  SettingsContext* sc_p  = SettingsContext::GetInstance();
  uint32           input = message.EventType == Event::MousePressed ? message.MouseEvent.MouseButton
                                                                    : message.KeyEvent.KeyCode;
  std::string      action = sc_p->RouteInput(input);

  if (action == "FORWARD")
    myMovement |= BIT(FORWARD);
  if (action == "BACKWARD")
    myMovement |= BIT(BACKWARD);
  if (action == "STRAFE_RIGHT")
    myMovement |= BIT(RIGHT);
  if (action == "STRAFE_LEFT")
    myMovement |= BIT(LEFT);
  if (action == "SPRINT")
    myMovement |= BIT(SPRINT);
  if (action == "JUMP")
    myMovement |= BIT(JUMP);
  if (action == "CROUCH")
    myMovement |= BIT(CROUCH);
  if (action == "QUICK_INVENTORY")
    myMovement |= BIT(QUICK_INVENTORY);
  if (action == "USE")
    myMovement |= BIT(USE);
}

void Player::_handleInputReleaseEvent(const Render::Event::Message& message)
{
  SettingsContext* sc_p = SettingsContext::GetInstance();
  uint32      input     = message.EventType == Event::MouseReleased ? message.MouseEvent.MouseButton
                                                                    : message.KeyEvent.KeyCode;
  std::string action    = sc_p->RouteInput(input);

  if (action == "FORWARD")
    myMovement &= ~BIT(FORWARD);
  if (action == "BACKWARD")
    myMovement &= ~BIT(BACKWARD);
  if (action == "STRAFE_RIGHT")
    myMovement &= ~BIT(RIGHT);
  if (action == "STRAFE_LEFT")
    myMovement &= ~BIT(LEFT);
  if (action == "SPRINT")
    myMovement &= ~BIT(SPRINT);
  if (action == "JUMP")
    myMovement &= ~BIT(JUMP);
  if (action == "CROUCH")
    myMovement &= ~BIT(CROUCH);
  if (action == "QUICK_INVENTORY")
    myMovement &= ~BIT(QUICK_INVENTORY);
  if (action == "USE")
    myMovement &= ~BIT(USE);
}
