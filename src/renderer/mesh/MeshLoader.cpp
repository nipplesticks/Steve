#include "MeshLoader.h"

std::unordered_map<std::string, Mesh> MeshLoader::myMeshes;

void MeshLoader::LoadMesh(const std::string& path, const std::string& name, bool flipWindingOrder)
{
  if (myMeshes[name].LoadFromFile(path, flipWindingOrder))
    myMeshes[name].CreateBuffers();
}

Mesh* MeshLoader::GetMesh(const std::string& name)
{
  return &myMeshes[name];
}
