#pragma once

#include <Common/Typedef.h>

struct ID3D12RootSignature;

namespace Render
{
  class Rootsignature
  {
  private:
    static Rootsignature gCRootsignature;
    static Rootsignature gGRootsignature;
    Rootsignature() = default;
    ~Rootsignature() = default;

  public:
    static uint16 MAX_ALLOWED_CBV;
    static uint16 MAX_ALLOWED_SRV;
    static uint16 MAX_ALLOWED_UAV;

    static void                 Init();
    static void                 Release();
    static ID3D12RootSignature* GetComputeRootsignature();
    static ID3D12RootSignature* GetGraphicRootsignature();

  private:
    ID3D12RootSignature* myRootSignature_p = nullptr;
  };
} // namespace Render
