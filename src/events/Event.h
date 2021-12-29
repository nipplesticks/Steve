#pragma once
#include "../utility/DMath.h"

class Event
{
public:
  enum Type
  {
    MouseMoved = 0,
    MouseWheel,
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
  EventMouseMoved(Event::Type eventType)
      : Event(eventType) {};
  DM::Vec2i MousePosition;
  DM::Vec2i MouseDelta;
  bool      LButtonPressed = false;
  bool      MButtonPressed = false;
  bool      RButtonPressed = false;
};

class EventMouseWheel : public Event
{
public:
  EventMouseWheel(Event::Type eventType)
      : Event(eventType) {};
  int Delta = 0;
};