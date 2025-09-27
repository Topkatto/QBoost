# QBoost/Canvas tutorial
## Introduction to Canvas
QBoost is an open-source library to make different things, some as shortcuts.
Canvas is an rendering engine for terminal, so if you hate graphics progamming, this may be for you.
## How to use Canvas
To use canvas, you must install the whole **QBoost library along with Boost (not required if you only include Canvas).
**

## Tutorial
### 1. Rendering for non-animated canvas
#### 1a. Rendering your first canva
To render canvas, we need to make an canvas first.
```c++
#include "include/QBoost/Canvas.hpp"

int main()
{
    qboost::Canvas p(35,35,{0,150,0}); // Dark green filled canvas
    p.Render(); // Renders the canvas in the current cursor position
}
```
where: `qboost::Canvas exampleCanvas(width, height, backgroundColor)`.
You can also make transparent canvas by replacing `backgroundColor` with `CanvasTransparent`.

Then, we render the canvas directly on the console by calling `Render()`.
It will show this:

<img width="1919" height="1029" alt="image" src="https://github.com/user-attachments/assets/82cfc208-a6d0-4bf6-8611-6ce276acda60" />
And we have canvas rendered on the terminal.

#### 1b. Drawing pixels
What you can do with canva is drawing pixels to the canvas data, and then render it.
To draw pixels, we use `exampleCanva.drawPixel(x_coord, y_coord, color)`.
```cpp
#include "include/QBoost/Canvas.hpp"
#include <iostream>

int main()
{
    // defining canvas dimensions
    const int width = 30;
    const int height = 30;

    qboost::Canvas canvas(width, height, qboost::CanvasTransparent);

    // defining properties of the circle
    const double centerX = width / 2.0;
    const double centerY = height / 2.0;
    const double radius = 28.0;
    const double radius_sq = radius * radius; // using squared radius for effeciency

    // define red color
    qboost::misc::rgb red_color = {255, 0, 0};

    // iterate through every pixel in the canva
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // calculation
            double dx = x - centerX;
            double dy = y - centerY;
            
            double distance_sq = dx * dx + dy * dy;

            // check if pixel's distance is in the circle
            if (distance_sq <= radius_sq) {
                canvas.drawPixel(x, y, red_color); // draw pixel in it
            }
        }
    }

    // when done its ready to render
    canvas.Render();
    
    std::cout << "\nPress Enter to exit..."; // wait user input
    std::cin.get();
}
```
<img width="560" height="541" alt="image" src="https://github.com/user-attachments/assets/c496bf0e-46c7-42d3-87f5-7800df009900" />


This is what you get with drawing pixels. you can also erase pixels by replacing `color` with `CanvasTransparent`.
