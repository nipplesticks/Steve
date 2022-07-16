#pragma once
#include <unordered_map>
#include "../utility/Typedef.h"

class InputRouter
{
private:
  InputRouter();
  ~InputRouter() = default;
public:
  static InputRouter* GetInstance();
  uint                RouteAction(const std::string& action);
  std::string         RouteInput(uint input);

  std::unordered_map<std::string, uint> myActionToKeyboardMapping;
  std::unordered_map<std::string, uint> myActionToMouseMapping;
  std::unordered_map<uint, std::string> myKeyboardToActionMapping;
  std::unordered_map<uint, std::string> myMouseToActionMapping;

};