#pragma once

namespace Render
{
  template <class Interface>
  static inline void SafeRelease(Interface** interfaceToRelease_pp)
  {
    if (*interfaceToRelease_pp != NULL)
    {
      (*interfaceToRelease_pp)->Release();

      (*interfaceToRelease_pp) = NULL;
    }
  }
} // namespace Render