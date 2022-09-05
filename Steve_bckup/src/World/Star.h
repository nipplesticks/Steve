#pragma once
#include "../entity/Drawable.h"
#include "../renderer/d3d12/GraphicsPipelineState.h"
#include "../renderer/lights/Light.h"
#include <vector>

class Star : public Drawable
{
public:
  Star();
  ~Star();

  void SetLightDirection(const DirectX::XMFLOAT4A& direction);

  const Light& GetLight() const;

  static std::vector<Star*> Active_Stars;

private:
  Light myLight;
  GraphicsPipelineState myPipelineState;
};