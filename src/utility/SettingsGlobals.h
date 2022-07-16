#pragma once

class SettingsGlobals
{
private:
  SettingsGlobals() = default;
  ~SettingsGlobals() = default;
public:
  static SettingsGlobals* GetInstance();

  float SENSITIVITY_X = 1.0f;
  float SENSITIVITY_Y = 1.0f;

};