#include "InputRouter.h"
#include <Windows.h>
#include <sstream>
#include <vector>
#include <iostream>
#include "../utility/SettingsGlobals.h"

template <typename A, typename B>
bool ExistInMap(std::unordered_map<A, B>& map, const A& key)
{
  return map.find(key) != map.end();
}


InputRouter::InputRouter()
{
  const std::string ini        = "config/inputmapping.ini";
  const std::string bmap       = "config/vkButtonMap.ini";
  const int         bufferSize = 1024 * 4;
  char              buffer[bufferSize];
  std::string       sections[] = {"Keyboard", "Mouse", "Gamepad", "Dev"};

  for (std::string& section : sections)
  {
    if (GetPrivateProfileStringA(section.c_str(), NULL, NULL, buffer, bufferSize, ini.c_str()))
    {
      std::vector<std::string> actionList;
      std::istringstream       actionStream;
      actionStream.str(std::string(buffer, bufferSize));
      std::string action = "";
      ZeroMemory(buffer, bufferSize);
      while (std::getline(actionStream, action, '\0'))
      {
        if (action == "")
          break;
        actionList.push_back(action);
      }

      uint counter = 0;
      for (std::string& a : actionList)
      {
        if (a == "SPRINT")
          int asdasd = 123;
        char valBuffer[64];
        GetPrivateProfileStringA(
            section.c_str(), actionList[counter++].c_str(), "", valBuffer, 64, ini.c_str());
        std::string value(valBuffer);
        if (value.size() == 1)
        {
          uint k               = (uint)value[0];
          if (section == "Keyboard")
          {
            myActionToKeyboardMapping[a] = k > 96 && k < 123 ? k - 32 : k;
            myKeyboardToActionMapping[k] = a;
          }
          else if (section == "Mouse")
          {
            myActionToMouseMapping[a] = k;
            myMouseToActionMapping[k] = a;
          }
        }
        else
        {
          int k = -1;
          k     = GetPrivateProfileIntA("vkButtonMap", value.c_str(), -1, bmap.c_str());
          if (k != -1)
          {
            if (section == "Keyboard")
            {
              myActionToKeyboardMapping[a] = k;
              myKeyboardToActionMapping[k] = a;
            }
            else if (section == "Mouse")
            {
              myActionToMouseMapping[a] = k;
              myMouseToActionMapping[k] = a;
            }
          }
        }
      }
    }
  }
  if (GetPrivateProfileStringA("Sensitivity", NULL, NULL, buffer, bufferSize, ini.c_str()))
  {
    std::istringstream       actionStream;
    actionStream.str(std::string(buffer, bufferSize));
    std::string action = "";
    ZeroMemory(buffer, bufferSize);
    while (std::getline(actionStream, action, '\0'))
    {
      if (action == "")
        break;
      if (action == "SENSITIVITY_X")
      {
        char valBuffer[64];
        GetPrivateProfileStringA(
            "Sensitivity", action.c_str(), "", valBuffer, 64, ini.c_str());
        std::string value(valBuffer);
        SettingsGlobals::GetInstance()->SENSITIVITY_X = std::atof(value.c_str());
      }
      else if (action == "SENSITIVITY_Y")
      {
        char valBuffer[64];
        GetPrivateProfileStringA("Sensitivity", action.c_str(), "", valBuffer, 64, ini.c_str());
        std::string value(valBuffer);
        SettingsGlobals::GetInstance()->SENSITIVITY_Y = std::atof(value.c_str());
      }
    }
  }
}

InputRouter* InputRouter::GetInstance()
{
  static InputRouter inputRouter;
  return &inputRouter;
}

uint InputRouter::RouteAction(const std::string& action)
{
  if (ExistInMap(myActionToMouseMapping, action))
    return myActionToMouseMapping[action];
  else if (ExistInMap(myActionToKeyboardMapping, action))
    return myActionToKeyboardMapping[action];
  return (uint)-1;
}

std::string InputRouter::RouteInput(uint input)
{
  if (ExistInMap(myMouseToActionMapping, input))
    return myMouseToActionMapping[input];
  else if (ExistInMap(myKeyboardToActionMapping, input))
    return myKeyboardToActionMapping[input];
  return "";
}
