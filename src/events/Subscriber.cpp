#include "Subscriber.h"
#include "EventHandler.h"

Subscriber::Subscriber(const Subscriber& other)
{
  _copy(other);
}

Subscriber::~Subscriber()
{
  UnSubscribeAll();
}

void Subscriber::Subscribe(Event::Type eventType)
{
  if (mySubscriptions[eventType] == false)
  {
    EventHandler::StartSubscription(eventType, this);
    mySubscriptions[eventType] = true;
  }
}

void Subscriber::UnSubscribe(Event::Type eventType)
{
  if (mySubscriptions[eventType] == true)
  {
    EventHandler::CancelSubscription(eventType, this);
    mySubscriptions[eventType] = false;
  }
  mySubscriptions.erase(eventType);
}

void Subscriber::UnSubscribeAll()
{
  for (auto & et : mySubscriptions)
    if (et.second)
      EventHandler::CancelSubscription(et.first, this);
  mySubscriptions.clear();
}

Subscriber& Subscriber::operator=(const Subscriber& other)
{
  if (this != &other)
  {
    UnSubscribeAll();
    _copy(other);
  }
  return *this;
}

void Subscriber::_copy(const Subscriber& other)
{
  for (auto& e : other.mySubscriptions)
    if (e.second)
      EventHandler::StartSubscription(e.first, this);
}
