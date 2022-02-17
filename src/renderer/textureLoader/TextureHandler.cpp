#include "TextureHandler.h"
std::unordered_map<std::string, Texture2D> TextureHandler::myTextures;
void TextureHandler::LoadTexture(const std::string& path, const std::string& name)
{
  auto image = TextureLoader::LoadImageData(path.c_str());

  myTextures[name].Create(image.width, image.height);
  myTextures[name].UpdateNow((void*)image.pixels.data(), D3D12_RESOURCE_STATE_GENERIC_READ);
}

Texture2D* TextureHandler::GetTexture(const std::string& name)
{
  return &myTextures[name];
}
