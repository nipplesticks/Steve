#include "Planet2.h"
#include "../renderer/TextureLoader.h"
#include "../utility/Timer.h"
#include <iostream>
#include <map>
//https://mft-dev.dk/uv-mapping-sphere/
Planet2::Planet2() { }

Planet2::~Planet2() { }

//Bitmap CreateTexture(int width, int height)
//{
//  Bitmap       image        = new Bitmap(width, height);
//  double       widthFactor  = 1.0 / width;
//  double       heightFactor = 1.0 / height;
//  Color        baseColor    = Color.FromArgb(255, 127, 35, 7);
//  SimplexNoise generator    = new SimplexNoise(seed : -5000);
//  for (int x = 0; x < width; ++x)
//  {
//    for (int y = 0; y < height; ++y)
//    {
//      double dX = x / (double)width;
//      double dY = y / (double)height;
//      /* noise range is clamped -1 to 1 */
//      double noise =
//          generator.PerlinNoise(dX, dY, octaves : 3, persistence : 3.0f / 4.0f, lacunarity : 3f);
//      int   blueHue  = (int)(baseColor.B * noise) + baseColor.B;
//      int   redHue   = (int)(baseColor.R * noise) + baseColor.R;
//      int   greenHue = (int)(baseColor.G * noise) + baseColor.G;
//      Color col      = Color.FromArgb(baseColor.A, redHue, greenHue, blueHue);
//      image.SetPixel(x, y, col);
//    }
//  }
//  return image;
//}

void pushIndices(uint a, uint b, uint c, std::vector<uint>& vec)
{
  vec.push_back(a);
  vec.push_back(b);
  vec.push_back(c);
}

void CreateIcosahedron(std::vector<uint>& indices, std::vector<DM::Vec3f>& vertices)
{
  float phi = (1.0f + sqrt(5.0f)) * 0.5f; // Golder Ratio
  float a   = 1.0f;
  float b   = 1.0f / phi;
  vertices.resize(12);
  indices.clear();

  uint idx        = 0;
  vertices[idx++] = DM::Vec3f(0, b, -a);
  vertices[idx++] = DM::Vec3f(b, a, 0);
  vertices[idx++] = DM::Vec3f(-b, a, 0);
  vertices[idx++] = DM::Vec3f(0, b, a);
  vertices[idx++] = DM::Vec3f(0, -b, a);
  vertices[idx++] = DM::Vec3f(-a, 0, b);
  vertices[idx++] = DM::Vec3f(0, -b, -a);
  vertices[idx++] = DM::Vec3f(a, 0, -b);
  vertices[idx++] = DM::Vec3f(a, 0, b);
  vertices[idx++] = DM::Vec3f(-a, 0, -b);
  vertices[idx++] = DM::Vec3f(b, -a, 0);
  vertices[idx++] = DM::Vec3f(-b, -a, 0);

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

  /*pushIndices(v3,  v2,  v1,  indices);
  pushIndices(v2,  v3,  v4,  indices);
  pushIndices(v6,  v5,  v4,  indices);
  pushIndices(v5,  v9,  v4,  indices);
  pushIndices(v8,  v7,  v1,  indices);
  pushIndices(v7,  v10, v1,  indices);
  pushIndices(v12, v11, v5,  indices);
  pushIndices(v11, v12, v7,  indices);
  pushIndices(v10, v6,  v3,  indices);
  pushIndices(v6,  v10, v12, indices);
  pushIndices(v9,  v8,  v2,  indices);
  pushIndices(v8,  v9,  v11, indices);
  pushIndices(v3,  v6,  v4,  indices);
  pushIndices(v9,  v2,  v4,  indices);
  pushIndices(v10, v3,  v1,  indices);
  pushIndices(v2,  v8,  v1,  indices);
  pushIndices(v12, v10, v7,  indices);
  pushIndices(v8,  v11, v7,  indices);
  pushIndices(v6,  v12, v5,  indices);
  pushIndices(v11, v9,  v5,  indices);*/

  pushIndices(v2, v3, v1, indices);
  pushIndices(v3, v2, v4, indices);
  pushIndices(v5, v6, v4, indices);
  pushIndices(v9, v5, v4, indices);
  pushIndices(v7, v8, v1, indices);
  pushIndices(v10, v7, v1, indices);
  pushIndices(v11, v12, v5, indices);
  pushIndices(v12, v11, v7, indices);
  pushIndices(v6, v10, v3, indices);
  pushIndices(v10, v6, v12, indices);
  pushIndices(v8, v9, v2, indices);
  pushIndices(v9, v8, v11, indices);
  pushIndices(v6, v3, v4, indices);
  pushIndices(v2, v9, v4, indices);
  pushIndices(v3, v10, v1, indices);
  pushIndices(v8, v2, v1, indices);
  pushIndices(v10, v12, v7, indices);
  pushIndices(v11, v8, v7, indices);
  pushIndices(v12, v6, v5, indices);
  pushIndices(v9, v11, v5, indices);
}

