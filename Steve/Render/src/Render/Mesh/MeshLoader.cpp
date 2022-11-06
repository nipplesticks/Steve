#include "pch.h"
#include "Render/Mesh/MeshLoader.h"
#include <Common/SafeDelete.h>

using namespace Render;

std::unordered_map<std::string, Mesh*> MeshLoader::myMeshes;

MeshLoader::~MeshLoader()
{
  for (auto& e : myMeshes)
  {
    SafeDelete(&e.second);
  }
  myMeshes.clear();
}

void MeshLoader::LoadMesh(const std::string& path, const std::string& name, bool flipWindingOrder)
{
  myMeshes[name] = new Mesh;
  myMeshes[name]->LoadFromFile(path, name, flipWindingOrder);
  myMeshes[name]->CreateBuffers(name, true);
}

Mesh* MeshLoader::GetMesh(const std::string& name)
{
  return myMeshes[name];
}
