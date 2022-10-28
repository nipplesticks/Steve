#pragma once
#include <Common/Typedef.h>
#include "Vertex.h"
#include <vector>
#include "Render/Resource/IndexBuffer.h"
#include "Render/Resource/VertexBuffer.h"

namespace Render
{
  class Mesh
  {
  public:
    uint64        GetVertexBufferSize() const;
    const uint64& GetVertexSize() const;
    uint64        GetIndexBufferSize() const;

    void LoadFromFile(const std::string& path, bool flipWindingOrder = false);
    void SetVertices(void*                      vertices,
                     const std::vector<uint32>& indices,
                     uint64                     vertexCount,
                     uint64                     vertexSize);

    void CreateBuffers(const std::string& name, bool deleteCpuData = false);

    IndexBuffer*  GetIndexBuffer() const;
    VertexBuffer* GetVertexBuffer() const;

    const uint64& GetNumberOfVertices() const;
    const uint64& GetNumberOfIndices() const;
    void*         GetRawVertices();
    uint32*       GetRawIndices();

  private:
    uint64              myNumVertices = 0;
    uint64              myVertexSize  = 0;
    uint64              myNumIndices  = 0;
    std::vector<uint32> myIndices;

    VertexBuffer        myVertexBuffer;
    IndexBuffer         myIndexBuffer;
    void*               myVertices = nullptr;
  };
} // namespace Render
