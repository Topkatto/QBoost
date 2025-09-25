#include <processenv.h>
#include <windows.h>
#include <consoleapi2.h>
#include <iostream>
#include <winnls.h>

namespace QBoostConsole
{
    const char LineBreak = '\n';
    inline void Output() {}
    template <typename... Args, typename T>
    inline void Output(T x, Args... t)
    {
        std::cout << x;
        Output(t...);
    }
    inline void Input() {}
    template <typename... Args, typename T>
    inline void Input(T x, Args... t)
    {
        std::cin << x;
        Input(t...);
    }
    inline void ToggleANSI(bool enable)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error getting standard output handle." << LineBreak;
            return;
        }
        DWORD dwMode = 0;
        if (!GetConsoleMode(hConsole, &dwMode))
        {
            std::cerr << "Error getting console mode." << LineBreak;
            return;
        }
        if (enable)
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        }
        else
        {
            dwMode &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        }

        if (!SetConsoleMode(hConsole, dwMode))
        {
            std::cerr << "Error setting console mode." << LineBreak;
        }
    }
    inline void SetConsoleEncodingUTF8()
    {
        SetConsoleOutputCP(CP_UTF8);
    }
    inline void TieInout()
    {
        std::cin.tie(&std::cout);
    }

    inline void UntieInout()
    {
        std::cin.tie(NULL);
    }

    inline void IosBaseSyncWithStdio(bool t)
    {
        std::ios_base::sync_with_stdio(t);
    }
}

namespace QBoostANSI
{
    inline std::string TextColorForeBack(int __FOREGROUND_COLOR, int __BACKGROUND_COLOR)
    {
        return "\033[38;5;" + std::to_string(__FOREGROUND_COLOR)
                  + ";48;5;" + std::to_string(__BACKGROUND_COLOR) + "m";
    }
    inline std::string TextColorFore(int __FOREGROUND_COLOR)
    {
        return "\033[38;5;" + std::to_string(__FOREGROUND_COLOR) + "m";
    }
    inline std::string TextColorBack(int __BACKGROUND_COLOR)
    {
        return "\033[48;5;" + std::to_string(__BACKGROUND_COLOR) + "m";
    }
    const std::string Bold = "\033[1m";
    const std::string Italic = "\033[3m";
    const std::string DisableLineWrap = "\033[?7l";
    const std::string EnableLineWrap = "\033[?7h";
    const std::string Underline = "\033[4m";
    const std::string Strikethrough = "\033[9m";
    const std::string Reset = "\033[0m";
    const std::string Inverse = "\033[7m";
    const std::string Hidden = "\033[8m";
    const std::string Faint = "\033[2m";
    const std::string DoubleUnderline = "\033[21m";
    const std::string Overline = "\033[53m";
    const std::string Fraktur = "\033[20m";
    inline std::string MoveCursor(int row, int col) { return "\033[" + std::to_string(row) + ";" + std::to_string(col) + "H"; }
    inline void MoveCursorFixed(int x, int y) {
        x++;
        y++;
        COORD pos = { (SHORT)x, (SHORT)y };
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, pos);
    }
    inline std::string ClearScreen(bool keepCursor = false) {return (keepCursor ? "\033[2J\033[3J" : "\033[2J\033[H\033[3J"); }
    const std::string SaveCursorPos = "\033[s";
    const std::string LoadCursorPos = "\033[u";

    inline std::string CursorMoveLeft(int n = 1) { return "\033[" + std::to_string(n) + "D"; }
    inline std::string CursorMoveRight(int n = 1){ return "\033[" + std::to_string(n) + "C"; }
    inline std::string CursorMoveUp(int n = 1)   { return "\033[" + std::to_string(n) + "A"; }
    inline std::string CursorMoveDown(int n = 1) { return "\033[" + std::to_string(n) + "B"; }

    inline std::string CursorVisibility(bool visible = true) { return (!visible ? "\033[?25l" : "\033[?25h"); }
    const std::string Beep  ="\a";
    inline std::string SetForegroundColorRGB(int r, int g, int b) {
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }
    inline std::string SetBackgroundColorRGB(int r, int g, int b) {
        return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }
    const std::string ClearToEndOfScreen  ="\033[0J";
    const std::string ClearToStartOfScreen  ="\033[1J";
    const std::string ClearToEndOfLine ="\033[0K";
    const std::string ClearToStartOfLine = "\033[1K";
    const std::string EraseLine  ="\033[2K";
    const std::string EraseLineFromEnd = "\033[0K";
    const std::string EraseLineToStart = "\033[1K";
    const std::string UseAltBuffer = "\033[?1049h";
    const std::string UseMainBuffer = "\033[?1049l";
    const std::string ReportCursorPosition = "\033[6n";
    inline std::string MoveToColumn(int col) { return "\033[" + std::to_string(col) + "G"; }
    inline std::string ScrollUp(int n = 1)   { return "\033[" + std::to_string(n) + "S"; }
    inline std::string ScrollDown(int n = 1) { return "\033[" + std::to_string(n) + "T"; }
}