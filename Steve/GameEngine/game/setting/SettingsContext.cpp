#include "pch.h"
#include "SettingsContext.h"
#include <Windows.h>

SettingsContext SettingsContext::gSettingsContext;

template <typename A, typename B>
static inline bool ExistInMap(std::unordered_map<A, B>& map, const A& key)
{
  return map.find(key) != map.end();
}

SettingsContext::SettingsContext()
{
  LoadSettings();
}

SettingsContext* SettingsContext::GetInstance()
{
  return &gSettingsContext;
}

void SettingsContext::SetSettings(const Settings& settings)
{
  mySettings = settings;
}

uint32 SettingsContext::RouteAction(const std::string& action)
{
  if (ExistInMap(mySettings.ActionToMouseMapping, action))
    return mySettings.ActionToMouseMapping[action];
  else if (ExistInMap(mySettings.ActionToKeyboardMapping, action))
    return mySettings.ActionToKeyboardMapping[action];

  return (uint32)-1;
}

std::string SettingsContext::RouteInput(uint32 input)
{
  if (ExistInMap(mySettings.MouseToActionMapping, input))
    return mySettings.MouseToActionMapping[input];
  else if (ExistInMap(mySettings.KeyboardToActionMapping, input))
    return mySettings.KeyboardToActionMapping[input];

  return "";
}

const DM::Vec2i& SettingsContext::GetClientCenter() const
{
  return myClientCenter;
}

void SettingsContext::SetClientCenter(const DM::Vec2i& center)
{
  myClientCenter = center;
}

void SettingsContext::LoadSettings()
{
  const std::string ini        = "assets/config/inputMapping.ini";
  const std::string bmap       = "assets/config/vkButtonMap.ini";
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

      uint32 counter = 0;
      for (std::string& a : actionList)
      {
        char valBuffer[64];
        GetPrivateProfileStringA(
            section.c_str(), actionList[counter++].c_str(), "", valBuffer, 64, ini.c_str());
        std::string value(valBuffer);
        if (value.size() == 1)
        {
          uint32 k = (uint32)value[0];
          if (section == "Keyboard")
          {
            mySettings.ActionToKeyboardMapping[a] = k > 96 && k < 123 ? k - 32 : k;
            mySettings.KeyboardToActionMapping[k] = a;
          }
          else if (section == "Mouse")
          {
            mySettings.ActionToMouseMapping[a] = k;
            mySettings.MouseToActionMapping[k] = a;
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
              mySettings.ActionToKeyboardMapping[a] = k;
              mySettings.KeyboardToActionMapping[k] = a;
            }
            else if (section == "Mouse")
            {
              mySettings.ActionToMouseMapping[a] = k;
              mySettings.MouseToActionMapping[k] = a;
            }
          }
        }
      }
    }
  }
  if (GetPrivateProfileStringA("Sensitivity", NULL, NULL, buffer, bufferSize, ini.c_str()))
  {
    std::istringstream actionStream;
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
        GetPrivateProfileStringA("Sensitivity", action.c_str(), "", valBuffer, 64, ini.c_str());
        std::string value(valBuffer);
        mySettings.MouseSensitivity.x = std::atof(value.c_str());
      }
      else if (action == "SENSITIVITY_Y")
      {
        char valBuffer[64];
        GetPrivateProfileStringA("Sensitivity", action.c_str(), "", valBuffer, 64, ini.c_str());
        std::string value(valBuffer);
        mySettings.MouseSensitivity.y = std::atof(value.c_str());
      }
    }
  }
}

const Settings& SettingsContext::GetSettings() const
{
  return mySettings;
}
