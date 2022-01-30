#pragma once
#include "../utility/DMath.h"
#include "../utility/Typedef.h"

class Event
{
public:
  enum Type
  {
    MouseMoved = 0,
    MouseWheel,
    MousePressed,
    MouseReleased,
    KeyDown,
    KeyUp,
    TextTyped,
    NREVENTS
  };

public:
  Event(Event::Type eventType);
  void Signal();
  Event::Type EventType;
};

class EventMouseMoved : public Event
{
public:
  EventMouseMoved()
      : Event(MouseMoved) {};
  DM::Vec2i MousePosition;
  DM::Vec2i MouseDelta;
  bool      LButtonPressed = false;
  bool      MButtonPressed = false;
  bool      RButtonPressed = false;
};

class EventMousePressed : public Event
{
public:
  EventMousePressed()
      : Event(MousePressed) {};
  DM::Vec2i MousePosition;
  bool      LButtonPressed = false;
  bool      MButtonPressed = false;
  bool      RButtonPressed = false;
};

class EventMouseReleased : public Event
{
public:
  EventMouseReleased()
      : Event(MouseReleased) {};
  DM::Vec2i MousePosition;
  bool      LButtonReleased = false;
  bool      MButtonReleased = false;
  bool      RButtonReleased = false;
};

class EventMouseWheel : public Event
{
public:
  EventMouseWheel()
      : Event(MouseWheel) {};
  int Delta = 0;
};
class EventKeyDown : public Event
{
public:
  EventKeyDown()
      : Event(KeyDown) {};
  uint16 KeyCode = -1;
};
class EventKeyUp : public Event
{
public:
  EventKeyUp()
      : Event(KeyUp) {};
  uint16 KeyCode = -1;
};
class EventTextTyped : public Event
{
public:
  EventTextTyped()
      : Event(TextTyped) {};
  uint KeyCode = -1;
};