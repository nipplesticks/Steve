#pragma once

#include "Event.h"
#include <map>
#include <vector>

class EventHandler
{
public:
  static void                PushEvent(Event* newEvent);
  static std::vector<Event*> GetEvents(Event::Type eventType);
  static void                ClearEvents(Event::Type eventType);
  static void                ClearAll();

private:
  static std::map<Event::Type, std::vector<Event*>> myEventMap;
};