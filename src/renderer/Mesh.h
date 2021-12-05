#pragma once

#include "../utility/Typedef.h"
#include "Vertex.h"
#include <vector>
#include <string>

class Mesh
{
public:
  Mesh();
  ~Mesh();

  uint GetByteSize() const;

  bool                       LoadMesh(const std::string& path);
  void                       SetMesh(const std::vector<Vertex>& vertices);
  Vertex*                    GetRawVertices();
  const std::vector<Vertex>& GetVertices() const;
  uint                       GetNumberOfVertices() const;

private:
  std::vector<Vertex> myMesh;
};