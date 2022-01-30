#pragma once

#include "../utility/Typedef.h"
#include <string>
#include <unordered_map>

class KeyboardInput
{
public:
  static void Update();
  static bool IsKeyFirstPressedThisFrame(const std::string& action);
  static bool IsKeyPressed(const std::string& action);
  static bool IsKeyReleased(const std::string& action);
  static void SetActionToKeyMap(const std::unordered_map<std::string, uint16>& actionToKeyMap);
  static void SetAnActionToKey(const std::string& action, uint16 key);
  static std::string GetTextEntered();
  static void        ClearTextEntered();

private:
  KeyboardInput()  = default;
  ~KeyboardInput() = default;

  static std::unordered_map<std::string, uint16> myActionToKeyMap;
  static std::unordered_map<uint16, bool>        myKeyPressedMap;
  static std::unordered_map<uint16, bool>        myKeyReleasedMap;
  static std::unordered_map<uint16, bool>        myKeyFirstPressedThisFrameMap;
  static std::string                             myTextEntered;
};