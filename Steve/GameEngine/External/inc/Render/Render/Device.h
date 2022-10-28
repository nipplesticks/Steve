#pragma once

#include <Common/Typedef.h>

struct ID3D12Device5;
namespace Render
{
  class Device
  {
  public:
    static constexpr uint16 ENABLE_DEBUG_LAYER      = 0x0001;
    static constexpr uint16 ENABLE_DEBUG_CONTROLLER = 0x0002;

  private:
    Device()  = default;
    ~Device() = default;

  public:
    static void           Init(uint16 debugLevel = 0x0000);
    static ID3D12Device5* GetDevice();
    static uint32         GetSrvUavCbvDescriptorSize();
    static uint32         GetRtvDescriptorHeapSize();
    static uint32         GetDsvDescriptorHeapSize();
    static uint32         GetSamplerDescriptorSize();

  private:
    static ID3D12Device5* gDevice_p;
    static uint32         gSrvUavCbvDescriptorSize;
    static uint32         gRtvDescriptorHeapSize;
    static uint32         gDsvDescriptorHeapSize;
    static uint32         gSamplerDescriptorSize;
  };
} // namespace Render
