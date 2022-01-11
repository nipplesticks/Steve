#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

Mesh::Mesh() { }

Mesh::~Mesh() { }

uint Mesh::GetTotalByteSizeOfVertices() const
{
  return sizeof(myMesh[0][0]) * GetTotalNumberOfVertices();
}

uint Mesh::GetByteSizeOfVertices(uint idx) const
{
  return sizeof(myMesh[0][0]) * myMesh[idx].size();
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

bool Mesh::LoadMesh(const std::string& path, bool flipWindingOrder)
{
  Assimp::Importer importer;
  const aiScene*   scene = importer.ReadFile(
      path.c_str(),
      aiProcess_Triangulate | (aiProcess_FlipWindingOrder * flipWindingOrder) | aiProcess_GenSmoothNormals |
          aiProcess_ForceGenNormals | aiProcess_PreTransformVertices| aiProcess_SortByPType |
          aiProcess_RemoveRedundantMaterials | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes);

  /*const aiScene* scene = importer.ReadFile(
      path.c_str(),
      aiProcess_Triangulate | aiProcess_FlipWindingOrder | aiProcess_GenSmoothNormals | aiProcess_ForceGenNormals);*/

  if (!scene || !scene->HasMeshes())
  {
    std::cout << "Failed to load " << path << "\n";
    return false;
  }

  //if (scene->HasMaterials())
  //{
  //  for (unsigned int i = 0; i < scene->mNumMaterials; i++)
  //  {
  //    const aiMaterial* material = scene->mMaterials[i];
  //    aiString          texturePath;

  //    unsigned int numTextures = material->GetTextureCount(aiTextureType_DIFFUSE); // always 0

  //    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
  //        material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
  //    {
  //      std::cout << texturePath.C_Str() << std::endl;
  //    }
  //  }
  //}

  uint numMeshes = scene->mNumMeshes;

  myMesh.resize(numMeshes);
  myIndices.resize(numMeshes);
  Vertex v        = {};
  v.color         = DirectX::XMFLOAT4A(1.0f, 1.0f, 1.0f, 1.0f);

  for (uint i = 0; i < scene->mNumMeshes; i++)
  {
    uint numVerts = scene->mMeshes[i]->mNumVertices;
    myMesh[i].resize(numVerts);
    for (uint j = 0; j < numVerts; j++)
    {
      myMesh[i][j] = v;
      if (scene->mMeshes[i]->mVertices)
        myMesh[i][j].position = AssimpToXmFloat4A(scene->mMeshes[i]->mVertices[j]);
      if (scene->mMeshes[i]->mColors[0])
        myMesh[i][j].color = AssimpToXmFloat4A(scene->mMeshes[i]->mColors[0][j]);
      if (scene->mMeshes[i]->mNormals)
        myMesh[i][j].normal = AssimpToXmFloat4A(scene->mMeshes[i]->mNormals[j], 0.0f);
      if (scene->mMeshes[i]->mTextureCoords[0])
        myMesh[i][j].uv = AssimpToXmFloat4A(scene->mMeshes[i]->mTextureCoords[0][j]);
    }
    uint numIndices = 0;
    for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
      numIndices += scene->mMeshes[i]->mFaces[j].mNumIndices;

    myIndices[i].resize(numIndices);

    uint offset = 0;
    for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
    {
      for (uint k = 0; k < scene->mMeshes[i]->mFaces[j].mNumIndices; k++)
      {
        myIndices[i][offset++] = scene->mMeshes[i]->mFaces[j].mIndices[k];
      }
    }
  }

  importer.FreeScene();

  return true;
}

void Mesh::SetMesh(std::vector<Vertex>&& vertices)
{
  myMesh.clear();
  myMesh.push_back(std::move(vertices));
}

void Mesh::SetMesh(std::vector<std::vector<Vertex>>&& vertices)
{
  myMesh = vertices;
}

void Mesh::SetIndices(std::vector<uint>&& indices)
{
  myIndices.clear();
  myIndices.push_back(std::move(indices));
}

void Mesh::SetIndices(std::vector<std::vector<uint>>&& indices)
{
  myIndices = indices;
}

void Mesh::SetImages(TextureLoader::Image&& image)
{
  myImages.clear();
  myImages.push_back(std::move(image));
}


void Mesh::SetImages(std::vector<TextureLoader::Image>&& images)
{
  myImages = images;
}

uint Mesh::GetMeshesCount() const
{
  return myMesh.size();
}

Vertex* Mesh::GetRawVertices(uint idx)
{
  return myMesh[idx].data();
}

const std::vector<Vertex>& Mesh::GetVertices(uint idx) const
{
  return myMesh[idx];
}

uint Mesh::GetNumberOfVertices(uint idx) const
{
  return myMesh[idx].size();
}

uint Mesh::GetTotalNumberOfVertices() const
{
  uint nrVerts = 0;
  for (auto & vb : myMesh)
    nrVerts += vb.size();
  return nrVerts;
}

const std::vector<std::vector<Vertex>>& Mesh::GetAllVertices() const
{
  return myMesh;
}

uint* Mesh::GetRawIndices(uint idx)
{
  return myIndices[idx].data();
}

const std::vector<uint>& Mesh::GetIndices(uint idx) const
{
  return myIndices[idx];
}

uint Mesh::GetNumberOfIndices(uint idx) const
{
  return myIndices[idx].size();
}

uint Mesh::GetTotalNumberOfIndices() const
{
  uint nrIndices = 0;
  for (auto& ib : myIndices)
    nrIndices += ib.size();
  return nrIndices;
}

const std::vector<std::vector<uint>>& Mesh::GetAllIndices() const
{
  return myIndices;
}

uint8* Mesh::GetRawImage(uint idx, uint* width, uint* height)
{
  *width = myImages[idx].width;
  *height = myImages[idx].height;
  return myImages[idx].pixels.data();
}

const TextureLoader::Image& Mesh::GetImage(uint idx) const
{
  return myImages[idx];
}

const std::vector<TextureLoader::Image>& Mesh::GetAllImages() const
{
  return myImages;
}
