#pragma once
#include "Event.h"
#include <unordered_map>
class Subscriber
{
public:
  Subscriber() = default;
  Subscriber(const Subscriber& other);
  ~Subscriber();

  void Subscribe(Event::Type eventType);
  void UnSubscribe(Event::Type eventType);
  void UnSubscribeAll();

  Subscriber& operator=(const Subscriber& other);
  virtual void HandleEvent(const Event::Message& message) = 0;

private:
  void _copy(const Subscriber& other);

private:
  std::unordered_map<Event::Type, bool> mySubscriptions;
};