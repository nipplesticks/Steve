#pragma once
#include "../Resource/Texture2D.h"
#include "Image.h"
#include <unordered_map>

namespace Render
{
  class TextureHandler
  {
  private:
    TextureHandler()  = default;
    ~TextureHandler() = default;

  public:
    static void LoadTextureFromFile(const std::string& path, const std::string& textureName);

    static void LoadTextureFromImage(const Image1& image, const std::string& textureName);
    static void LoadTextureFromImage(const Image2& image, const std::string& textureName);
    static void LoadTextureFromImage(const Image4& image, const std::string& textureName);

    static Texture2D* GetTexture(const std::string& textureName);

  private:
    static std::unordered_map<std::string, Texture2D> gTextures;
  };
} // namespace Render