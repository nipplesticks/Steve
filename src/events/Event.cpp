#include "Event.h"
#include "EventHandler.h"


void Event::PushMessage(const Event::Message& message)
{
  EventHandler::PushMessage(message);
}
