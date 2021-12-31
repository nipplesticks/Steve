#include "Planet3.h"
#include "../renderer/TextureLoader.h"
#include "../utility/Timer.h"
#include <iostream>
#include <map>
#include <math.h>

Planet3::Planet3() { }

Planet3::~Planet3() { }

void Planet3::Create(float size, uint div, float uvTiles)
{
  std::vector<std::vector<Triangle>>  triangles;
  std::vector<std::vector<DM::Vec3f>> points;

  std::vector<std::vector<uint>>   indices;
  std::vector<std::vector<Vertex>> vertices;

  _createIcosahedron(triangles, points);

  for (uint subDiv = 0; subDiv < div; subDiv++)
  {
    for (uint meshIdx = 0; meshIdx < triangles.size(); meshIdx++)
    {
      _subdevideIcosahedron(triangles[meshIdx], points[meshIdx]);
    }
  }

  indices.resize(20);
  vertices.resize(20);
  float PI = DirectX::XM_PI;
  uint _size = 0;
  uint  _size2 = 0;
  for (uint meshIdx = 0; meshIdx < triangles.size(); meshIdx++)
  {
    std::vector<Triangle>*  meshVec  = &triangles[meshIdx];
    std::vector<DM::Vec3f>* pointVec = &points[meshIdx];
    indices[meshIdx].resize(meshVec->size() * 3u);
    vertices[meshIdx].resize(pointVec->size());

    uint idx = 0;

    for (uint triangleIdx = 0; triangleIdx < meshVec->size(); triangleIdx++)
    {
      indices[meshIdx][idx++] = meshVec->at(triangleIdx).A;
      indices[meshIdx][idx++] = meshVec->at(triangleIdx).B;
      indices[meshIdx][idx++] = meshVec->at(triangleIdx).C;
      _size2 += 3;
    }
    for (uint vertexIdx = 0; vertexIdx < pointVec->size(); vertexIdx++)
    {
      Vertex* v   = &vertices[meshIdx][vertexIdx];
      v->color    = DirectX::XMFLOAT4A(1.0f, 1.0f, 1.0f, 1.0f);
      v->normal   = pointVec->at(vertexIdx).Normalize().AsXmFloat4AVector();
      v->position = pointVec->at(vertexIdx).Normalize().AsXmFloat4APoint();
      v->uv.x     = -1.0f * (0.5f + (std::atan2(v->position.z, v->position.x) / (2.0f * PI)));
      v->uv.y = 0.5f - (std::asin(v->position.y) / PI);
      _size++;
    }
  }
  std::cout << "nrOfVerts: " << _size << std::endl;
  std::cout << "nrOfIdx:" << _size2 << std::endl;

  myMesh.SetMesh(std::move(vertices));
  myMesh.SetIndices(std::move(indices));
  TextureLoader::Image shrek = TextureLoader::LoadImageData("assets/textures/testingFesting.jpg");
  myMesh.SetImages(std::move(shrek));
}

const Mesh& Planet3::GetMesh() const
{
  return myMesh;
}

void PushIndices(uint a, uint b, uint c, std::vector<uint>& indices)
{
  indices.push_back(a);
  indices.push_back(b);
  indices.push_back(c);
}

