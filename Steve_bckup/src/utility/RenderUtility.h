#pragma once
#define NOMINMAX
#include "Typedef.h"
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
    ((n) + 255 & ~255)                                                                             \
  }
#define AlignAs(a, n)                                                                              \
  {                                                                                                \
    (n) + ((a)-1) & ~((a)-1)                                                                       \
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

static bool
GetChannelInformation(DXGI_FORMAT format, uint* channelElementSize_p, uint* nrOfChannels_p)
{
  switch (format)
  {
  case DXGI_FORMAT_R32G32B32A32_TYPELESS:
  case DXGI_FORMAT_R32G32B32A32_FLOAT:
  case DXGI_FORMAT_R32G32B32A32_UINT:
  case DXGI_FORMAT_R32G32B32A32_SINT:
    *channelElementSize_p = sizeof(uint);
    *nrOfChannels_p       = 4;
    break;
  case DXGI_FORMAT_R32G32B32_TYPELESS:
  case DXGI_FORMAT_R32G32B32_FLOAT:
  case DXGI_FORMAT_R32G32B32_UINT:
  case DXGI_FORMAT_R32G32B32_SINT:
    *channelElementSize_p = sizeof(uint);
    *nrOfChannels_p       = 3;
    break;
  case DXGI_FORMAT_R16G16B16A16_TYPELESS:
  case DXGI_FORMAT_R16G16B16A16_FLOAT:
  case DXGI_FORMAT_R16G16B16A16_UNORM:
  case DXGI_FORMAT_R16G16B16A16_UINT:
  case DXGI_FORMAT_R16G16B16A16_SNORM:
  case DXGI_FORMAT_R16G16B16A16_SINT:
    *channelElementSize_p = sizeof(uint16);
    *nrOfChannels_p       = 4;
    break;
  case DXGI_FORMAT_R32G32_TYPELESS:
  case DXGI_FORMAT_R32G32_FLOAT:
  case DXGI_FORMAT_R32G32_UINT:
  case DXGI_FORMAT_R32G32_SINT:
    *channelElementSize_p = sizeof(uint);
    *nrOfChannels_p       = 2;
    break;
  case DXGI_FORMAT_R8G8B8A8_TYPELESS:
  case DXGI_FORMAT_R8G8B8A8_UNORM:
  case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
  case DXGI_FORMAT_R8G8B8A8_UINT:
  case DXGI_FORMAT_R8G8B8A8_SNORM:
  case DXGI_FORMAT_R8G8B8A8_SINT:
    *channelElementSize_p = sizeof(uint8);
    *nrOfChannels_p       = 4;
    break;
  case DXGI_FORMAT_R16G16_TYPELESS:
  case DXGI_FORMAT_R16G16_FLOAT:
  case DXGI_FORMAT_R16G16_UNORM:
  case DXGI_FORMAT_R16G16_UINT:
  case DXGI_FORMAT_R16G16_SNORM:
  case DXGI_FORMAT_R16G16_SINT:
    *channelElementSize_p = sizeof(uint16);
    *nrOfChannels_p       = 2;
    break;
  case DXGI_FORMAT_R32_TYPELESS:
  case DXGI_FORMAT_D32_FLOAT:
  case DXGI_FORMAT_R32_FLOAT:
  case DXGI_FORMAT_R32_UINT:
  case DXGI_FORMAT_R32_SINT:
    *channelElementSize_p = sizeof(uint);
    *nrOfChannels_p       = 1;
    break;
  case DXGI_FORMAT_R8G8_TYPELESS:
  case DXGI_FORMAT_R8G8_UNORM:
  case DXGI_FORMAT_R8G8_UINT:
  case DXGI_FORMAT_R8G8_SNORM:
  case DXGI_FORMAT_R8G8_SINT:
    *channelElementSize_p = sizeof(uint8);
    *nrOfChannels_p       = 1;
    break;
  case DXGI_FORMAT_R16_TYPELESS:
  case DXGI_FORMAT_R16_FLOAT:
  case DXGI_FORMAT_D16_UNORM:
  case DXGI_FORMAT_R16_UNORM:
  case DXGI_FORMAT_R16_UINT:
  case DXGI_FORMAT_R16_SNORM:
  case DXGI_FORMAT_R16_SINT:
    *channelElementSize_p = sizeof(uint16);
    *nrOfChannels_p       = 1;
    break;
  case DXGI_FORMAT_R8_TYPELESS:
  case DXGI_FORMAT_R8_UNORM:
  case DXGI_FORMAT_R8_UINT:
  case DXGI_FORMAT_R8_SNORM:
  case DXGI_FORMAT_R8_SINT:
  case DXGI_FORMAT_A8_UNORM:
    *channelElementSize_p = sizeof(uint8);
    *nrOfChannels_p       = 1;
    break;
  default:
    *channelElementSize_p = UINT_MAX;
    *nrOfChannels_p       = UINT_MAX;
    return false;
    break;
  }
  return true;
}