#include "Planet.h"
#include "../renderer/TextureLoader.h"
#define FRONT_IDX 0
#define RIGHT_IDX 1
#define TOP_IDX 2
#define BACK_IDX 3
#define LEFT_IDX 4
#define BOT_IDX 5
#define NR_OF_SIDES 6

#define SET_CUBE false

Planet::Planet() { }

Planet::~Planet() { }

void Planet::Create(float size, uint div, float uvTiles)
{
  uvTiles = 1.0f / uvTiles;
  std::vector<std::vector<DM::Vec3f>> points;
  points.resize(NR_OF_SIDES);

  // Front
  {
    float     offset = 1.0f / (float)(div + 1);
    DM::Vec3f start(-0.5f, 0.5f, 0.5f);
    for (uint y = 0; y <= div + 1; y++)
    {
      start.x = -0.5f;
      for (uint x = 0; x <= div + 1; x++)
      {
        points[FRONT_IDX].push_back(start);
        start.x += offset;
      }
      start.y -= offset;
    }
    /*float w = div + 2;
    for (uint y = 0; y <= div + 1; y++)
    {
      for (uint x = 0; x <= div + 1; x++)
      {
        if ((x == 0 && y == 0) ||
            (x == div + 1 && y == div + 1) ||
            (x == 0 && y == div + 1) ||
            (x == div + 1 && y == 0))
          continue;

        uint      idx   = x + y * (div + 2);
        DM::Vec2f point = points[FRONT_IDX][idx].AsXmFloat2();
        DM::Vec2f center(0.0f, 0.0f);
        DM::Vec2f dir = center - point;
        float     l   = dir.Length();
        if (l < 0.001f)
          continue;

        point = point + dir * l * l * l * l * l * l; 
        if (x != 0 && x != div + 1)
          points[FRONT_IDX][idx].x = point.x;
        if (y != 0 && y != div + 1)
          points[FRONT_IDX][idx].y = point.y;
      }
    }*/
  }
  // Right
  {
    DM::Mat3x3      rotMatrix;
    constexpr float rad = DirectX::XMConvertToRadians(90.0f);
    rotMatrix.Store(DirectX::XMMatrixRotationAxis(DM::Vec3f(0.0f, 1.0f, 0.0f).Load(), rad));
    points[RIGHT_IDX].resize(points[FRONT_IDX].size());
    uint c = 0;
    for (auto& p : points[FRONT_IDX])
    {
      DM::Vec3f point;
      point.Store(DirectX::XMVector3TransformCoord(p.Load(), rotMatrix.Load()));
      points[RIGHT_IDX][c++] = point;
    }
  }
  // Left
  {
    DM::Mat3x3      rotMatrix;
    constexpr float rad = DirectX::XMConvertToRadians(90.0f);
    rotMatrix.Store(DirectX::XMMatrixRotationAxis(DM::Vec3f(0.0f, -1.0f, 0.0f).Load(), rad));
    points[LEFT_IDX].resize(points[FRONT_IDX].size());
    uint c = 0;
    for (auto& p : points[FRONT_IDX])
    {
      DM::Vec3f point;
      point.Store(DirectX::XMVector3TransformCoord(p.Load(), rotMatrix.Load()));
      points[LEFT_IDX][c++] = point;
    }
  }
  // Top
  {
    DM::Mat3x3      rotMatrix;
    constexpr float rad = DirectX::XMConvertToRadians(90.0f);
    rotMatrix.Store(DirectX::XMMatrixRotationAxis(DM::Vec3f(-1.0f, 0.0f, 0.0f).Load(), rad));
    points[TOP_IDX].resize(points[FRONT_IDX].size());
    uint c = 0;
    for (auto& p : points[FRONT_IDX])
    {
      DM::Vec3f point;
      point.Store(DirectX::XMVector3TransformCoord(p.Load(), rotMatrix.Load()));
      points[TOP_IDX][c++] = point;
    }
  }
  // BOT
  {
    DM::Mat3x3      rotMatrix;
    constexpr float rad = DirectX::XMConvertToRadians(90.0f);
    rotMatrix.Store(DirectX::XMMatrixRotationAxis(DM::Vec3f(1.0f, 0.0f, 0.0f).Load(), rad));
    points[BOT_IDX].resize(points[FRONT_IDX].size());
    uint c = 0;
    for (auto& p : points[FRONT_IDX])
    {
      DM::Vec3f point;
      point.Store(DirectX::XMVector3TransformCoord(p.Load(), rotMatrix.Load()));
      points[BOT_IDX][c++] = point;
    }
  }
  // BACK
  {
    DM::Mat3x3      rotMatrix;
    constexpr float rad = DirectX::XMConvertToRadians(180.0f);
    rotMatrix.Store(DirectX::XMMatrixRotationAxis(DM::Vec3f(0.0f, 1.0f, 0.0f).Load(), rad));
    points[BACK_IDX].resize(points[FRONT_IDX].size());
    uint c = 0;
    for (auto& p : points[FRONT_IDX])
    {
      DM::Vec3f point;
      point.Store(DirectX::XMVector3TransformCoord(p.Load(), rotMatrix.Load()));
      points[BACK_IDX][c++] = point;
    }
  }

  // Apply some noise
  {

  }

  // Convert to sphere and store in mesh
  {
    std::vector<std::vector<Vertex>> verts(NR_OF_SIDES);
    for (uint i = 0; i < NR_OF_SIDES; i++)
    {
      uint count = points[i].size();
      verts[i].resize(count);
      for (uint j = 0; j < count; j++)
      {
        DM::Vec3f p          = points[i][j];
        p                    = p.Normalize();
        DM::Vec3f nor        = p;
        p                    = p * size;
        verts[i][j].position = DirectX::XMFLOAT4A(p.x, p.y, p.z, 1.0f);
        verts[i][j].normal   = DirectX::XMFLOAT4A(nor.x, nor.y, nor.z, 0.0f);
        verts[i][j].color    = DirectX::XMFLOAT4A(1.0f, 1.0f, 1.0f, 1.0f);
        verts[i][j].uv       = DirectX::XMFLOAT4A(0.0f, 0.0f, 0.0f, 0.0f);

        if (SET_CUBE)
        {
          verts[i][j].position =
              DirectX::XMFLOAT4A(points[i][j].x, points[i][j].y, points[i][j].z, 1.0f);
          switch (i)
          {
          case FRONT_IDX:
            verts[i][j].normal = DirectX::XMFLOAT4A(0.0f, 0.0f, 1.0f, 0.0f);
            break;
          case RIGHT_IDX:
            verts[i][j].normal = DirectX::XMFLOAT4A(1.0f, 0.0f, 0.0f, 0.0f);
            break;
          case LEFT_IDX:
            verts[i][j].normal = DirectX::XMFLOAT4A(-1.0f, 0.0f, 0.0f, 0.0f);
            break;
          case TOP_IDX:
            verts[i][j].normal = DirectX::XMFLOAT4A(0.0f, 1.0f, 0.0f, 0.0f);
            break;
          case BOT_IDX:
            verts[i][j].normal = DirectX::XMFLOAT4A(0.0f, -1.0f, 0.0f, 0.0f);
            break;
          case BACK_IDX:
            verts[i][j].normal = DirectX::XMFLOAT4A(0.0f, 0.0f, -1.0f, 0.0f);
            break;
          }
        }
      }
    }
    uint w = div + 2;
    for (uint i = 0; i < NR_OF_SIDES; i++)
    {
      for (uint y = 0; y < w; y++)
      {
        float length = 0;
        for (uint x = 0; x < w - 1; x++)
        {
          DirectX::XMFLOAT4A xmP1 = verts[i][x + y * w].position;
          DirectX::XMFLOAT4A xmP2 = verts[i][x + 1 + y * w].position;
          DM::Vec3f          p1(xmP1.x, xmP1.y, xmP1.z);
          DM::Vec3f          p2(xmP2.x, xmP2.y, xmP2.z);
          length += (p2 - p1).Length();
        }
        length  = length * uvTiles;
        float l = 0.0f;
        for (uint x = 1; x < w; x++)
        {
          DirectX::XMFLOAT4A xmP1 = verts[i][x + y * w].position;
          DirectX::XMFLOAT4A xmP2 = verts[i][x - 1 + y * w].position;
          DM::Vec3f          p1(xmP1.x, xmP1.y, xmP1.z);
          DM::Vec3f          p2(xmP2.x, xmP2.y, xmP2.z);
          l += (p2 - p1).Length();
          verts[i][x + y * w].uv.x = l / length;
        }
      }
      for (uint x = 0; x < w; x++)
      {
        float length = 0;
        for (uint y = 0; y < w - 1; y++)
        {
          DirectX::XMFLOAT4A xmP1 = verts[i][x + y * w].position;
          DirectX::XMFLOAT4A xmP2 = verts[i][x + 1 + y * w].position;
          DM::Vec3f          p1(xmP1.x, xmP1.y, xmP1.z);
          DM::Vec3f          p2(xmP2.x, xmP2.y, xmP2.z);
          length += (p2 - p1).Length();
        }
        length  = length * uvTiles;
        float l = 0.0f;
        for (uint y = 1; y < w; y++)
        {
          DirectX::XMFLOAT4A xmP1 = verts[i][x + y * w].position;
          DirectX::XMFLOAT4A xmP2 = verts[i][x - 1 + y * w].position;
          DM::Vec3f          p1(xmP1.x, xmP1.y, xmP1.z);
          DM::Vec3f          p2(xmP2.x, xmP2.y, xmP2.z);
          l += (p2 - p1).Length();
          verts[i][x + y * w].uv.y = l / length;
        }
      }
    }
    myMesh.SetMesh(std::move(verts));
  }

  // Create indices
  {
    std::vector<std::vector<uint>> indices(NR_OF_SIDES);
    uint                           w = div + 2;
    for (uint i = 0; i < NR_OF_SIDES; i++)
    {
      for (uint j = 0; j < points[i].size() - w; j++)
      {
        if ((j + 1) % w == 0)
          continue;
        //First triangle
        indices[i].push_back(j);
        indices[i].push_back(j + w + 1);
        indices[i].push_back(j + w);

        //Second Triangle
        indices[i].push_back(j);
        indices[i].push_back(j + 1);
        indices[i].push_back(j + w + 1);
      }
    }
    myMesh.SetIndices(std::move(indices));
  }
  uint   height = 0, width = 0;
  TextureLoader::Image shrek = TextureLoader::LoadImageData("assets/textures/Shrek.PNG");
  myMesh.SetImages(std::move(shrek));
}

const Mesh& Planet::GetMesh() const
{
  return myMesh;
}
