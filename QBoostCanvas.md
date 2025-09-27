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

## 2. Rendering for animated canvas
We can use `RenderAt(cursor_x_coord, cursor_y_coord)` function inside our canvas to render the canvas.

We will use the rainbow traingle example in OpenGL.
```cpp
#include <bits/stdc++.h> // Im lazy to include so with gcc i use bits/stdc++.h
#include "../include/QBoost/Canvas.hpp"

// helper struct to calculate
struct Vertex {
    double x, y, z;
    qboost::misc::rgb color;
};

// helper function to calculate
auto barycentric(const Vertex& p1, const Vertex& p2, const Vertex& p3, int px, int py) {
    struct { double w1, w2, w3; } weights;

    double den = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
    if (std::abs(den) < 1e-5) {
        weights.w1 = weights.w2 = weights.w3 = -1.0;
        return weights;
    }
    
    weights.w1 = ((p2.y - p3.y) * (px - p3.x) + (p3.x - p2.x) * (py - p3.y)) / den;
    weights.w2 = ((p3.y - p1.y) * (px - p3.x) + (p1.x - p3.x) * (py - p3.y)) / den;
    weights.w3 = 1.0 - weights.w1 - weights.w2;

    return weights;
}

int main() {
    const int width = 300, height = 300; // canvas width & height
    
    qboost::Canvas canvas(width, height, {0, 0, 0}); // making canvas
    std::vector<std::vector<double>> z_buffer(height, std::vector<double>(width, 0.0));

    const double centerX = width / 2.0;
    const double centerY = height / 2.0;
    const double radius = 100.0;

    Vertex initial_vertices[3] = {
        {0, -radius, 0, {255, 0, 0}},
        {-radius * 0.866, radius * 0.5, 0, {0, 255, 0}},
        {radius * 0.866, radius * 0.5, 0, {0, 0, 255}}
    };

    double angle = 0.0;
    const double rotation_speed = 0.05;

    qboost::CanvasMode(true); // Entering canvas mode to render animations, or more technologically switch to alternate buffer

    while (true) { // this would repeat forever
        if (qboost::TerminalResize()) qboost::ResetScreen(); // This line is important for every animated canvas as it will prevent color bleed glitch.
        canvas.fillCanvas({0, 0, 0}); // filling canvas with black
        //! calculation ahead vvv
        for (int y = 0; y < height; ++y) {
            std::fill(z_buffer[y].begin(), z_buffer[y].end(), std::numeric_limits<double>::max());
        }

        angle += rotation_speed;
        double cosA = cos(angle), sinA = sin(angle);

        Vertex rotated_vertices[3];
        for (int i = 0; i < 3; ++i) {
            double rx = initial_vertices[i].x * cosA - initial_vertices[i].y * sinA;
            double ry = initial_vertices[i].x * sinA + initial_vertices[i].y * cosA;
            rotated_vertices[i] = {rx + centerX, ry + centerY, 0, initial_vertices[i].color};
        }
        
        int minX = std::max(0, (int)std::floor(std::min({rotated_vertices[0].x, rotated_vertices[1].x, rotated_vertices[2].x})));
        int maxX = std::min(width - 1, (int)std::ceil(std::max({rotated_vertices[0].x, rotated_vertices[1].x, rotated_vertices[2].x})));
        int minY = std::max(0, (int)std::floor(std::min({rotated_vertices[0].y, rotated_vertices[1].y, rotated_vertices[2].y})));
        int maxY = std::min(height - 1, (int)std::ceil(std::max({rotated_vertices[0].y, rotated_vertices[1].y, rotated_vertices[2].y})));

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                auto w = barycentric(rotated_vertices[0], rotated_vertices[1], rotated_vertices[2], x, y);
                if (w.w1 >= -1e-6 && w.w2 >= -1e-6 && w.w3 >= -1e-6) {
                    double z = w.w1 * rotated_vertices[0].z + w.w2 * rotated_vertices[1].z + w.w3 * rotated_vertices[2].z;
                    if (z < z_buffer[y][x]) {
                        z_buffer[y][x] = z;
                        int r = std::max(0, std::min(255, (int)(w.w1 * rotated_vertices[0].color.r + w.w2 * rotated_vertices[1].color.r + w.w3 * rotated_vertices[2].color.r)));
                        int g = std::max(0, std::min(255, (int)(w.w1 * rotated_vertices[0].color.g + w.w2 * rotated_vertices[1].color.g + w.w3 * rotated_vertices[2].color.g)));
                        int b = std::max(0, std::min(255, (int)(w.w1 * rotated_vertices[0].color.b + w.w2 * rotated_vertices[1].color.b + w.w3 * rotated_vertices[2].color.b)));
                        canvas.drawPixel(x, y, {r, g, b});
                    }
                }
            }
        }
        //! calculation done ^^^
        canvas.RenderAt(1, 1); // Render the canvas
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Adding a delay so it won't use all CPU usage
    }

    qboost::CanvasMode(false); // turning off canvas mode or technologically switch to main buffer
}
```


This is the result:
<img width="1919" height="1028" alt="image" src="https://github.com/user-attachments/assets/bc11ae9f-2100-4f47-a7e7-4565db5434b4" />


Because of some limitations to view this animation copy and paste this in your code.
As you can see this make the rainbow traingle in the OpenGL examples.

## 3. Canvas information
`Canvas.width` The canvas width.
`Canvas.height` The canvas height.
`Canvas.colormap` The canvas's pixel color data (`Canvas.colormap[y_coord][x_coord]`)
`Canvas(long long w, long long h, qboost::misc::rgb cr)` The default constructor for canvas. It will create an canvas with `width=w,height=h,background/color=cr`
`Canvas.drawPixel(long long x, long long y, qboost::misc::rgb colr)` Draws an pixel into the Canvas at `(x,y)` with `color=colr`.
`Canvas.fillCanvas(qboost::misc::rgb t)` Fills the canvas with an solid color `t`.
`Canvas.RenderAt(long long cx, long long cy)` Renders the canvas at `(cx,cy)`. it is primarily used for animated canvas.
`Canvas.Render()` Renders the canvas at the current cursor position.
## 4. Other information
`qboost::CanvasTransparent` Transparent color for canvas.
`qboost::CanvasMode(bool a)` Enters the alternate buffer session/Canvas session, mainly used for animating, as this disables scrolling. To exit simply set `a=false`.
`qboost::TerminalResize()` Returns an bool for which checks if the terminal is resized or not. This is the most improtant at animated canvases as it allows you to fix bugs like color bleed.
`qboost::ResetScreen()` Clears the screen.

