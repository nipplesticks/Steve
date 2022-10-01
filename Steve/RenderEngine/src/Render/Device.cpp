#include "pch.h"
#include "Render/Device.h"

using namespace Render;

ID3D12Device5* Device::gDevice_p = nullptr;

void Device::Init(uint16 debugLevel)
{
  if (debugLevel & ENABLE_DEBUG_LAYER)
  {
    ID3D12Debug* debugController_p = nullptr;
    HR_ASSERT(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_p)));
    debugController_p->EnableDebugLayer();
    if (debugLevel & ENABLE_DEBUG_CONTROLLER)
    {
      ID3D12Debug1* debugcontroller1_p;
      HR_ASSERT(debugController_p->QueryInterface(IID_PPV_ARGS(&debugcontroller1_p)));
      debugcontroller1_p->SetEnableGPUBasedValidation(true);
    }
  }

  IDXGIFactory6* factory_p = nullptr;
  IDXGIAdapter1* adapter_p = nullptr;
  CreateDXGIFactory(IID_PPV_ARGS(&factory_p));

  for (uint16 adapterIndex = 0;; adapterIndex++)
  {
    adapter_p = nullptr;
    if (DXGI_ERROR_NOT_FOUND == factory_p->EnumAdapters1(adapterIndex, &adapter_p))
      break;
    if (SUCCEEDED(
            D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device5), nullptr)))
      break;
    SafeRelease(&adapter_p);
  }
  if (adapter_p)
  {
    HR_ASSERT(D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&gDevice_p)));
    SafeRelease(&adapter_p);
  }
  else
  {
    factory_p->EnumWarpAdapter(IID_PPV_ARGS(&adapter_p));
    D3D12CreateDevice(adapter_p, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&gDevice_p));
  }
  SafeRelease(&factory_p);
}

ID3D12Device5* Device::GetDevice()
{
  return gDevice_p;
}
