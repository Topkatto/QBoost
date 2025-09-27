#pragma once

#include "ConsoleExtended.hpp"
#include "Structs.hpp"
#include <bits/stdc++.h>


namespace qboost
{
    inline void CanvasMode(bool a)
    {
        QBoostConsole::Output(a ? QBoostANSI::UseAltBuffer : QBoostANSI::UseMainBuffer);
    }

    inline misc::rgb CanvasTransparent = {-1, -1, -1};

    struct Canvas
    {
        long long width, height;
        std::vector<std::vector<misc::rgb>> colormap;

        Canvas(long long w, long long h, misc::rgb color)
        {
            width = w;
            height = h;
            colormap.assign(height, std::vector<misc::rgb>(width, color));
        }

        void drawPixel(long long x, long long y, misc::rgb color)
        {
            if (x < 0 || y < 0 || x >= width || y >= height) return;
            if (color.r == -1 && color.g == -1 && color.b == -1) return;
            colormap[y][x] = color;
        }

        void clearCanvas()
        {
            for (long long i = 0; i < height; i++)
            {
                std::fill((*this).colormap[i].begin(), (*this).colormap[i].end(), CanvasTransparent);
            }
        }

        void fillCanvas(misc::rgb t)
        {
            for (long long i = 0; i < height; i++)
            {
                std::fill((*this).colormap[i].begin(), (*this).colormap[i].end(), t);
            }
        }
        
        /**
        * Renders the canvas at (cx,cy).
        * Best for animations.
        */
        void RenderAt(long long cx, long long cy)
        {
            std::ostringstream output;
            output << QBoostANSI::MoveCursor(cx, cy) << QBoostANSI::CursorVisibility(false) << QBoostANSI::DisableLineWrap;

            static std::string spaces(3000, ' ');

            for (long long y = 0; y < height; ++y)
            {
                std::ostringstream rowbuf;
                misc::rgb last_color = {-2, -2, -2};
                long long x = 0;
                while (x < width)
                {
                    misc::rgb cc = colormap[y][x];
                    if (cc.r == -1 && cc.g == -1 && cc.b == -1) {
                        if (!(last_color.r == -2 && last_color.g == -2 && last_color.b == -2)) {
                            rowbuf << QBoostANSI::Reset;
                            last_color = {-2, -2, -2};
                        }
                        rowbuf << "  ";
                        x++;
                        continue;
                    }
                    long long run = 1;
                    while (x + run < width && colormap[y][x + run] == cc && !(colormap[y][x + run].r == -1 && colormap[y][x + run].g == -1 && colormap[y][x + run].b == -1)) {
                        run++;
                    }
                    if (!(cc == last_color)) {
                        rowbuf << QBoostANSI::SetBackgroundColorRGB(cc.r, cc.g, cc.b);
                        last_color = cc;
                    }
                    long long remaining = run;
                    while (remaining > 0) {
                        long long chunk = std::min((long long)(spaces.size() / 2), remaining);
                        rowbuf.write(spaces.c_str(), chunk * 2);
                        remaining -= chunk;
                    }
                    x += run;
                }
                rowbuf << QBoostANSI::Reset;
                output << rowbuf.str() << QBoostConsole::LineBreak;
            }

            output << QBoostANSI::Reset;
            output << QBoostANSI::CursorVisibility(true) << QBoostANSI::EnableLineWrap;
            QBoostConsole::Output(output.str());
        }   

        /**
        * Renders the canvas directly into the main buffer without positioning.
        * This is a simpler version of RenderAt.
        */
        void Render()
        {
            std::ostringstream output;
            output << QBoostANSI::CursorVisibility(false);
            output << QBoostANSI::DisableLineWrap;
            static std::string spaces(3000, ' ');
            for (long long y = 0; y < height; ++y)
            {
                std::ostringstream rowbuf;
                misc::rgb last_color = {-2, -2, -2};
                long long x = 0;
                while (x < width)
                {
                    misc::rgb cc = colormap[y][x];
                    if (cc.r == -1 && cc.g == -1 && cc.b == -1) {
                        if (!(last_color.r == -2 && last_color.g == -2 && last_color.b == -2)) {
                            rowbuf << QBoostANSI::Reset;
                            last_color = {-2, -2, -2};
                        }
                        rowbuf << "  ";
                        x++;
                        continue;
                    }
                    long long run = 1;
                    while (x + run < width && colormap[y][x + run] == cc && !(colormap[y][x + run].r == -1 && colormap[y][x + run].g == -1 && colormap[y][x + run].b == -1)) {
                        run++;
                    }
                    if (!(cc == last_color)) {
                        rowbuf << QBoostANSI::SetBackgroundColorRGB(cc.r, cc.g, cc.b);
                        last_color = cc;
                    }
                    long long remaining = run;
                    while (remaining > 0) {
                        long long chunk = std::min((long long)(spaces.size() / 2), remaining);
                        rowbuf.write(spaces.c_str(), chunk * 2);
                        remaining -= chunk;
                    }
                    x += run;
                }
                rowbuf << QBoostANSI::Reset;
                output << rowbuf.str() << QBoostConsole::LineBreak;
            }
            output << QBoostANSI::Reset;
            output << QBoostANSI::CursorVisibility(true) << QBoostANSI::EnableLineWrap;
            QBoostConsole::Output(output.str());
        }    
    };
}
