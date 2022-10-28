#include "pch.h"
#include "Window/WindowEvent.h"

using namespace Render::Event;

std::vector<Message>                                            EventHandler::myEventQueue;
std::unordered_map<Type, std::unordered_map<Subscriber*, bool>> EventHandler::mySubscribers;
bool                                                            EventHandler::SkipEvents = false;

Render::Event::Subscriber::Subscriber(const Subscriber& other)
{
  _copy(other);
}

Render::Event::Subscriber::~Subscriber()
{
  UnSubscribeAll();
}

void Render::Event::Subscriber::Subscribe(Event::Type eventType)
{
  if (mySubscriptions[eventType] == false)
  {
    EventHandler::StartSubscription(eventType, this);
    mySubscriptions[eventType] = true;
  }
}

void Render::Event::Subscriber::UnSubscribe(Event::Type eventType)
{
  if (mySubscriptions[eventType] == true)
  {
    EventHandler::CancelSubscription(eventType, this);
    mySubscriptions[eventType] = false;
  }
  mySubscriptions.erase(eventType);
}

void Render::Event::Subscriber::UnSubscribeAll()
{
  for (auto& et : mySubscriptions)
    if (et.second)
      EventHandler::CancelSubscription(et.first, this);
  mySubscriptions.clear();
}

Subscriber& Render::Event::Subscriber::operator=(const Subscriber& other)
{
  if (this != &other)
  {
    UnSubscribeAll();
    _copy(other);
  }
  return *this;
}

void Render::Event::Subscriber::_copy(const Subscriber& other)
{
  for (auto& e : other.mySubscriptions)
    if (e.second)
      EventHandler::StartSubscription(e.first, this);
}

void Render::Event::EventHandler::PushMessage(Event::Message message)
{
  myEventQueue.push_back(message);
}

void Render::Event::EventHandler::HandleEvents()
{
  for (Event::Message& m : myEventQueue)
  {
    if (m.EventType == Event::LostFocus)
      SkipEvents = true;
    else if (m.EventType == Event::GainedFocus)
      SkipEvents = false;
    if (!SkipEvents)
    {
      for (auto& subscriber : mySubscribers[m.EventType])
      {
        if (subscriber.second)
          subscriber.first->HandleEvent(m);
      }
    }
  }
  myEventQueue.clear();
}

void Render::Event::EventHandler::StartSubscription(Event::Type type, Subscriber* subscriber_p)
{
  mySubscribers[type][subscriber_p] = true;
}

void Render::Event::EventHandler::CancelSubscription(Event::Type type, Subscriber* subscriber_p)
{
  mySubscribers[type][subscriber_p] = false;
  mySubscribers[type].erase(subscriber_p);
}
