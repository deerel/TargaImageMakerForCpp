#include "TgaImage.h"

#include <fstream>
#include <stdexcept>
#include <cstdint>

namespace ti
{
  struct Data
  {
    char b;
    char g;
    char r;
  };

  struct Header
  {
    uint8_t idLength;            // ID Length
    uint8_t colorMapType;        // Color Map Type
    uint8_t imageType;           // Image Type
    uint8_t colorMapStart_byte1; // Color Map Specification
    uint8_t colorMapStart_byte2;
    uint8_t colorMapLength_byte1;
    uint8_t colorMapLength_byte2;
    uint8_t colorMapSize;
    uint8_t xOrigin_byte1;       // Image Specification
    uint8_t xOrigin_byte2;
    uint8_t yOrigin_byte1;
    uint8_t yOrigin_byte2;
    uint8_t width_byte1;
    uint8_t width_byte2;
    uint8_t height_byte1;
    uint8_t height_byte2;
    uint8_t pixelDepth;
    uint8_t imageDescriptor;
  };

  using namespace std;

  class TgaImage::impl
  {
  public:
    impl(uint16_t width, uint16_t height)
      : m_width(width)
      , m_height(height)
      , m_header()
      , m_imageData(nullptr)
    {
      m_imageData = std::unique_ptr<Data[]>{ new Data[width*height] };
      m_header.imageType = 2;                           // True Color Mode
      m_header.width_byte1 = 0x00FF & width;            // Little endian fix
      m_header.width_byte2 = ((0xFF00 & width) >> 8);   // Little endian fix
      m_header.height_byte1 = 0x00FF & height;          // Little endian fix
      m_header.height_byte2 = ((0xFF00 & height) >> 8); // Little endian fix
      m_header.pixelDepth = 24;
      m_header.imageDescriptor = 0b00100000;            // bit 5:
                                                        // 0 = (0,0) in top left corner
                                                        // 1 = (0,0) in lower left corner
    }

    ~impl()
    {
    }

    void save(const std::string& path, const std::string& filename)
    {
      const std::string fullPath = path + filename;
      ofstream image(fullPath.c_str(), ios::binary);
      if (image.is_open())
      {
        image.write(reinterpret_cast<char*>(&m_header), sizeof(Header));
        image.write(reinterpret_cast<char*>(m_imageData.get()),
          sizeof(Data)*m_width*m_height);
        image.close();
      }
      else
      {
        throw std::invalid_argument("Could not save image at given location.");
      }
    }

    void fill(uint8_t red, uint8_t green, uint8_t blue) noexcept
    {
      for (auto i = 0; i < m_width*m_height; ++i)
      {
        m_imageData[i].r = red;
        m_imageData[i].g = green;
        m_imageData[i].b = blue;
      }
    }

    void set(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
    {
      if (x < 0 || x >= m_width
        || y < 0 || y >= m_height)
      {
        // Outside image boundaries
        throw std::invalid_argument("Coordinate is outside the image.");
      }

      const auto index = x + y * m_width;
      m_imageData[index].r = red;
      m_imageData[index].g = green;
      m_imageData[index].b = blue;
    }
  private:
    const uint16_t m_width;
    const uint16_t m_height;
    std::string m_fileName;
    Header m_header;
    std::unique_ptr<Data[]> m_imageData;
  }; // impl

  TgaImage::TgaImage(uint16_t width, uint16_t height)
    : m_upImpl(new impl(width, height))
  {
  }

  TgaImage::~TgaImage() = default;

  TgaImage::TgaImage(TgaImage && op) noexcept = default;

  TgaImage & TgaImage::operator=(TgaImage && op) noexcept = default;

  void TgaImage::save(const std::string & filename)
  {
    m_upImpl->save("", filename);
  }

  void TgaImage::save(const std::string & path, const std::string & filename)
  {
    m_upImpl->save(path, filename);
  }

  void TgaImage::fill(const Color & color) noexcept
  {
    m_upImpl->fill(color.r, color.g, color.b);
  }

  void TgaImage::fill(uint8_t value) noexcept
  {
    m_upImpl->fill(value, value, value);
  }

  void TgaImage::fill(uint8_t red, uint8_t green, uint8_t blue) noexcept
  {
    m_upImpl->fill(red, green, blue);
  }

  void TgaImage::set(uint16_t x, uint16_t y, const Color & color)
  {
    m_upImpl->set(x, y, color.r, color.g, color.b);
  }

  void TgaImage::set(uint16_t x, uint16_t y, uint8_t value)
  {
    m_upImpl->set(x, y, value, value, value);
  }

  void TgaImage::set(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
  {
    m_upImpl->set(x, y, red, green, blue);
  }



}