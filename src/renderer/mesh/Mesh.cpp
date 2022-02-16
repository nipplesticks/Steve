#include "Mesh.h"
#include "../../utility/UtilityFuncs.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
static DirectX::XMFLOAT4A AssimpToXmFloat4A(const aiVector3D& vec, float w = 1.0f)
{
  return DirectX::XMFLOAT4A(vec.x, vec.y, vec.z, w);
}

static DirectX::XMFLOAT4A AssimpToXmFloat4A(const aiColor4D& vec)
{
  return DirectX::XMFLOAT4A(vec.r, vec.g, vec.b, vec.a);
}

static DirectX::XMFLOAT2A AssimpToXmFloat2A(const aiVector3D& vec)
{
  return DirectX::XMFLOAT2A(vec.x, vec.y);
}

uint Mesh::GetVertexBufferByteSize()
{
  return GetSingleVertexByteSize() * GetNumberOfVertices();
}

uint Mesh::GetSingleVertexByteSize()
{
  switch (myVertexType)
  {
  case VertexType::VertexBasic:
    return sizeof(Vertex_Basic);
    break;
  case VertexType::VertexTangent:
    return sizeof(Vertex_With_Tangent);
    break;
  default:
    ASSERT_STR(false, "Unsupported Vertex Type");
    break;
  }
  return UINT_MAX;
}

uint Mesh::GetIndexBufferByteSize()
{
  return sizeof(uint) * (uint)myIndices.size();
}

bool Mesh::LoadFromFile(const std::string& path, bool flipWindingOrder)
{
  Assimp::Importer importer;
  const aiScene*   scene = importer.ReadFile(
      path.c_str(),
      aiProcess_Triangulate | (aiProcess_FlipWindingOrder * flipWindingOrder) |
          aiProcess_GenSmoothNormals | aiProcess_ForceGenNormals | aiProcess_PreTransformVertices |
          aiProcess_SortByPType | aiProcess_RemoveRedundantMaterials | aiProcess_GenUVCoords |
          aiProcess_OptimizeMeshes);

  ASSERT_STR(!(!scene || !scene->HasMeshes()), "Failed to load %s\n", path);

  uint vertexOffset = 0;
  uint indexOffset  = 0;

  bool vertexTypeFound = false;

  for (uint i = 0; i < scene->mNumMeshes; i++)
  {
    uint numVerts = scene->mMeshes[i]->mNumVertices;
    if (!vertexTypeFound)
    {
      if (scene->mMeshes[i]->mVertices && scene->mMeshes[i]->mNormals &&
          scene->mMeshes[i]->mTextureCoords[0] && scene->mMeshes[i]->mTangents &&
          scene->mMeshes[i]->mBitangents)
      {
        myVertexType = VertexType::VertexTangent;
      }
      else if (scene->mMeshes[i]->mVertices && scene->mMeshes[i]->mNormals &&
               scene->mMeshes[i]->mTextureCoords[0])
      {
        myVertexType = VertexType::VertexBasic;
      }
      else
      {
        ASSERT_STR(false, "Unsupporet mesh: %s\n", path);
      }
    }
    if (myVertexType == VertexType::VertexBasic)
      myVertices.basicVertices.resize(myVertices.basicVertices.size() + numVerts);
    else if (myVertexType == VertexType::VertexTangent)
      myVertices.tangentVertices.resize(myVertices.tangentVertices.size() + numVerts);

    if (myVertexType == VertexType::VertexBasic)
    {
      for (uint j = 0; j < numVerts; j++)
      {
        if (scene->mMeshes[i]->mVertices)
          myVertices.basicVertices[vertexOffset + j].position =
              AssimpToXmFloat4A(scene->mMeshes[i]->mVertices[j]);
        if (scene->mMeshes[i]->mNormals)
          myVertices.basicVertices[vertexOffset + j].normal =
              AssimpToXmFloat4A(scene->mMeshes[i]->mNormals[j], 0.0f);
        if (scene->mMeshes[i]->mTextureCoords[0])
          myVertices.basicVertices[vertexOffset + j].uv =
              AssimpToXmFloat2A(scene->mMeshes[i]->mTextureCoords[0][j]);
      }
    }
    else if (myVertexType == VertexType::VertexTangent)
    {
      for (uint j = 0; j < numVerts; j++)
      {
        if (scene->mMeshes[i]->mVertices)
          myVertices.tangentVertices[vertexOffset + j].vertexBasic.position =
              AssimpToXmFloat4A(scene->mMeshes[i]->mVertices[j]);
        if (scene->mMeshes[i]->mNormals)
          myVertices.tangentVertices[vertexOffset + j].vertexBasic.normal =
              AssimpToXmFloat4A(scene->mMeshes[i]->mNormals[j], 0.0f);
        if (scene->mMeshes[i]->mTextureCoords[0])
          myVertices.tangentVertices[vertexOffset + j].vertexBasic.uv =
              AssimpToXmFloat2A(scene->mMeshes[i]->mTextureCoords[0][j]);
        if (scene->mMeshes[i]->mTangents)
          myVertices.tangentVertices[vertexOffset + j].tangent =
              AssimpToXmFloat4A(scene->mMeshes[i]->mTangents[j]);
        if (scene->mMeshes[i]->mBitangents)
          myVertices.tangentVertices[vertexOffset + j].bitangent =
              AssimpToXmFloat4A(scene->mMeshes[i]->mBitangents[j]);
      }
    }

    uint numIndices = 0;
    for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
      numIndices += scene->mMeshes[i]->mFaces[j].mNumIndices;
    myIndices.resize(myIndices.size() + numIndices);
    uint it = 0;
    for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
    {
      for (uint k = 0; k < scene->mMeshes[i]->mFaces[j].mNumIndices; k++)
      {
        myIndices[indexOffset + it++] = scene->mMeshes[i]->mFaces[j].mIndices[k] + indexOffset;
      }
    }
    indexOffset += numIndices;
    vertexOffset += numVerts;
  }

  importer.FreeScene();

  return true;
}

