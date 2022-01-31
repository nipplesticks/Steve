#pragma once
#include "../utility/Typedef.h"
#include <vector>
class TextureLoader
{
public:

  struct Image
  {
    struct Pixel
    {
      uint8 r, g, b, a;
    };

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
    Pixel              GetPixel(uint x, uint y)
    {
      Pixel p;
      p.r = pixels[(x + y * width) * 4 + 0];
      p.g = pixels[(x + y * width) * 4 + 1];
      p.b = pixels[(x + y * width) * 4 + 2];
      p.a = pixels[(x + y * width) * 4 + 3];
      return p;
    }

    Pixel GetAveragePixel(uint x, uint y, int sampleSize = 0)
    {
      int _x = x;
      int _y = y;

      uint r = 0, g = 0, b = 0, a = 0;
      uint c = 0;
      for (int yy = -sampleSize; yy <= sampleSize; yy++)
      {
        for (int xx = -sampleSize; xx <= sampleSize; xx++)
        {
          c++;
          Pixel p = GetPixel((xx + _x) % width, (yy + _y) % height);
          r += p.r;
          g += p.g;
          b += p.b;
          a += p.a;
        }
      }
      r = r / c;
      g = g / c;
      b = b / c;
      a = a / c;
      Pixel p {r, g, b, a};

      return p;
    }
    

    std::vector<uint8> pixels;
    uint               width;
    uint               height;
  };
  static Image LoadImageData(const char* str);
};