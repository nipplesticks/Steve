#pragma once
#include "../renderer/Mesh.h"
#include "../utility/DMath.h"

class Planet2
{
public:
  Planet2();
  ~Planet2();

  void        Create(float size, uint div, float uvTiles = 1.0f);
  const Mesh& GetMesh() const;

private:
  Mesh myMesh;
};