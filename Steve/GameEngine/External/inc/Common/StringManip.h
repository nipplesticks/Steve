#pragma once
#include <string>

namespace String
{
static inline std::string ToString(const std::wstring& wstr)
{
  std::string str(wstr.begin(), wstr.end());
  return str;
}
static inline std::wstring ToWString(const std::string& str)
{
  std::wstring wstr(str.begin(), str.end());
  return wstr;
}
}
