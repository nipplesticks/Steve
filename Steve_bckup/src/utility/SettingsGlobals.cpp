#include "SettingsGlobals.h"

SettingsGlobals* SettingsGlobals::GetInstance()
{
  static SettingsGlobals sg;
  return &sg;
}
