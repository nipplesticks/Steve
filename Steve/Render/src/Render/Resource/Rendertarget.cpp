#include "pch.h"
#include "Render/Resource/Rendertarget.h"

using namespace Render;

void RenderTarget::Create(
    const std::string& name, uint32 width, uint32 height, RenderTargetType type, DXGI_FORMAT format)
{
  myRenderTargetType = type;
  Init(Resource_Type::RenderTarget, name, width, format, height);
}

RenderTargetType RenderTarget::GetRenderTargetType() const
{
  return myRenderTargetType;
}

uint32 Render::RenderTarget::GetClassSize() const
{
  return sizeof(RenderTarget);
}
