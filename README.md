# Targa Image Maker for C++
A small and easy to use library for targa image making with C++.

## Usage
Download TgaImage.h and TgaImage.cpp and add them to you project.

### Simple example

Fully working example. Creates a blue image with a white square.
```cpp
#include "TgaImage.h"

int main()
{
  // Declare and initialize an image called myImage
  ti::TgaImage myImage(ti::TgaImage(128, 128));

  // Declare and initialize a new color called steelBlue
  auto steelBlue(ti::Color(70, 130, 180));

  // Fill the image with steelBlue
  myImage.fill(steelBlue);

  // Nested loop to draw a white square
  for (auto i = 32; i < 64; i++)
  {
    for (auto j = 64; j < 96; j++)
    {
      // Set pixel at (i, j) to white (r, g, b = 255, 255, 255)
      myImage.set(i, j, 255);
    }
  }

  // Save the image under the name myImage.tga
  myImage.save("myImage.tga");

return 0;
}
```

### Function description

Create an image with a width of 128 pixels and a height of 256 pixels.
```cpp
auto image(ti::TgaImage(128, 256));
```

Fill the entire image with grey. The values for red, green and blue will all be set to 128.
```cpp
image.fill(128);
```

Fill the entire image with red. The value for red will be set to 255, and the values for green and blue to 0.
```cpp
image.fill(255, 0, 0);
```

Define a color and fill the entire image with it.
```cpp
auto myColor(ti::Color(70,130,180));
image.fill(myColor);
```

Set the pixel att position (0, 16) to grey (the value 128).
```cpp
image.set(0, 16, 128);
```

Set the pixel att position (0, 16) to red. Red, green and blur are set to 255, 0, 0 respectivly.
```cpp
image.set(0, 16, 255, 0, 0);
```

Set the pixel att position (0, 16) to red. Here we define a color and use it to fill the image with.
```cpp
auto myColor(ti::Color(255,0,0));
image.set(0, 16, 255, 0, 0);
```

Save the image with the name myImage.tga at the location of the program.
```cpp
image.save("myImage.tga");
```

Save the image at F:\myImage.tga (on Windows).
```cpp
image.save("F:\\", "myImage.tga"); 
```
