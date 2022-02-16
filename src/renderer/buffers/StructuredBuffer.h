#pragma once

#pragma once

#include "Resource.h"

class StructuredBuffer : public Resource
{
public:
  StructuredBuffer() = default;
  ~StructuredBuffer() = default;
  void Create(uint sizeOfElement, uint numberOfElements)
  {
    Init(Resource_Type::StructuredBuffer, sizeOfElement * numberOfElements, DXGI_FORMAT_UNKNOWN, 1, 1, numberOfElements);
  }
};