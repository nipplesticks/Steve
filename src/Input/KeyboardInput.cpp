#include "KeyboardInput.h"
#include "../events/EventHandler.h"

std::unordered_map<std::string, uint16> KeyboardInput::myActionToKeyMap;
std::unordered_map<uint16, bool>        KeyboardInput::myKeyPressedMap;
std::unordered_map<uint16, bool>        KeyboardInput::myKeyReleasedMap;
std::unordered_map<uint16, bool>        KeyboardInput::myKeyFirstPressedThisFrameMap;
std::string                             KeyboardInput::myTextEntered = "";

void KeyboardInput::Update()
{
  std::vector<Event*> keyDownEvents = EventHandler::GetEvents(Event::KeyDown);
  EventHandler::ClearEvents(Event::KeyDown);
  std::vector<Event*> keyUpEvents = EventHandler::GetEvents(Event::KeyUp);
  EventHandler::ClearEvents(Event::KeyUp);
  std::vector<Event*> textTypedEvent = EventHandler::GetEvents(Event::TextTyped);
  EventHandler::ClearEvents(Event::TextTyped);

  myKeyFirstPressedThisFrameMap.clear();
  for (Event* event_p : keyDownEvents)
  {
    EventKeyDown* e_p                           = (EventKeyDown*)event_p;
    myKeyFirstPressedThisFrameMap[e_p->KeyCode] = !myKeyPressedMap[e_p->KeyCode];
    myKeyPressedMap[e_p->KeyCode]               = true;
    delete e_p;
  }

  myKeyReleasedMap.clear();
  for (Event* event_p : keyUpEvents)
  {
    EventKeyUp* e_p                = (EventKeyUp*)event_p;
    myKeyReleasedMap[e_p->KeyCode] = true;
    myKeyPressedMap[e_p->KeyCode]  = false;
    delete e_p;
  }

  for (Event* event_p : textTypedEvent)
  {
    EventTextTyped* e_p = (EventTextTyped*)event_p;
    if (e_p->KeyCode > 31 && e_p->KeyCode < 126)
      myTextEntered += (char)e_p->KeyCode;
    delete e_p;
  }
}

bool KeyboardInput::IsKeyFirstPressedThisFrame(const std::string& action)
{
  return myKeyFirstPressedThisFrameMap[myActionToKeyMap[action]];
}

bool KeyboardInput::IsKeyPressed(const std::string& action)
{
  return myKeyPressedMap[myActionToKeyMap[action]];
}

bool KeyboardInput::IsKeyReleased(const std::string& action)
{
  return myKeyReleasedMap[myActionToKeyMap[action]];
}

void KeyboardInput::SetActionToKeyMap(const std::unordered_map<std::string, uint16>& actionToKeyMap)
{
  myActionToKeyMap = actionToKeyMap;
}

void KeyboardInput::SetAnActionToKey(const std::string& action, uint16 key)
{
  myActionToKeyMap[action] = key;
}

std::string KeyboardInput::GetTextEntered()
{
  return myTextEntered;
}

void KeyboardInput::ClearTextEntered()
{
  myTextEntered = "";
}
