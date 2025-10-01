#pragma once

#include "ConsoleExtended.hpp"
#include "Structs.hpp"
#include <string>
#include <vector>
#include <algorithm>

namespace qboost
{
    // Enables UTF-8 encoding.
    inline void CanvasSetup()
    {
        QBoostConsole::SetConsoleEncodingUTF8();
    }
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
                std::fill(colormap[i].begin(), colormap[i].end(), CanvasTransparent);
            }
        }

        void fillCanvas(misc::rgb t)
        {
            for (long long i = 0; i < height; i++)
            {
                std::fill(colormap[i].begin(), colormap[i].end(), t);
            }
        }

    private:
        void genrenderstr(std::string& outbuf)
        {
            outbuf.reserve(height * (width * 7 + 10));
            const std::string chr = "⠀";

            for (long long y = 0; y < height; ++y)
            {
                const auto& row = colormap[y];
                misc::rgb lcr = {-2, -2, -2};
                long long x = 0;

                while (x < width)
                {
                    misc::rgb cc = row[x];

                    if (cc.r == -1 && cc.g == -1 && cc.b == -1) {
                        if (!(lcr.r == -2 && lcr.g == -2 && lcr.b == -2)) {
                            outbuf.append(QBoostANSI::Reset);
                            lcr = {-2, -2, -2};
                        }
                        outbuf.append("  ");
                        x++;
                        continue;
                    }

                    long long run = 1;
                    while (x + run < width && row[x + run] == cc) {
                        run++;
                    }

                    if (!(cc == lcr)) {
                        outbuf.append(QBoostANSI::SetBackgroundColorRGB(cc.r, cc.g, cc.b));
                        lcr = cc;
                    }
                    for (int i = 0; i < run * 2; ++i)
                    {
                        outbuf.append(chr);
                    }
                    
                    x += run;
                }
                outbuf.append(QBoostANSI::Reset);
                outbuf.append(&QBoostConsole::LineBreak);
            }
        }

    public:
        /**
        * Renders the canvas at (cx,cy). Best for animations.
        */
        void RenderAt(long long cx, long long cy)
        {
            std::string outbuf;
            
            outbuf.append(QBoostANSI::MoveCursor(cx, cy));
            outbuf.append(QBoostANSI::CursorVisibility(false));
            outbuf.append(QBoostANSI::DisableLineWrap);

            genrenderstr(outbuf);

            outbuf.append(QBoostANSI::Reset);
            outbuf.append(QBoostANSI::CursorVisibility(true));
            outbuf.append(QBoostANSI::EnableLineWrap);
            
            QBoostConsole::Output(outbuf);
        }

        /**
        * Renders the canvas directly into the main buffer.
        */
        void Render()
        {
            std::string outbuf;

            outbuf.append(QBoostANSI::CursorVisibility(false));
            outbuf.append(QBoostANSI::DisableLineWrap);

            genrenderstr(outbuf);

            outbuf.append(QBoostANSI::Reset);
            outbuf.append(QBoostANSI::CursorVisibility(true));
            outbuf.append(QBoostANSI::EnableLineWrap);
            
            QBoostConsole::Output(outbuf);
        }
    };
}
