#pragma once

#include "Event.h"
#include <unordered_map>
#include <vector>

class Subscriber;

class EventHandler
{
public:
  static void                PushMessage(Event::Message message);
  static void                HandleEvents();
  static void                StartSubscription(Event::Type type, Subscriber* subscriber_p);
  static void                CancelSubscription(Event::Type type, Subscriber* subscriber_p);

private:
  static std::vector<Event::Message>                                            myEventQueue;
  static std::unordered_map<Event::Type, std::unordered_map<Subscriber*, bool>> mySubscribers;
  static bool                                                                   FlushEvents;
};