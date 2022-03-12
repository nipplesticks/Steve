#pragma once
#include "Resource.h"

class RenderTarget : public Resource
{
public:
  enum RenderTargetType : uint
  {
    Position = 0u,
    Normal,
    Color,
    PickableID,
    NUMBER_OF_RENDER_TARGET_TYPES
  };

  RenderTarget() = default;
  ~RenderTarget() = default;
public:
  void Create(uint        width,
              uint        height,
              RenderTargetType type,
              DXGI_FORMAT format    = DXGI_FORMAT_R8G8B8A8_UNORM)
  {
    myRenderTargetType = type;
    Init(Resource_Type::RenderTarget, width, format, height);

    switch (myRenderTargetType)
    {
    case Position:
      SetName("RenderTarget_Position");
      break;
    case Normal:
      SetName("RenderTarget_Normal");
      break;
    case Color:
      SetName("RenderTarget_Normal");
      break;
    case PickableID:
      SetName("RenderTarget_PickableID");
      break;
    }

  }
  RenderTargetType GetRenderTargetType() const
  {
    return myRenderTargetType;
  }

private:
  RenderTargetType myRenderTargetType = RenderTargetType::NUMBER_OF_RENDER_TARGET_TYPES;
};