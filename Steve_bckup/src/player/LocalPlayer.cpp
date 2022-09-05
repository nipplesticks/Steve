#include "LocalPlayer.h"
#include "../Input/InputRouter.h"
#include "../utility/SettingsGlobals.h"
#include <iostream>

#define FORWARD_BIT 0x1
#define BACKWARD_BIT 0x2
#define RIGHT_BIT 0x4
#define LEFT_BIT 0x8
#define SPRINT_BIT 0x10
#define FORWARD ((uint16)1 << 0)
#define BACKWARD ((uint16)1 << 1)
#define RIGHT ((uint16)1 << 2)
#define LEFT ((uint16)1 << 3)
#define SPRINT ((uint16)1 << 4)

LocalPlayer::LocalPlayer()
    : Drawable()
    , Subscriber()
{
  myCamera = FpsCamera();
  myCamera.SetLookTo(0, 0, 1);
  //myCamera.SetCustomUpVector(0, 1, 0);
  myCamera.UseCustomUpVector(true);
  myMovement = 0;
  _subscribeAllInputEvents();
}

void LocalPlayer::Update(float dt, float height)
{
  DM::Vec3f pos   = GetPosition();
  DM::Vec3f oldUp = myCamera.GetRelativeUp();
  DM::Vec3f up    = pos.Normalize();
  myCamera.SetCustomUpVector(up);
  DM::Vec3f right   = myCamera.GetRelativeRight();
  DM::Vec3f forward = up.Cross(right).Normalize();
  right             = forward.Cross(up).Normalize();

  DM::Vec3f vel(1.0f * (bool)(myMovement & RIGHT_BIT) + -1.0f * (bool)(myMovement & LEFT_BIT),
                0,
                1.0f * (bool)(myMovement & FORWARD_BIT) +
                    -1.0f * (bool)(myMovement & BACKWARD_BIT));

  if (vel.LengthSq())
    vel = vel.Normalize();

  pos = pos + (forward * vel.z + right * vel.x) * dt *
                  ((myMovement & SPRINT_BIT) ? mySpeed * mySprintMultiplier : mySpeed);

  SetPosition(pos.Normalize() * (height + 2));
  myCamera.SetPosition(GetPosition());
  
  DM::Mat3x3f m = up.GetRotationFrom(oldUp);
  myCamera.RotateFromRotationMatrix(m);
  
  myCamera.SetAsMainCameraAndUpdate();
}

Camera* LocalPlayer::GetCamera()
{
  return &myCamera;
}

void LocalPlayer::_subscribeAllInputEvents()
{
  Subscribe(Event::KeyDown);
  Subscribe(Event::KeyUp);
  Subscribe(Event::MouseMoved);
  Subscribe(Event::MousePressed);
  Subscribe(Event::MouseReleased);
  Subscribe(Event::MouseWheel);
}

void LocalPlayer::HandleEvent(const Event::Message& message)
{
  const SettingsGlobals* const sg_p = SettingsGlobals::GetInstance();
  InputRouter*                 ir_p = InputRouter::GetInstance();
  static bool                  lol  = false;
  switch (message.EventType)
  {
  case Event::Type::MouseMoved:
    if (!lol)
    {
      lol    = true;
      mpLast = message.MouseEvent.MousePosition;
    }
    if (myMouseLocked)
    {
      float dx = ((float)message.MouseEvent.MouseDelta.x - mpLast.x) * -sg_p->SENSITIVITY_X;
      float dy = ((float)message.MouseEvent.MouseDelta.y - mpLast.y) * -sg_p->SENSITIVITY_Y;
      myCamera.Rotate(dy, dx, 0.0f);
    }
    break;
  case Event::Type::MouseWheel:
    break;
  case Event::Type::MousePressed:
    break;
  case Event::Type::MouseReleased:
    break;
  case Event::Type::KeyDown:
  {
    std::string action = ir_p->RouteInput(message.KeyEvent.KeyCode);
    if (action == "FORWARD")
      myMovement |= FORWARD;
    else if (action == "BACKWARD")
      myMovement |= BACKWARD;
    if (action == "STRAFE_RIGHT")
      myMovement |= RIGHT;
    else if (action == "STRAFE_LEFT")
      myMovement |= LEFT;
    else if (action == "SPRINT")
      myMovement |= SPRINT;
    break;
  }
  case Event::Type::KeyUp:
  {
    std::string action = ir_p->RouteInput(message.KeyEvent.KeyCode);
    std::cout << action << " released!\n";
    if (action == "FORWARD")
      myMovement &= ~FORWARD;
    else if (action == "BACKWARD")
      myMovement &= ~BACKWARD;
    if (action == "STRAFE_RIGHT")
      myMovement &= ~RIGHT;
    else if (action == "STRAFE_LEFT")
      myMovement &= ~LEFT;
    else if (action == "SPRINT")
      myMovement &= ~SPRINT;
    break;
  }
  default:
    break;
  }
}

DM::Vec3f LocalPlayer::GetUp()
{
  return myCamera.GetUp();
}
