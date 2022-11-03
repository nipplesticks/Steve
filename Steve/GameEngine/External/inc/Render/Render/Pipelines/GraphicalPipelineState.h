#pragma once
#include <d3d12.h>
#include <string>
#include <vector>

#include "PipelineState.h"

namespace Render
{
  enum RenderTargetType : uint32
  {
    Position = 0u,
    Normal,
    Color,
    NUMBER_OF_RENDER_TARGET_TYPES
  };

  class GraphicalPipelineState : public PipelineState, public D3D12_GRAPHICS_PIPELINE_STATE_DESC
  {
  public:
    static bool USE_WIRE_FRAME;
    GraphicalPipelineState();
    ~GraphicalPipelineState();
    void SetVertexShader(const std::string& vertexShader);
    void SetHullShader(const std::string& hullShader);
    void SetDomainShader(const std::string& domainShader);
    void SetGeometryShader(const std::string& geometryShader);
    void SetPixelShader(const std::string& pixelShader);

    void AllowWireframe(bool flag);
    void EnableBlending();
    void GenerateInputElementDesc();
    void SetInputElementDesc(const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputElementDescs);

    void CreatePipelineState(const std::string& name);

    virtual ID3D12PipelineState* GetPipelineState() const override;

  private:
    void _initDefaultValues();

    ID3DBlob*            myVertexShader_p           = nullptr;
    ID3DBlob*            myHullShader_p             = nullptr;
    ID3DBlob*            myDomainShader_p           = nullptr;
    ID3DBlob*            myGeometryShader_p         = nullptr;
    ID3DBlob*            myPixelShader_p            = nullptr;
    ID3D12PipelineState* myPipelineStateWireframe_p = nullptr;
    bool                 myAllowWireframe           = true;

    std::vector<D3D12_INPUT_ELEMENT_DESC> myInputElementDescs;
  };
} // namespace Render