#pragma once
#define NOMINMAX
#include "UtilityFuncs.h"
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
    (n) + 255 & ~255                                                                               \
  }
#define AlignAs(a, n)                                                                              \
  {                                                                                                \
    (n) + ((a) - 1) & ~((a) - 1)                                                                               \
  }

template <class Interface>
static inline void SafeRelease(Interface** ppInterfaceToRelease)
{
  if (*ppInterfaceToRelease != NULL)
  {
    (*ppInterfaceToRelease)->Release();

    (*ppInterfaceToRelease) = NULL;
  }
}

static D3D12_ROOT_PARAMETER_TYPE ConvertToParameterType(D3D_SHADER_INPUT_TYPE inputType)
{
  switch (inputType)
  {
  case D3D_SIT_CBUFFER: // CBV
    return D3D12_ROOT_PARAMETER_TYPE_CBV;
  case D3D_SIT_TEXTURE: // Texture
    return D3D12_ROOT_PARAMETER_TYPE_SRV;
  case D3D_SIT_UAV_RWTYPED: // UAV
    return D3D12_ROOT_PARAMETER_TYPE_UAV;
  }

  ASSERT_STR(false, "Passed input not defined (%d), eat ass\n", inputType);

  return D3D12_ROOT_PARAMETER_TYPE_CBV;
}

static D3D12_DESCRIPTOR_RANGE_TYPE ConvertToRangeType(D3D12_ROOT_PARAMETER_TYPE inputType)
{
  switch (inputType)
  {
  case D3D12_ROOT_PARAMETER_TYPE_CBV:
    return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
  case D3D12_ROOT_PARAMETER_TYPE_SRV:
    return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  case D3D12_ROOT_PARAMETER_TYPE_UAV:
    return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
  }

  ASSERT_STR(false, "Passed input not defined (%d), eat ass\n", inputType);

  return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
}