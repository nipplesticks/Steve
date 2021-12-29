#include "Event.h"
#include "EventHandler.h"

Event::Event(Event::Type eventType)
{
  EventType = eventType;
}

void Event::Signal()
{
  EventHandler::PushEvent(this);
}
