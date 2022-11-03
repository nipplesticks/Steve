#include "pch.h"
#include "Render/Resource/IndexBuffer.h"

using namespace Render;

void IndexBuffer::Create(const std::string& name, uint32 numIndices)
{
  Init(Resource_Type::IndexBuffer, name, numIndices * sizeof(uint32));
}

uint32 Render::IndexBuffer::GetClassSize() const
{
  return sizeof(IndexBuffer);
}
