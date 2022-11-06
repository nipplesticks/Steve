#pragma once
#include <vector>
#include <Common/DMath.h>

namespace Render
{
  template <class T>
  class Pixel
  {
  public:
    Pixel(const T& color = T());
    void SetColor(const T& color);
    T    pixel;
  };

  template <class T>
  class Image
  {
  public:
    Image() = default;
    Image(uint32 width, uint32 height);
    Image(const Image<T>& img);
    Image(Image<T>&& img) noexcept;
    void            Create(uint32 width, uint32 height, const Pixel<T>& pixel = Pixel<T>());
    Image<T>& operator=(const Image<T>& img);
    const Pixel<T>& GetPixel(uint32 x, uint32 y) const;
    const Pixel<T>& GetPixel(const DM::Vec2u& index) const;
    void      SetPixel(uint32 x, uint32 y, const Pixel<T>& pixel);
    void      SetPixel(const DM::Vec2u& index, const Pixel<T>& pixel);
    const Pixel<T>*       GetPixels() const;
    Pixel<T>*       GetPixels();
    DM::Vec2u       GetSize() const;
    uint64          GetByteSize() const;

  private:
    uint32                myWidth = 0u;
    uint32                myHeight = 0u;
    std::vector<Pixel<T>> myPixels;
  };


  using Image1 = Image<uint8>;
  using Image2 = Image<DM::Color2>;
  using Image4 = Image<DM::Color4>;

  void LoadImageFromFile(Image1& img, const std::string& imagePath);
  void LoadImageFromFile(Image2& img, const std::string& imagePath);
  void LoadImageFromFile(Image4& img, const std::string& imagePath);

  template <class T>
  inline Pixel<T>::Pixel(const T& color)
  {
    SetColor(color);
  }
  template <class T>
  inline void Pixel<T>::SetColor(const T& color)
  {
    pixel = color;
  }
  template <class T>
  inline Image<T>::Image(uint32 width, uint32 height)
  {
    Create(width, height);
  }
  template <class T>
  inline Image<T>::Image(const Image<T>& img)
  {
    myWidth = img.myWidth;
    myHeight = img.myHeight;
    myPixels = img.myPixels;
  }
  template <class T>
  inline Image<T>::Image(Image<T>&& img) noexcept
  {
    myWidth  = img.myWidth;
    myHeight = img.myHeight;
    myPixels = std::move(img.myPixels);
  }
  template <class T>
  inline void Image<T>::Create(uint32 width, uint32 height, const Pixel<T>& pixel)
  {
    myWidth = width;
    myHeight = height;
    myPixels.resize(width * height);
    for (auto& p : myPixels)
      p = pixel;
  }
  template <class T>
  inline Image<T>& Image<T>::operator=(const Image<T>& img)
  {
    if (this != &img)
    {
      myWidth = img.myWidth;
      myWidth = img.myWeight;
      myWidth = img.myPixels;
    }
    return *this;
  }
  template <class T>
  inline const Pixel<T>& Image<T>::GetPixel(uint32 x, uint32 y) const
  {
    return GetPixel(DM::Vec2u(x, y));
  }
  template <class T>
  inline const Pixel<T>& Image<T>::GetPixel(const DM::Vec2u& index) const
  {
    return myPixels[index.x + index.y * myWidth];
  }
  template <class T>
  inline void Image<T>::SetPixel(uint32 x, uint32 y, const Pixel<T>& pixel)
  {
    SetPixel(DM::Vec2u(x, y), pixel);
  }
  template <class T>
  inline void Image<T>::SetPixel(const DM::Vec2u& index, const Pixel<T>& pixel)
  {
    myPixels[index.x + index.y * myWidth] = pixel;
  }
  template <class T>
  inline const Pixel<T>* Image<T>::GetPixels() const
  {
    return myPixels.data();
  }
  template <class T>
  inline Pixel<T>* Image<T>::GetPixels()
  {
    return myPixels.data();
  }
  template <class T>
  inline DM::Vec2u Image<T>::GetSize() const
  {
    return DM::Vec2u(myWidth, myHeight);
  }
  template <class T>
  inline uint64 Image<T>::GetByteSize() const
  {
    return sizeof(T) * myWidth * myHeight;
  }
} // namespace Render