void SubdevideIcosahedron(std::vector<uint>& indices, std::vector<DM::Vec3f>& vertices)
{
  uint ind = indices.size();

  std::vector<DM::Vec3f> newVertices((ind / 3) * 6);
  std::vector<uint>      newIndices((ind / 3u) * 12u);
  uint                   vertCounter = 0;
  uint                   idxCounter  = 0;

  for (uint i = 0; i < ind; i += 3)
  {
    uint v1 = indices[i];
    uint v2 = indices[i + 1];
    uint v3 = indices[i + 2];

    DM::Vec3f p1 = vertices[v1];
    DM::Vec3f p2 = vertices[v2];
    DM::Vec3f p3 = vertices[v3];

    DM::Vec3f p1p2 = p1 + (p2 - p1) * 0.5f;
    DM::Vec3f p2p3 = p2 + (p3 - p2) * 0.5f;
    DM::Vec3f p3p1 = p3 + (p1 - p3) * 0.5f;

    newVertices[vertCounter++] = vertices[v1];
    newVertices[vertCounter++] = p1p2;
    newVertices[vertCounter++] = vertices[v2];
    newVertices[vertCounter++] = p2p3;
    newVertices[vertCounter++] = vertices[v3];
    newVertices[vertCounter++] = p3p1;

    uint s  = vertCounter;
    uint i1 = s - 6;
    uint i2 = s - 5;
    uint i3 = s - 4;
    uint i4 = s - 3;
    uint i5 = s - 2;
    uint i6 = s - 1;

    newIndices[idxCounter++] = i1;
    newIndices[idxCounter++] = i2;
    newIndices[idxCounter++] = i6;
    newIndices[idxCounter++] = i2;
    newIndices[idxCounter++] = i3;
    newIndices[idxCounter++] = i4;
    newIndices[idxCounter++] = i6;
    newIndices[idxCounter++] = i4;
    newIndices[idxCounter++] = i5;
    newIndices[idxCounter++] = i2;
    newIndices[idxCounter++] = i4;
    newIndices[idxCounter++] = i6;
  }

  indices  = std::move(newIndices);
  vertices = std::move(newVertices);
}

void OptimiseMesh(std::vector<uint>& indices, std::vector<DM::Vec3f>& vertices)
{
  std::vector<DM::Vec3f> newVertices(vertices.size());
  std::vector<bool>      invalidPoints(vertices.size());
  uint                   removed = 0;
  uint                   counter = 0;
  for (uint i = 0; i < vertices.size(); i++)
  {
    if (invalidPoints[i])
    {
      removed++;
      continue;
    }
    //newVertices.push_back(vertices[i]);
    newVertices[counter++] = vertices[i];

    for (uint j = i + 1; j < vertices.size(); j++)
    {
      if (invalidPoints[j])
        continue;

      if ((vertices[i] - vertices[j]).LengthSq() < FLT_EPSILON)
      {
        invalidPoints[j] = true;

        for (uint k = 0; k < indices.size(); k++)
        {
          if (indices[k] == j || indices[k] == i)
          {
            //indices[k] = newVertices.size() - 1;
            indices[k] = counter - 1;
          }
        }
      }
    }
  }
  std::cout << "removed: " << removed << "\n";
  newVertices.resize(counter);
  vertices = std::move(newVertices);
}

std::vector<uint> detectWrappedUVCoordinates(std::vector<uint>&   indices,
                                             std::vector<Vertex>& vertices)
{
  std::vector<uint> _ind;
  uint              nrOfIndices = indices.size();

  for (uint i = 0; i < nrOfIndices; i += 3)
  {
    uint a = indices[i];
    uint b = indices[i + 1];
    uint c = indices[i + 2];

    DM::Vec3f texA(vertices[a].uv.x, vertices[a].uv.y, 0.0f);
    DM::Vec3f texB(vertices[b].uv.x, vertices[b].uv.y, 0.0f);
    DM::Vec3f texC(vertices[c].uv.x, vertices[c].uv.y, 0.0f);
    DM::Vec3f texNormal = (texC - texA).Cross(texB - texA);
    if (texNormal.z < 0)
      _ind.push_back(i);
  }

  return _ind;
}

