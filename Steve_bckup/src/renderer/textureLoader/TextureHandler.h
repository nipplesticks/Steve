#pragma once
#include "../buffers/Texture2D.h"
#include "TextureLoader.h"
#include <unordered_map>

class TextureHandler
{
private:
  TextureHandler()  = default;
  ~TextureHandler() = default;

public:
  static void       LoadTexture(const std::string& path, const std::string& name);
  static Texture2D* GetTexture(const std::string& name);

private:
  static std::unordered_map<std::string, Texture2D> myTextures;
};