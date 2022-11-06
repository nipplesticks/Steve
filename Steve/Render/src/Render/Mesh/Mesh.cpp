#include "pch.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Render/Mesh/Mesh.h"
#include "Render/Texture/TextureHandler.h"

using namespace Render;

static DM::Vec4f AssimpToDM(const aiVector3D& vec, float w = 1.0f)
{
  return DM::Vec4f(vec.x, vec.y, vec.z, w);
}
static DM::Vec4f AssimpToDM(const aiColor4D& vec)
{
  return DM::Vec4f(vec.r, vec.g, vec.b, vec.a);
}

uint64 Mesh::GetVertexBufferSize() const
{
  return myVertexBuffer.GetBufferSize();
}

const uint64& Mesh::GetVertexSize() const
{
  return myVertexSize;
}

uint64 Mesh::GetIndexBufferSize() const
{
  return myIndexBuffer.GetBufferSize();
}

void Mesh::LoadFromFile(const std::string& path, const std::string& meshName, bool flipWindingOrder)
{
  Assimp::Importer importer;
  const aiScene*   scene = importer.ReadFile(
      path.c_str(),
      aiProcess_Triangulate | (aiProcess_FlipWindingOrder * flipWindingOrder) |
          aiProcess_GenSmoothNormals | aiProcess_ForceGenNormals | aiProcess_PreTransformVertices |
          aiProcess_SortByPType | aiProcess_RemoveRedundantMaterials | aiProcess_GenUVCoords |
          aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_MakeLeftHanded);

  ASSERT_STR(!(!scene || !scene->HasMeshes()), "Failed to load %s\n", path.c_str());

  free(myVertices);

  uint64 vertexOffset = 0;
  uint64 indexOffset  = 0;

  bool vertexTypeFound = false;
  bool isVertexEx      = false;

  std::vector<VertexEx> vertEx;
  std::vector<Vertex>   vert;

  if (scene->mMeshes[0]->mVertices && scene->mMeshes[0]->mNormals &&
      scene->mMeshes[0]->mTextureCoords[0] && scene->mMeshes[0]->mTangents &&
      scene->mMeshes[0]->mBitangents)
  {
    myVertexSize = sizeof(VertexEx);
    isVertexEx   = true;
  }
  else if (scene->mMeshes[0]->mVertices && scene->mMeshes[0]->mNormals &&
           scene->mMeshes[0]->mTextureCoords[0])
  {
    myVertexSize = sizeof(Vertex);
  }
  else
  {
    ASSERT_STR(false, "Unsupporet mesh: %s\n", path);
  }

  size_t delimiter = path.find_last_of('/');

  std::string sourcePath = path.substr(0, delimiter + 1);

  for (uint32 i = 0; i < scene->mNumMeshes; i++)
  {
    uint64 numVerts = scene->mMeshes[i]->mNumVertices;
    aiMaterial* mat_p = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
    for (uint32 j = 0; j < mat_p->GetTextureCount(aiTextureType_DIFFUSE); j++)
    {
      aiString relativePathToTexture;
      if (mat_p->GetTexture(aiTextureType_DIFFUSE, j, &relativePathToTexture) == aiReturn_SUCCESS)
      {
        std::string pathToTexture = sourcePath + std::string(relativePathToTexture.C_Str());
        std::string texName       = meshName + "_diffuse_" + std::to_string(j);
        TextureHandler::LoadTextureFromFile(pathToTexture, texName);
        myTexturesMap.push_back(texName);
      }
    }
    for (uint32 j = 0; j < mat_p->GetTextureCount(aiTextureType_NORMALS); j++)
    {
      aiString relativePathToTexture;
      if (mat_p->GetTexture(aiTextureType_NORMALS, j, &relativePathToTexture) == aiReturn_SUCCESS)
      {
        std::string pathToTexture = sourcePath + std::string(relativePathToTexture.C_Str());
        std::string texName       = meshName + "_bump_" + std::to_string(j);
        TextureHandler::LoadTextureFromFile(pathToTexture, texName);
        myTexturesMap.push_back(texName);
      }
    }
    
    if (isVertexEx)
      vertEx.resize(vertEx.size() + numVerts);
    else
      vert.resize(vert.size() + numVerts);

    for (uint32 j = 0; j < numVerts; j++)
    {
      if (isVertexEx)
      {
        if (scene->mMeshes[i]->mVertices)
          vertEx[vertexOffset + j].position = AssimpToDM(scene->mMeshes[i]->mVertices[j]);
        if (scene->mMeshes[i]->mNormals)
          vertEx[vertexOffset + j].normal = AssimpToDM(scene->mMeshes[i]->mNormals[j], 0.0f);
        if (scene->mMeshes[i]->mTextureCoords[0])
          vertEx[vertexOffset + j].uv = AssimpToDM(scene->mMeshes[i]->mTextureCoords[0][j]);
        if (scene->mMeshes[i]->mTangents)
          vertEx[vertexOffset + j].tangent = AssimpToDM(scene->mMeshes[i]->mTangents[j]);
        if (scene->mMeshes[i]->mBitangents)
          vertEx[vertexOffset + j].bitangent = AssimpToDM(scene->mMeshes[i]->mBitangents[j]);
      }
      else
      {
        if (scene->mMeshes[i]->mVertices)
          vert[vertexOffset + j].position = AssimpToDM(scene->mMeshes[i]->mVertices[j]);
        if (scene->mMeshes[i]->mNormals)
          vert[vertexOffset + j].normal = AssimpToDM(scene->mMeshes[i]->mNormals[j], 0.0f);
        if (scene->mMeshes[i]->mTextureCoords[0])
          vert[vertexOffset + j].uv = AssimpToDM(scene->mMeshes[i]->mTextureCoords[0][j]);
      }
    }
    uint64 numIndices = 0;
    for (uint64 j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
      numIndices += scene->mMeshes[i]->mFaces[j].mNumIndices;
    myIndices.resize(myIndices.size() + numIndices);
    uint64 it = 0;
    for (uint64 j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
    {
      for (uint64 k = 0; k < scene->mMeshes[i]->mFaces[j].mNumIndices; k++)
      {
        myIndices[indexOffset + it++] = (uint32)scene->mMeshes[i]->mFaces[j].mIndices[k] + indexOffset;
      }
    }
    indexOffset += numIndices;
    vertexOffset += numVerts;
  }
  importer.FreeScene();

  void* vertices = nullptr;
  if (isVertexEx)
  {
    myNumVertices = (uint64)vertEx.size();
    vertices      = vertEx.data();
  }
  else
  {
    myNumVertices = (uint64)vert.size();
    vertices      = vert.data();
  }

  myNumIndices = (uint64)myIndices.size();
  myVertices = malloc(myNumVertices * myVertexSize);
  if (myVertices)
    memcpy(myVertices, vertices, myNumVertices * myVertexSize);
}

void Mesh::SetVertices(void*                      vertices,
                       const std::vector<uint32>& indices,
                       uint64                     vertexCount,
                       uint64                     vertexSize)
{
  myIndices = indices;
  memcpy(myVertices, vertices, vertexSize * vertexCount);
}

void Mesh::CreateBuffers(const std::string& name, bool deleteCpuData)
{
  myIndexBuffer.Create(name + "_IB", (uint32)myNumIndices);
  myVertexBuffer.Create(name + "_VB", (uint32)myVertexSize, (uint32)myNumVertices);

  myIndexBuffer.Update(myIndices.data());
  myVertexBuffer.Update(myVertices);

  if (deleteCpuData)
  {
    myIndices.clear();
    free(myVertices);
    myVertices = nullptr;
  }
}

IndexBuffer* Mesh::GetIndexBuffer() const
{
  return (IndexBuffer*)&myIndexBuffer;
}

VertexBuffer* Mesh::GetVertexBuffer() const
{
  return (VertexBuffer*)&myVertexBuffer;
}

const uint64& Mesh::GetNumberOfVertices() const
{
  return myNumVertices;
}

const uint64& Mesh::GetNumberOfIndices() const
{
  return myNumIndices;
}

void* Mesh::GetRawVertices()
{
  return myVertices;
}

uint32* Mesh::GetRawIndices()
{
  return myIndices.data();
}

std::vector<Resource*> Render::Mesh::GetTextures() const
{
  std::vector<Resource*> tex(myTexturesMap.size());
  for (size_t i = 0; i < myTexturesMap.size(); i++)
    tex[i] = TextureHandler::GetTexture(myTexturesMap[i]);
  return tex;
}
