#include "pch.h"
#include "Render/Resource/DepthBuffer.h"

using namespace Render;

void Render::DepthBuffer::Create(const std::string& name, uint16 width, uint16 height)
{
  Init(Resource_Type::DepthBuffer, name, width, DXGI_FORMAT_D32_FLOAT, height);
}

uint32 Render::DepthBuffer::GetClassSize() const
{
  return sizeof(DepthBuffer);
}
