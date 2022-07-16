#include "EventHandler.h"
#include "Subscriber.h"

std::vector<Event::Message>                                            EventHandler::myEventQueue;
std::unordered_map<Event::Type, std::unordered_map<Subscriber*, bool>> EventHandler::mySubscribers;
bool EventHandler::FlushEvents = false;

void EventHandler::PushMessage(Event::Message message)
{
  myEventQueue.push_back(message);
}

void EventHandler::HandleEvents()
{
  for (Event::Message& m : myEventQueue)
  {
    if (m.EventType == Event::LostFocus)
      FlushEvents = true;
    else if (m.EventType == Event::GainedFocus)
      FlushEvents = false;
    if (!FlushEvents)
      for (auto& subscriber : mySubscribers[m.EventType])
      {
        if (subscriber.second)
          subscriber.first->HandleEvent(m);
      }
  }
  myEventQueue.clear();
}

void EventHandler::StartSubscription(Event::Type type, Subscriber* subscriber_p)
{
  mySubscribers[type][subscriber_p] = true;
}

void EventHandler::CancelSubscription(Event::Type type, Subscriber* subscriber_p)
{
  mySubscribers[type][subscriber_p] = false;
  mySubscribers[type].erase(subscriber_p);
}
