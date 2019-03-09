#pragma once

#include <cstdalign> 
#include <memory>
#include <string>
#include <vector>

namespace ti
{

  /**
    Holds rgb values for a color.
  */
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
    /** 
      Constructor

      @param width The width of the image, max 65535.
      @param height The height of the image, max 65535.
    */
    TgaImage(uint16_t width, uint16_t height);

    /**
      Destructor
    */
    ~TgaImage();

    /**
      Copy Constructor
    */
    TgaImage(TgaImage && op) noexcept;

    /**
      Copy Constructor
    */
    TgaImage& operator=(TgaImage && op) noexcept;

    /**
      Saves the image.

      @param filename The name of the image file.
    */
    void save(const std::string& filename);

    /**
      Saves the image.

      @param path The path to the location where the image is saved.
      @param filename The name of the image file.
    */
    void save(const std::string& path, const std::string& fileName);

    /**
      Fill entire image with a color.

      @param color The Color to fill the image with.
    */
    void fill(const Color& color) noexcept;

    /**
      Fill entire image with a color.

      @param value The pixel value to fill the image with (0-255).
    */
    void fill(uint8_t value) noexcept;

    /**
      Fill entire image with a color.

      @param red The value for the red channel (0-255).
      @param green The value for the green (0-255).
      @param blur The value for the blue channel (0-255).
    */
    void fill(uint8_t red, uint8_t green, uint8_t blue) noexcept;

    /**
      Set specific pixel to a color.

      @param x The x coordinate for the pixel.
      @param y The y coordinate for the pixel.
      @param color The Color of the pixel.
    */
    void set(uint16_t x, uint16_t y, const Color& color);

    /**
      Set specific pixel to a color.

      @param x The x coordinate for the pixel.
      @param y The y coordinate for the pixel.
      @param value The pixel value for the pixel (0-255).
    */
    void set(uint16_t x, uint16_t y, uint8_t value);

    /**
      Set specific pixel to a color.

      @param x The x coordinate for the pixel.
      @param y The y coordinate for the pixel.
      @param red The value for the red channel (0-255).
      @param green The value for the green channel (0-255).
      @param blur The value for the blue channel (0-255).
    */
    void set(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);
  private:
    class impl;
    std::unique_ptr<impl> m_upImpl;
  };
}

