#include "pch.h"
#include "Render/Resource/ConstantBuffer.h"

using namespace Render;

void ConstantBuffer::Create(const std::string& name, uint32 size)
{
  Init(Resource_Type::ConstantBuffer, name, size);
}
