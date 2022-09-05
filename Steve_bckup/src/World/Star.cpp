#include "Star.h"
#include "../renderer/mesh/MeshLoader.h"

std::vector<Star*> Star::Active_Stars;

Star::Star()
    : Drawable()
{
  Active_Stars.push_back(this);
  myLight.type      = LightType::DirectionalLight;
  myLight.direction = DirectX::XMFLOAT4A(-0.917060f, -0.398749f, 0.0f, 0.0f);
  myLight.color     = DirectX::XMFLOAT4A(1, 1, 1, 1);
  myLight.intensity = 1;
  myLight.dropOff   = 1;
  myLight.pow       = 1;
  myLight.radius    = 1;

  myPipelineState.SetVertexShader("assets/shaders/StarVertexShader.hlsl");
  myPipelineState.SetPixelShader("assets/shaders/StarPixelShader.hlsl");
  myPipelineState.GenerateInputElementDesc();
  myPipelineState.CreatePipelineState();
  SetGraphicsPipelineState(&myPipelineState);
  SetMesh(MeshLoader::GetMesh("star"));
  SetLights({myLight});
  BindWithDefaultResourceDescHeap();
}

Star::~Star()
{
  auto it = std::find(Active_Stars.begin(), Active_Stars.end(), this);
  if (it != Active_Stars.end())
  {
    Active_Stars.erase(it);
  }
}

void Star::SetLightDirection(const DirectX::XMFLOAT4A& direction)
{
  myLight.direction = direction;
  SetLights({myLight});
}

const Light& Star::GetLight() const
{
  return myLight;
}
