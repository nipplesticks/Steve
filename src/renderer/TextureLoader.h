#pragma once
#include "../utility/Typedef.h"
#include <vector>
class TextureLoader
{
public:
  struct Image
  {
    Image() = default;
    Image(const Image& img)
    {
      width  = img.width;
      height = img.height;
      pixels = img.pixels;
    }
    Image(Image&& img) noexcept
    {
      width = img.width;
      height = img.height;
      pixels = std::move(img.pixels);
    }
    Image& operator=(const Image& img)
    {
      if (this != &img)
      {
        width  = img.width;
        height = img.height;
        pixels = img.pixels;
      }
      return *this;
    }
    std::vector<uint8> pixels;
    uint               width;
    uint               height;
  };
  static Image LoadImageData(const char* str);
};