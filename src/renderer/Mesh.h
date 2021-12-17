#pragma once

#include "../utility/Typedef.h"
#include "TextureLoader.h"
#include "Vertex.h"
#include <string>
#include <vector>

class Mesh
{
public:
  Mesh();
  ~Mesh();

  uint GetTotalByteSizeOfVertices() const;
  uint GetByteSizeOfVertices(uint idx) const;

  bool LoadMesh(const std::string& path);
  void SetMesh(std::vector<Vertex>&& vertices);
  void SetMesh(std::vector<std::vector<Vertex>>&& vertices);
  void SetIndices(std::vector<uint>&& indices);
  void SetIndices(std::vector<std::vector<uint>>&& indices);
  void SetImages(TextureLoader::Image&& image);
  void SetImages(std::vector<TextureLoader::Image>&& images);

  uint GetMeshesCount() const;

  Vertex*                                 GetRawVertices(uint idx);
  const std::vector<Vertex>&              GetVertices(uint idx) const;
  uint                                    GetNumberOfVertices(uint idx) const;
  uint                                    GetTotalNumberOfVertices() const;
  const std::vector<std::vector<Vertex>>& GetAllVertices() const;

  uint*                                 GetRawIndices(uint idx);
  const std::vector<uint>&              GetIndices(uint idx) const;
  uint                                  GetNumberOfIndices(uint idx) const;
  uint                                  GetTotalNumberOfIndices() const;
  const std::vector<std::vector<uint>>& GetAllIndices() const;

  uint8*                                   GetRawImage(uint idx, uint* width, uint* height);
  const TextureLoader::Image&              GetImage(uint idx) const;
  const std::vector<TextureLoader::Image>& GetAllImages() const;

private:
  std::vector<std::vector<Vertex>>  myMesh;
  std::vector<std::vector<uint>>    myIndices;
  std::vector<TextureLoader::Image> myImages;
};