void fixWrappedUV(std::vector<uint>&   wrapped,
                  std::vector<uint>&   indices,
                  std::vector<Vertex>& vertices)
{
  uint                 verticeIndex = vertices.size() - 1;
  std::map<uint, uint> visited;

  for (auto& i : wrapped)
  {
    uint   a = indices[i];
    uint   b = indices[i + 1];
    uint   c = indices[i + 2];
    Vertex A = vertices[a];
    Vertex B = vertices[b];
    Vertex C = vertices[c];

    if (A.uv.x < 0.25f)
    {
      uint tempA = a;
      if (visited.find(a) == visited.end())
      {
        A.uv.x += 1.0f;
        vertices.push_back(A);
        verticeIndex++;
        visited.insert(std::make_pair(a, verticeIndex));
        tempA = verticeIndex;
      }
      else
      {
        tempA = visited[a];
      }
      a = tempA;
    }
    if (B.uv.x < 0.25f)
    {
      uint tempB = b;
      if (visited.find(b) == visited.end())
      {
        B.uv.x += 1.0f;
        vertices.push_back(B);
        verticeIndex++;
        visited.insert(std::make_pair(b, verticeIndex));
        tempB = verticeIndex;
      }
      else
      {
        tempB = visited[b];
      }
      b = tempB;
    }
    if (C.uv.x < 0.25f)
    {
      uint tempC = c;
      if (visited.find(c) == visited.end())
      {
        C.uv.x += 1.0f;
        vertices.push_back(C);
        verticeIndex++;
        visited.insert(std::make_pair(c, verticeIndex));
        tempC = verticeIndex;
      }
      else
      {
        tempC = visited[c];
      }
      c = tempC;
    }
    indices[i]     = a;
    indices[i + 1] = b;
    indices[i + 2] = c;
  }
}

void fixSharedPoleVertices(std::vector<uint>& indices, std::vector<Vertex>& vertices)
{
  uint northIdx  = UINT_MAX;
  uint southIdx  = UINT_MAX;
  uint vertexIdx = vertices.size() - 1;
  for (uint i = 0; i < vertices.size(); i++)
  {
    if (northIdx != UINT_MAX && southIdx != UINT_MAX)
      break;

    if (vertices[i].position.y == 1.0f)
      northIdx = i;
    if (vertices[i].position.y == -1.0f)
      southIdx = i;
  }

  for (uint i = 0; i < indices.size(); i++)
  {
    if (indices[i] == northIdx)
    {
      uint startIdx = i - (i % 3);
      Vertex A        = vertices[indices[startIdx]];
      Vertex B        = vertices[indices[startIdx + 1]];
      Vertex C        = vertices[indices[startIdx + 2]];
      Vertex newNorth = vertices[northIdx];
      newNorth.uv.x   = (B.uv.x + C.uv.x) * 0.5f;
      vertexIdx++;
      vertices.push_back(newNorth);
      indices[i] = vertexIdx;
    }
    else if (indices[i] == southIdx)
    {
      uint   startIdx = i - (i % 3);
      Vertex A        = vertices[indices[startIdx]];
      Vertex B        = vertices[indices[startIdx + 1]];
      Vertex C        = vertices[indices[startIdx + 2]];
      Vertex newSouth = vertices[southIdx];
      newSouth.uv.x   = (B.uv.x + C.uv.x) * 0.5f;
      vertexIdx++;
      vertices.push_back(newSouth);
      indices[i] = vertexIdx;
    }
  }
}

void Planet2::Create(float size, uint div, float uvTiles)
{
  std::vector<DM::Vec3f> points;
  std::vector<uint>      indices;
  CreateIcosahedron(indices, points);
  Timer t;
  t.Start();

  for (uint i = 0; i < div; i++)
  {
    SubdevideIcosahedron(indices, points);
  }

  std::cout << "Before:\n";
  std::cout << points.size() << "\n";
  OptimiseMesh(indices, points);
  std::cout << "After:\n";
  std::cout << points.size() << "\n";

  double lol = t.Stop();
  std::cout << "Time taken: " << lol << " seconds\n";

  std::vector<Vertex> verts(points.size());
  Vertex              v = {};
  v.color               = DirectX::XMFLOAT4A(1, 1, 1, 1);
  float PI              = DirectX::XM_PI;
  for (uint i = 0; i < points.size(); i++)
  {
    verts[i]          = v;
    verts[i].position = points[i].Normalize().AsXmFloat4APoint();
    //verts[i].position = points[i].AsXmFloat4APoint();
    verts[i].normal = points[i].Normalize().AsXmFloat4AVector();
    verts[i].uv.x   = 0.5f + (std::atan2(verts[i].position.z, verts[i].position.x) / (2.0f * PI));
    verts[i].uv.y   = 0.5f - (std::asin(verts[i].position.y) / PI);
  }
  std::vector<uint> wrapped = detectWrappedUVCoordinates(indices, verts);
  fixWrappedUV(wrapped, indices, verts);
  fixSharedPoleVertices(indices, verts);

  myMesh.SetMesh(std::move(verts));
  myMesh.SetIndices(std::move(indices));

  uint height = 0, width = 0;
  //TextureLoader::Image shrek = TextureLoader::LoadImageData("assets/textures/Shrek.PNG");
  //TextureLoader::Image shrek = TextureLoader::LoadImageData("assets/textures/Tile.png");
  TextureLoader::Image shrek = TextureLoader::LoadImageData("assets/textures/testingFesting.jpg");
  myMesh.SetImages(std::move(shrek));
}

const Mesh& Planet2::GetMesh() const
{
  return myMesh;
}
