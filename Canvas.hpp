#include "ConsoleExtended.hpp"
#include "Structs.hpp"
#include <bits/stdc++.h>

namespace qboost {

inline void CanvasMode(bool a) {
    QBoostConsole::Output(a ? QBoostANSI::DisableLineWrap : QBoostANSI::EnableLineWrap);
    QBoostConsole::Output(a ? QBoostANSI::UseAltBuffer : QBoostANSI::UseMainBuffer);
    QBoostConsole::ToggleANSI(a);
}

inline qboost::misc::rgb CanvasTransparent = {-67667, -67667, -67667};

struct Canvas {
private:
    qboost::misc::rgb background_color;

public:
    long long width;
    long long height;
    std::vector<std::vector<qboost::misc::rgb>> colormap;

    void drawPixel(long long x, long long y, qboost::misc::rgb color) {
        if (y >= 0 && y < height && x >= 0 && x < width) {
            colormap[y][x] = color;
        }
    }

    Canvas(long long w, long long h, qboost::misc::rgb color) {
        width = w;
        height = h;
        background_color = color;
        colormap.resize(height, std::vector<qboost::misc::rgb>(width, color));
    }

    void clearCanvas() {
        for (auto& row : colormap)
            std::fill(row.begin(), row.end(), CanvasTransparent);
    }

    void fillCanvas(misc::rgb clr) {
        for (auto& row : colormap)
            std::fill(row.begin(), row.end(), clr);
    }

    // Renders the canvas at the given cursor position
    // For best results, enable CanvasMode(true) before rendering
    void RenderAt(long long cx, long long cy) {
        std::string output;
        output.reserve(width * height * 3);

        output += QBoostANSI::MoveCursor(cx, cy);
        output += QBoostANSI::CursorVisibility(false);

        static std::string spaces(65535, ' ');

        for (long long y = 0; y < height; y++) {
            misc::rgb last_color = {255, 255, 255};

            for (long long x = 0; x < width;) {
                misc::rgb cc = colormap[y][x];
                long long run_start = x;

                while (x + 1 < width && colormap[y][x + 1] == cc)
                    x++;

                long long run_length = x - run_start + 1;

                if (!(cc == last_color)) {
                    if (!(cc == CanvasTransparent))
                    {
                        output += QBoostANSI::SetBackgroundColorRGB(cc.r, cc.g, cc.b);
                        last_color = cc;
                    } else {
                        last_color = CanvasTransparent;
                    }
                }

                while (run_length > 0) {
                    long long chunk = std::min((long long)(spaces.size() / 2), run_length);
                    output.append(spaces, 0, chunk * 2);
                    run_length -= chunk;
                }

                x++;
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

} // namespace qboost
