#include "pch.h"
#include "Render/Resource/StructuredBuffer.h"

using namespace Render;

void StructuredBuffer::Create(const std::string& name, uint32 elementSize, uint32 numElements)
{
  Init(Resource_Type::StructuredBuffer,
       name,
       elementSize * numElements,
       DXGI_FORMAT_UNKNOWN,
       1,
       1,
       numElements);
}

uint32 Render::StructuredBuffer::GetClassSize() const
{
  return sizeof(StructuredBuffer);
}
