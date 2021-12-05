#pragma once
#define NOMINMAX
#include <Windows.h>
#include <comdef.h>
#include <stdexcept>

#define HR_ASSERT(x)                                                                               \
  do                                                                                               \
  {                                                                                                \
    HRESULT hr_ = x;                                                                               \
    if (FAILED(hr_))                                                                               \
    {                                                                                              \
      _com_error err(hr_);                                                                         \
      CHAR       s_str[256] = {};                                                                  \
      printf("%s (%d): %ls", __FILE__, __LINE__, err.ErrorMessage());                              \
      sprintf_s(s_str, "%s (%d): %ls", __FILE__, __LINE__, err.ErrorMessage());                    \
                                                                                                   \
      MessageBoxA(GetActiveWindow(), s_str, "DirectX Error", 0);                                   \
      throw std::runtime_error(s_str);                                                             \
    }                                                                                              \
  } while (0)

#define AlignAs256(n)                                                                              \
  {                                                                                                \
    n + 255 & ~255                                                                                 \
  }