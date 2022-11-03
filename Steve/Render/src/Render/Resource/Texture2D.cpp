#include "pch.h"
#include "Render/Resource/Texture2D.h"

using namespace Render;

void Texture2D::Create(
    const std::string& name, uint32 width, uint32 height, DXGI_FORMAT format, bool cpuAccess)
{
  Init(Resource_Type::Texture2D, name, width, format, height);
}

uint32 Render::Texture2D::GetClassSize() const
{
  return sizeof(Texture2D);
}
