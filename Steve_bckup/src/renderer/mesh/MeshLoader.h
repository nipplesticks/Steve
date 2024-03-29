#pragma once
#include "Mesh.h"
#include <unordered_map>

class MeshLoader
{
private:
  MeshLoader()  = default;
  ~MeshLoader() = default;

public:
  static void
  LoadMesh(const std::string& path, const std::string& name, bool flipWindingOrder = false);
  static Mesh* GetMesh(const std::string& name);

private:
  static std::unordered_map<std::string, Mesh> myMeshes;
};