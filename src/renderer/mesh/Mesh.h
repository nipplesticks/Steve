#pragma once
#define NOMINMAX
#include "../../utility/Typedef.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexBuffer.h"
#include "Vertex.h"
#include <string>
#include <vector>

class Mesh
{
public:
  Mesh()  = default;
  ~Mesh() = default;

  uint GetVertexBufferByteSize();
  uint GetSingleVertexByteSize();
  uint GetIndexBufferByteSize();

  bool LoadFromFile(const std::string& path, bool flipWindingOrder = false);

  void SetMesh(const std::vector<Vertex>& vertices, VertexType vertexType);
  void SetMesh(const std::vector<Vertex>& vertices,
               const std::vector<uint>&   indices,
               VertexType                 vertexType);

  void CreateBuffers(bool deleteCpuData = false);

  IndexBuffer*  GetIndexBuffer() const;
  VertexBuffer* GetVertexBuffer() const;

  uint       GetNumberOfVertices() const;
  uint       GetNumberOfIndices() const;
  VertexType GetVertexType() const;
  void*      GetRawVertices();
  uint*      GetRawIndices();

private:
  VertexType                       myVertexType = VertexType::NumberOfVertexTypes;
  std::vector<uint>                myIndices;
  VertexBuffer                     myVertexBuffer;
  IndexBuffer                      myIndexBuffer;
  std::vector<Vertex_Basic>        myBasicVertices;
  std::vector<Vertex_With_Tangent> myTangentVertices;
  uint                             myNumberOfVertices = 0;
  uint                             myNumberOfIndices = 0;
  bool                             myCpuDataDeleted = false;

};