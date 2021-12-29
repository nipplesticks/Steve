#include "EventHandler.h"

std::map<Event::Type, std::vector<Event*>> EventHandler::myEventMap;

void EventHandler::PushEvent(Event* newEvent)
{
  myEventMap[newEvent->EventType].push_back(newEvent);
}

std::vector<Event*> EventHandler::GetEvents(Event::Type eventType)
{
  return myEventMap[eventType];
}

void EventHandler::ClearEvents(Event::Type eventType)
{
  myEventMap[eventType].clear();
}

void EventHandler::ClearAll()
{
  myEventMap.clear();
}
