#include "pch.h"
#include "Render/Resource/IndexBuffer.h"

using namespace Render;

void IndexBuffer::Create(const std::string& name, uint32 numIndices)
{
  Init(Resource_Type::IndexBuffer,
       name,
       numIndices * sizeof(uint32),
       DXGI_FORMAT_UNKNOWN,
       1,
       1,
       numIndices);
}

uint32 Render::IndexBuffer::GetClassSize() const
{
  return sizeof(IndexBuffer);
}
