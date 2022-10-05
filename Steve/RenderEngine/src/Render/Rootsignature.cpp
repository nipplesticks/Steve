#include "pch.h"
#include "Render/Rootsignature.h"
#include <vector>

using namespace Render;

Rootsignature Rootsignature::gCRootsignature;
Rootsignature Rootsignature::gGRootsignature;
uint16        Rootsignature::MAX_ALLOWED_CBV = 32;
uint16        Rootsignature::MAX_ALLOWED_SRV = 16;
uint16        Rootsignature::MAX_ALLOWED_UAV = 16;

void Rootsignature::Init()
{
  D3D12_ROOT_PARAMETER                rootParams[3] = {};
  std::vector<D3D12_DESCRIPTOR_RANGE> cbvRanges(MAX_ALLOWED_CBV);
  std::vector<D3D12_DESCRIPTOR_RANGE> srvRanges(MAX_ALLOWED_SRV);
  std::vector<D3D12_DESCRIPTOR_RANGE> uavRanges(MAX_ALLOWED_UAV);

  for (uint16 i = 0; i < MAX_ALLOWED_CBV; i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc            = {};
    rangeDesc.RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    rangeDesc.NumDescriptors                    = 1;
    rangeDesc.RegisterSpace                     = 0;
    rangeDesc.BaseShaderRegister                = i;
    rangeDesc.OffsetInDescriptorsFromTableStart = i;
    cbvRanges[i]                                = rangeDesc;
  }
  for (uint16 i = 0; i < MAX_ALLOWED_SRV; i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc            = {};
    rangeDesc.RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    rangeDesc.NumDescriptors                    = 1;
    rangeDesc.RegisterSpace                     = 0;
    rangeDesc.BaseShaderRegister                = i;
    rangeDesc.OffsetInDescriptorsFromTableStart = i;
    srvRanges[i]                                = rangeDesc;
  }
  for (uint16 i = 0; i < MAX_ALLOWED_UAV; i++)
  {
    D3D12_DESCRIPTOR_RANGE rangeDesc            = {};
    rangeDesc.RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
    rangeDesc.NumDescriptors                    = 1;
    rangeDesc.RegisterSpace                     = 0;
    rangeDesc.BaseShaderRegister                = i;
    rangeDesc.OffsetInDescriptorsFromTableStart = i;
    uavRanges[i]                                = rangeDesc;
  }

  rootParams[0].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[0].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[0].DescriptorTable.NumDescriptorRanges = MAX_ALLOWED_CBV;
  rootParams[0].DescriptorTable.pDescriptorRanges   = cbvRanges.data();

  rootParams[1].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[1].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[1].DescriptorTable.NumDescriptorRanges = MAX_ALLOWED_SRV;
  rootParams[1].DescriptorTable.pDescriptorRanges   = srvRanges.data();

  rootParams[2].ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  rootParams[2].ShaderVisibility                    = D3D12_SHADER_VISIBILITY_ALL;
  rootParams[2].DescriptorTable.NumDescriptorRanges = MAX_ALLOWED_UAV;
  rootParams[2].DescriptorTable.pDescriptorRanges   = uavRanges.data();
  D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSigDesc   = {};
  rootSigDesc.Version                               = D3D_ROOT_SIGNATURE_VERSION_1_0;
  rootSigDesc.Desc_1_0.Flags         = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
  rootSigDesc.Desc_1_0.NumParameters = 3;
  rootSigDesc.Desc_1_0.pParameters   = &rootParams[0];

  D3D12_STATIC_SAMPLER_DESC samplerDesc  = {};
  samplerDesc.Filter                     = D3D12_FILTER_ANISOTROPIC;
  samplerDesc.AddressU                   = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.AddressV                   = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.AddressW                   = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
  samplerDesc.MaxAnisotropy              = 16;
  samplerDesc.RegisterSpace              = 0;
  samplerDesc.MinLOD                     = -D3D12_FLOAT32_MAX;
  samplerDesc.MaxLOD                     = D3D12_FLOAT32_MAX;
  samplerDesc.MipLODBias                 = 0;
  samplerDesc.ShaderRegister             = 0;
  samplerDesc.ShaderVisibility           = D3D12_SHADER_VISIBILITY_ALL;
  rootSigDesc.Desc_1_0.pStaticSamplers   = &samplerDesc;
  rootSigDesc.Desc_1_0.NumStaticSamplers = 1;

  ID3DBlob* errorBlob_p     = nullptr;
  ID3DBlob* signatureBlob_p = nullptr;

  HR_ASSERT(D3D12SerializeRootSignature(
      &rootSigDesc.Desc_1_0, rootSigDesc.Version, &signatureBlob_p, &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  HR_ASSERT(
      Device::GetDevice()->CreateRootSignature(0,
                                               signatureBlob_p->GetBufferPointer(),
                                               signatureBlob_p->GetBufferSize(),
                                               IID_PPV_ARGS(&gGRootsignature.myRootSignature_p)));
  gGRootsignature.myRootSignature_p->SetName(L"gGRootsignature");

  rootSigDesc.Desc_1_0.Flags = D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
                               D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
  HR_ASSERT(D3D12SerializeRootSignature(
      &rootSigDesc.Desc_1_0, rootSigDesc.Version, &signatureBlob_p, &errorBlob_p));

  if (errorBlob_p != nullptr)
    printf("%s\n", (char*)errorBlob_p->GetBufferPointer());

  HR_ASSERT(
      Device::GetDevice()->CreateRootSignature(0,
                                               signatureBlob_p->GetBufferPointer(),
                                               signatureBlob_p->GetBufferSize(),
                                               IID_PPV_ARGS(&gCRootsignature.myRootSignature_p)));
  gCRootsignature.myRootSignature_p->SetName(L"gCRootsignature");
}

void Rootsignature::Release()
{
  SafeRelease(&gCRootsignature.myRootSignature_p);
  SafeRelease(&gGRootsignature.myRootSignature_p);
}

ID3D12RootSignature* Rootsignature::GetComputeRootsignature()
{
  return gCRootsignature.myRootSignature_p;
}

ID3D12RootSignature* Rootsignature::GetGraphicRootsignature()
{
  return gGRootsignature.myRootSignature_p;
}
