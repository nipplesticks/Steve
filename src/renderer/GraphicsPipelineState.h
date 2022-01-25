#pragma once

#include "../utility/Typedef.h"
#include <d3d12.h>
#include <string>
#include <vector>
class GraphicsPipelineState : public D3D12_GRAPHICS_PIPELINE_STATE_DESC
{
public:
  GraphicsPipelineState();
  ~GraphicsPipelineState();

  HRESULT SetVertexShader(const std::string& vertexShader);
  HRESULT SetHullShader(const std::string& hullShader);
  HRESULT SetDomainShader(const std::string& domainShader);
  HRESULT SetGeometryShader(const std::string& geometryShader);
  HRESULT SetPixelShader(const std::string& pixelShader);
  void    GenerateInputElementDesc();
  void    SetRootSignature(ID3D12RootSignature* rootSignature_p);
  HRESULT    GenerateRootSignature();
  void    SetInputElementDesc(const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElementDescs);

  HRESULT CreatePipelineState();

  ID3D12PipelineState* GetPipelineState() const;
  ID3D12RootSignature* GetRootSignature() const;

private:
  void _defaultValues();


  ID3DBlob*                             myVertexShader_p  = nullptr;
  ID3DBlob*                             myPixelShader_p   = nullptr;
  ID3D12PipelineState*                  myPipelineState_p = nullptr;
  ID3D12RootSignature*                  myRootSignature_p = nullptr;
  std::vector<D3D12_INPUT_ELEMENT_DESC> myInputElementDescs;
};