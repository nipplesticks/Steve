#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


TextureLoader::Image TextureLoader::LoadImageData(const char* str)
{
  int w = 0, h = 0;
  int comp = 0;

  uint8* img = stbi_load(str, &w, &h, &comp, 4);

  TextureLoader::Image image;
  image.height = h;
  image.width  = w;
  uint size    = w * h * 4 * sizeof(uint8);
  image.pixels.resize(w * h * 4);
  memcpy(image.pixels.data(), img, size);

  free(img);

  return image;
}