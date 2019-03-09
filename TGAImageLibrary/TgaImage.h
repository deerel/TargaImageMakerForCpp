#pragma once

#include <cstdalign> 
#include <memory>
#include <string>
#include <vector>

namespace ti
{

  struct Color
  {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue){}
  };

  class TgaImage
  {
  public:
    // Maximum size is 65,535 x 65,535 pixels.
    TgaImage(uint16_t width, uint16_t height);
    ~TgaImage();
    TgaImage(TgaImage && op) noexcept;
    TgaImage& operator=(TgaImage && op) noexcept;
    void save(const std::string& fileName);
    void save(const std::string& path, const std::string& fileName);
    void fill(const Color& color) noexcept;
    void fill(uint8_t value) noexcept;
    void fill(uint8_t red, uint8_t green, uint8_t blue) noexcept;
    void set(uint16_t x, uint16_t y, const Color& color);
    void set(uint16_t x, uint16_t y, uint8_t value);
    void set(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);
  private:
    class impl;
    std::unique_ptr<impl> m_pImpl;
  };
}

