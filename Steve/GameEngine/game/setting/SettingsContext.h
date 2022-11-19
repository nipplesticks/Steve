#pragma once
#include <Common/DMath.h>
#include <unordered_map>

struct Settings
{
  DM::Vec2f                               MouseSensitivity;
  std::unordered_map<std::string, uint32> ActionToKeyboardMapping;
  std::unordered_map<std::string, uint32> ActionToMouseMapping;
  std::unordered_map<uint32, std::string> KeyboardToActionMapping;
  std::unordered_map<uint32, std::string> MouseToActionMapping;
};

class SettingsContext
{
private:
  static SettingsContext gSettingsContext;
  SettingsContext();
  ~SettingsContext() = default;

public:
  static SettingsContext* GetInstance();

  void             LoadSettings();
  const Settings&  GetSettings() const;
  void             SetSettings(const Settings& settings);
  uint32           RouteAction(const std::string& action);
  std::string      RouteInput(uint32 input);
  const DM::Vec2i& GetClientCenter() const;
  void             SetClientCenter(const DM::Vec2i& center);

private:
  Settings  mySettings;
  DM::Vec2i myClientCenter;
};