void Mesh::SetMesh(const std::vector<Vertex>& vertices, VertexType vertexType)
{
  myVertexType = vertexType;

  if (myVertexType == VertexType::VertexBasic)
  {
    myVertices.basicVertices.resize(vertices.size());
    myIndices.resize(vertices.size());
    for (uint i = 0; i < (uint)vertices.size(); i++)
    {
      myVertices.basicVertices[i] = vertices[i].vertexBasic;
      myIndices[i]                = i;
    }
  }
  else if (myVertexType == VertexType::VertexTangent)
  {
    myVertices.tangentVertices.resize(vertices.size());
    myIndices.resize(vertices.size());
    for (uint i = 0; i < (uint)vertices.size(); i++)
    {
      myVertices.tangentVertices[i] = vertices[i].vertexTangent;
      myIndices[i]                  = i;
    }
  }
}

void Mesh::SetMesh(const std::vector<Vertex>& vertices,
                   const std::vector<uint>&   indices,
                   VertexType                 vertexType)
{
  myIndices = indices;
  myVertexType = vertexType;

  if (myVertexType == VertexType::VertexBasic)
  {
    myVertices.basicVertices.resize(vertices.size());
    for (uint i = 0; i < (uint)vertices.size(); i++)
      myVertices.basicVertices[i] = vertices[i].vertexBasic;
  }
  else if (myVertexType == VertexType::VertexTangent)
  {
    myVertices.tangentVertices.resize(vertices.size());
    myIndices.resize(vertices.size());
    for (uint i = 0; i < (uint)vertices.size(); i++)
      myVertices.tangentVertices[i] = vertices[i].vertexTangent;
  }

}

void Mesh::CreateBuffers()
{
  myIndexBuffer.Create(GetNumberOfIndices());
  myVertexBuffer.Create(GetSingleVertexByteSize(), GetNumberOfVertices());
  myIndexBuffer.UpdateNow(myIndices.data(), D3D12_RESOURCE_STATE_GENERIC_READ);
  myVertexBuffer.UpdateNow(GetRawVertices(), D3D12_RESOURCE_STATE_GENERIC_READ);
}

IndexBuffer* Mesh::GetIndexBuffer() const
{
  return (IndexBuffer*)&myIndexBuffer;
}

VertexBuffer* Mesh::GetVertexBuffer() const
{
  return (VertexBuffer*)&myVertexBuffer;
}

uint Mesh::GetNumberOfVertices() const
{
  switch (myVertexType)
  {
  case VertexType::VertexBasic:
    return myVertices.basicVertices.size();
  case VertexType::VertexTangent:
    return myVertices.tangentVertices.size();
  default:
    ASSERT_STR(false, "Unsupported Vertex Type");
    break;
  }

  return UINT_MAX;
}

uint Mesh::GetNumberOfIndices() const
{
  return myIndices.size();
}

VertexType Mesh::GetVertexType() const
{
  return myVertexType;
}

void* Mesh::GetRawVertices() const
{
  switch (myVertexType)
  {
  case VertexType::VertexBasic:
    return (void*)myVertices.basicVertices.data();
    break;
  case VertexType::VertexTangent:
    return (void*)myVertices.tangentVertices.data();
  default:
    ASSERT_STR(false, "Unsupported Vertex Type");
    break;
  }
  return nullptr;
}

uint* Mesh::GetRawIndices() const
{
  return (uint*)myIndices.data();
}
