#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

Mesh::Mesh() { }

Mesh::~Mesh() { }

uint Mesh::GetByteSize() const
{
  return sizeof(myMesh[0]) * myMesh.size();
}

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
  const aiScene*   scene =
      importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipWindingOrder);

  if (!scene || !scene->HasMeshes())
  {
    std::cout << "Failed to load " << path << "\n";
    return false;
  }

  uint numVertices = 0u;

  for (uint i = 0; i < scene->mNumMeshes; i++)
  {
    for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
    {
      numVertices += scene->mMeshes[i]->mFaces[j].mNumIndices;
    }
  }
  myMesh.resize(numVertices);
  uint counter = 0u;
  Vertex v       = {};
  v.color        = DirectX::XMFLOAT4A(1.0f, 1.0f, 1.0f, 1.0f);
  for (uint i = 0; i < scene->mNumMeshes; i++)
  {
    for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
    {
      for (uint k = 0; k < scene->mMeshes[i]->mFaces[j].mNumIndices; k++)
      {
        uint vertIdx             = scene->mMeshes[i]->mFaces[j].mIndices[k];
        myMesh[counter] = v;
        if (scene->mMeshes[i]->mVertices)
        {
          myMesh[counter].position = AssimpToXmFloat4A(scene->mMeshes[i]->mVertices[vertIdx]);
        }
        if (scene->mMeshes[i]->mColors[0])
          myMesh[counter].color = AssimpToXmFloat4A(scene->mMeshes[i]->mColors[0][vertIdx]);
        if (scene->mMeshes[i]->mNormals)
          myMesh[counter].normal = AssimpToXmFloat4A(scene->mMeshes[i]->mNormals[vertIdx], 0.0f);
        if (scene->mMeshes[i]->mTextureCoords[0])
          myMesh[counter].uv = AssimpToXmFloat4A(scene->mMeshes[i]->mTextureCoords[0][vertIdx]);

        counter++;
      }
    }
  }
}

void Mesh::SetMesh(const std::vector<Vertex>& vertices)
{
  myMesh = vertices;
}

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
