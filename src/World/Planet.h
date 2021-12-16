#pragma once
#include "../renderer/Mesh.h"
#include "../utility/DMath.h"
class Planet
{
public:
  Planet();
  ~Planet();

  void Create(float size, uint div);
  const Mesh& GetMesh() const;

private:
  Mesh myMesh;

};