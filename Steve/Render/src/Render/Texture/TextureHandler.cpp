#include "pch.h"
#include "Render/Texture/TextureHandler.h"

using namespace Render;

std::unordered_map<std::string, Texture2D> TextureHandler::gTextures;

void Render::TextureHandler::LoadTextureFromFile(const std::string& path,
                                                 const std::string& textureName)
{
  Image4 img;
  Render::LoadImageFromFile(img, path);
  auto size = img.GetSize();
  gTextures[textureName].Create(textureName, size.x, size.y);
  gTextures[textureName].Update(img.GetPixels());
}

void Render::TextureHandler::LoadTextureFromImage(const Image1&      image,
                                                  const std::string& textureName)
{
  auto size = image.GetSize();
  gTextures[textureName].Create(textureName, size.x, size.y, DXGI_FORMAT_R8_UNORM);
  gTextures[textureName].Update((void*)image.GetPixels());
}

void Render::TextureHandler::LoadTextureFromImage(const Image2&      image,
                                                  const std::string& textureName)
{
  auto size = image.GetSize();
  gTextures[textureName].Create(textureName, size.x, size.y, DXGI_FORMAT_R8G8_UNORM);
  gTextures[textureName].Update((void*)image.GetPixels());
}

void Render::TextureHandler::LoadTextureFromImage(const Image4&      image,
                                                  const std::string& textureName)
{
  auto size = image.GetSize();
  gTextures[textureName].Create(textureName, size.x, size.y, DXGI_FORMAT_R8G8B8A8_UNORM);
  gTextures[textureName].Update((void*)image.GetPixels());
}

Texture2D* Render::TextureHandler::GetTexture(const std::string& textureName)
{
  return &gTextures[textureName];
}
