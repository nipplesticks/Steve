#include "Mesh.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Mesh::Mesh() { }

Mesh::~Mesh() { }

DirectX::XMFLOAT4A AssimpToXmFloat4A(const aiVector3D& vec, float w = 1.0f)
{
  return DirectX::XMFLOAT4A(vec.x, vec.y, vec.z, w);
}
DirectX::XMFLOAT4A AssimpToXmFloat4A(const aiColor4D& vec)
{
  return DirectX::XMFLOAT4A(vec.r, vec.g, vec.b, vec.a);
}
DirectX::XMFLOAT2A AssimpToXmFloat2A(const aiVector3D& vec)
{
  return DirectX::XMFLOAT2A(vec.x, vec.y);
}

bool Mesh::LoadMesh(const std::string& path)
{
  Assimp::Importer importer;
  const aiScene*   scene = importer.ReadFile(
    path.c_str(),
    aiProcess_CalcTangentSpace |
    aiProcess_Triangulate |
    aiProcess_SortByPType);

  if (!scene || !scene->HasMeshes())
  {
    std::cout << "Failed to load " << path << std::endl;
    return false;
  }

  uint numVertices = 0u;

  for (uint i = 0; i < scene->mNumMeshes; i++)
    numVertices += scene->mMeshes[i]->mNumVertices;

  myMesh.resize(numVertices);
  uint counter = 0;

  for (uint i = 0; i < scene->mNumMeshes; i++)
    for (uint j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
    {
      myMesh[counter].position = AssimpToXmFloat4A(scene->mMeshes[i]->mVertices[j]);
      myMesh[counter].color    = AssimpToXmFloat4A(scene->mMeshes[i]->mColors[0][j]);
      myMesh[counter].uv       = AssimpToXmFloat2A(scene->mMeshes[i]->mTextureCoords[0][j]);
    }

}

void Mesh::SetMesh(const std::vector<Vertex>& vertices) { }

Vertex* Mesh::GetRawVertices()
{
  return myMesh.data();
}

const std::vector<Vertex>& Mesh::GetVertices() const
{
  return myMesh;
}

uint Mesh::GetNumberOfVertices() const
{
  return myMesh.size();
}

const D3D12_VERTEX_BUFFER_VIEW& Mesh::GetVBV() const
{
  return myVertexBufferView;
}
