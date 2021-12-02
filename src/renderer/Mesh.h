#pragma once

#include "Renderer.h"
#include <vector>

class Mesh
{
public:
  Mesh();
  ~Mesh();

  bool                            LoadMesh(const std::string& path);
  void                            SetMesh(const std::vector<Vertex>& vertices);
  Vertex*                         GetRawVertices();
  const std::vector<Vertex>&      GetVertices() const;
  uint                            GetNumberOfVertices() const;
  const D3D12_VERTEX_BUFFER_VIEW& GetVBV() const;

private:
  ID3D12Resource*          myVerttexBuffer    = nullptr;
  D3D12_VERTEX_BUFFER_VIEW myVertexBufferView = {};
  std::vector<Vertex>      myMesh;
};