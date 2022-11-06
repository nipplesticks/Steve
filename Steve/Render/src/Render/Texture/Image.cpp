#include "pch.h"
#include "Render/Texture/Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Render/Texture/stb_image.h"

using namespace Render;

template <typename T>
static inline void LoadFromFile(Image<T>& img, const char* str, uint8 numComponents)
{
  int w = 0;
  int h = 0;
  int comp = 0;
  uint8* img_p = stbi_load(str, &w, &h, &comp, numComponents);

  img.Create(w, h);
  memcpy(img.GetPixels(), img_p, sizeof(T) * w * h);
  free(img_p);
}

void Render::LoadImageFromFile(Image1& img, const std::string& imagePath)
{
  LoadFromFile(img, imagePath.c_str(), 1);
}

void Render::LoadImageFromFile(Image2& img, const std::string& imagePath)
{
  LoadFromFile(img, imagePath.c_str(), 2);
}

void Render::LoadImageFromFile(Image4& img, const std::string& imagePath)
{
  LoadFromFile(img, imagePath.c_str(), 4);
}
