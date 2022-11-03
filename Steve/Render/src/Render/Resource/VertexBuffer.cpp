#include "pch.h"
#include "Render/Resource/VertexBuffer.h"

using namespace Render;

void VertexBuffer::Create(const std::string& name, uint32 vertexSize, uint32 numVertices)
{
  Init(Resource_Type::VertexBuffer,
       name,
       vertexSize * numVertices,
       DXGI_FORMAT_UNKNOWN,
       1,
       1,
       numVertices);
}

uint32 Render::VertexBuffer::GetClassSize() const
{
  return sizeof(VertexBuffer);
}
