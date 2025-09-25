#include "ConsoleExtended.hpp"
#include "Structs.hpp"
#include <bits/stdc++.h>

namespace qboost
{
    inline void CanvasMode(bool a)
    {
        QBoostConsole::Output(a ? QBoostANSI::DisableLineWrap : QBoostANSI::EnableLineWrap);
        QBoostConsole::Output((a ? QBoostANSI::UseAltBuffer : QBoostANSI::UseMainBuffer));
    }
    inline qboost::misc::rgb CanvasTransparent = {-67667,-67667,-67667};
    struct Canvas
    { 
        private:
        qboost::misc::rgb background_color;
        public:
        long long width;
        long long height;
        std::vector<std::vector<qboost::misc::rgb>> colormap;
        void drawPixel(long long x, long long y, qboost::misc::rgb color)
        {
            if (y >= 0 && y < height && x >= 0 && x < width) {
                colormap[y][x] = color;
            }
        }
        Canvas(long long w, long long h, qboost::misc::rgb color)
        {
            width = w;
            height = h;
            background_color = color;
            colormap.resize(height, std::vector<qboost::misc::rgb>(width, color));
        }
        //**
        // Renders the canvas (optimized possibl) at the cursor position (in screen).
        // ! For best possible results without glitches please enable CanvasMode(true).
        //  */
        void RenderAt(long long cx, long long cy) {
            std::string output;
            output.reserve(width * height * 2 + height * 64);

            output += QBoostANSI::MoveCursor(cx, cy);
            output += QBoostANSI::CursorVisibility(false);

            static std::string spaces(3000, ' ');

            for (long long y = 0; y < height; y++) {
                misc::rgb last_color = {-1, -1, -1};
                long long x = 0;

                while (x < width) {
                    misc::rgb cc = colormap[y][x];
                    long long run = 1;
                    while (x + run < width && colormap[y][x + run] == cc) run++;

                    if (cc == CanvasTransparent) {
                        output += QBoostANSI::Reset;
                        long long remaining = run;
                        while (remaining > 0) {
                            long long _v_chunk = std::min((long long)(spaces.size() / 2), remaining);
                            output.append(spaces.c_str(), _v_chunk * 2);
                            remaining -= _v_chunk;
                        }
                        last_color = {-1, -1, -1};
                    } else {
                        if (!(cc == last_color)) {
                            output += QBoostANSI::SetBackgroundColorRGB(cc.r, cc.g, cc.b);
                            last_color = cc;
                        }
                        long long remaining = run;
                        while (remaining > 0) {
                            long long _v_chunk = std::min((long long)(spaces.size() / 2), remaining);
                            output.append(spaces.c_str(), _v_chunk * 2);
                            remaining -= _v_chunk;
                        }
                    }

                    x += run;
                }

                output += QBoostANSI::Reset;
                output += QBoostANSI::ClearToEndOfLine;
                output += QBoostConsole::LineBreak;
            }


            output += QBoostANSI::Reset;
            output += QBoostANSI::ClearToEndOfLine;
            output += QBoostANSI::CursorVisibility(true);
            QBoostConsole::Output(output);
        }

    };

    inline void clearCanvasAt(Canvas& colormap, int cursorx, int cursory)
    {
        std::stringstream ss;
        ss << QBoostANSI::CursorVisibility(false) << QBoostANSI::MoveCursor(1, 1);
        for (int i = 0; i < (long long)colormap.colormap.size(); i++)
        {
            for (int j = 0; j < (long long)colormap.colormap[i].size(); j++)
            {
                ss << "  ";
            }
            ss << QBoostConsole::LineBreak;
        }

        QBoostConsole::Output(ss.str(), QBoostANSI::CursorVisibility(true));
    }
    inline void clearEveryCanvas(Canvas& colormap, int cursorx, int cursory)
    {
        QBoostConsole::Output(QBoostANSI::ClearScreen());
    }
}