void Planet3::_createIcosahedron(std::vector<std::vector<Triangle>>&  triangles,
                                 std::vector<std::vector<DM::Vec3f>>& vertices)
{
  triangles.clear();
  triangles.resize(20);
  vertices.clear();
  vertices.resize(20);

  float phi = (1.0f + sqrt(5.0f)) * 0.5f; // Golder Ratio
  float a   = 1.0f;
  float b   = 1.0f / phi;

  std::vector<DM::Vec3f> _verts(12);
  std::vector<uint>      indices;

  uint vertIdx      = 0u;
  _verts[vertIdx++] = DM::Vec3f(0, b, -a);
  _verts[vertIdx++] = DM::Vec3f(b, a, 0);
  _verts[vertIdx++] = DM::Vec3f(-b, a, 0);
  _verts[vertIdx++] = DM::Vec3f(0, b, a);
  _verts[vertIdx++] = DM::Vec3f(0, -b, a);
  _verts[vertIdx++] = DM::Vec3f(-a, 0, b);
  _verts[vertIdx++] = DM::Vec3f(0, -b, -a);
  _verts[vertIdx++] = DM::Vec3f(a, 0, -b);
  _verts[vertIdx++] = DM::Vec3f(a, 0, b);
  _verts[vertIdx++] = DM::Vec3f(-a, 0, -b);
  _verts[vertIdx++] = DM::Vec3f(b, -a, 0);
  _verts[vertIdx++] = DM::Vec3f(-b, -a, 0);

  uint v1  = 0;
  uint v2  = 1;
  uint v3  = 2;
  uint v4  = 3;
  uint v5  = 4;
  uint v6  = 5;
  uint v7  = 6;
  uint v8  = 7;
  uint v9  = 8;
  uint v10 = 9;
  uint v11 = 10;
  uint v12 = 11;

  PushIndices(v2, v3, v1, indices);
  PushIndices(v3, v2, v4, indices);
  PushIndices(v5, v6, v4, indices);
  PushIndices(v9, v5, v4, indices);
  PushIndices(v7, v8, v1, indices);
  PushIndices(v10, v7, v1, indices);
  PushIndices(v11, v12, v5, indices);
  PushIndices(v12, v11, v7, indices);
  PushIndices(v6, v10, v3, indices);
  PushIndices(v10, v6, v12, indices);
  PushIndices(v8, v9, v2, indices);
  PushIndices(v9, v8, v11, indices);
  PushIndices(v6, v3, v4, indices);
  PushIndices(v2, v9, v4, indices);
  PushIndices(v3, v10, v1, indices);
  PushIndices(v8, v2, v1, indices);
  PushIndices(v10, v12, v7, indices);
  PushIndices(v11, v8, v7, indices);
  PushIndices(v12, v6, v5, indices);
  PushIndices(v9, v11, v5, indices);

  for (uint i = 0; i < 20; i++)
  {
    uint      idx = i * 3;
    DM::Vec3f a   = _verts[indices[idx]];
    DM::Vec3f b   = _verts[indices[idx + 1]];
    DM::Vec3f c   = _verts[indices[idx + 2]];
    triangles[i].push_back(Triangle(0, 1, 2));
    vertices[i].resize(3);
    vertices[i][0] = a;
    vertices[i][1] = b;
    vertices[i][2] = c;
  }
}

void Planet3::_subdevideIcosahedron(std::vector<Triangle>&  triangles,
                                    std::vector<DM::Vec3f>& vertices)
{
  uint numTri  = triangles.size();
  uint lastTri = numTri;
  triangles.resize(numTri + numTri * 3u);
  uint numVert = vertices.size();
  vertices.resize(numVert + numTri * 3u);

  for (uint triIdx = 0; triIdx < numTri; triIdx++)
  {
    DM::Vec3f a = vertices[triangles[triIdx].A];
    DM::Vec3f b = vertices[triangles[triIdx].B];
    DM::Vec3f c = vertices[triangles[triIdx].C];

    DM::Vec3f ab = a + (b - a) * 0.5f;
    DM::Vec3f bc = b + (c - b) * 0.5f;
    DM::Vec3f ca = c + (a - c) * 0.5f;

    uint abIdx = numVert;
    uint bcIdx = abIdx + 1;
    uint caIdx = bcIdx + 1;

    vertices[abIdx]      = ab;
    vertices[bcIdx]      = bc;
    vertices[caIdx]      = ca;
    numVert += 3;

    Triangle temp = triangles[triIdx];

    triangles[triIdx]    = Triangle(temp.A, abIdx, caIdx);
    triangles[lastTri++] = Triangle(temp.B, bcIdx, abIdx);
    triangles[lastTri++] = Triangle(temp.C, caIdx, bcIdx);
    triangles[lastTri++] = Triangle(caIdx, abIdx, bcIdx);
  }
}

//void Planet3::_optimizeMesh(std::vector<std::vector<Triangle>>&  triangles,
//                            std::vector<std::vector<DM::Vec3f>>& vertices)
//{ }

void Planet3::_uvMap(std::vector<std::vector<Triangle>>&  triangles,
                     std::vector<std::vector<DM::Vec3f>>& vertices)
{ }
