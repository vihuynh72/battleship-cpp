#ifndef UI_THEME_H
#define UI_THEME_H

#include <chrono>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace ui {
namespace theme {

inline constexpr const char* RESET = "\033[0m";
inline constexpr const char* BOLD = "\033[1m";
inline constexpr const char* DIM = "\033[2m";
inline constexpr const char* ITALIC = "\033[3m";
inline constexpr const char* FG_WHITE = "\033[97m";
inline constexpr const char* FG_GRAY = "\033[38;5;246m";
inline constexpr const char* FG_BLUE = "\033[38;5;39m";
inline constexpr const char* FG_CYAN = "\033[38;5;45m";
inline constexpr const char* FG_NAVY = "\033[38;5;26m";
inline constexpr const char* FG_GREEN = "\033[38;5;46m";
inline constexpr const char* FG_YELLOW = "\033[38;5;220m";
inline constexpr const char* FG_ORANGE = "\033[38;5;214m";
inline constexpr const char* FG_RED = "\033[38;5;196m";
inline constexpr const char* FG_MAGENTA = "\033[38;5;201m";
inline constexpr const char* FG_PURPLE = "\033[38;5;141m";

inline std::string stylize(const std::string& text, std::initializer_list<const char*> codes) {
    std::string prefix;
    for (const char* code : codes) {
        prefix += code;
    }
    return prefix + text + RESET;
}

inline std::string accent(const std::string& text) {
    return stylize(text, {BOLD, FG_CYAN});
}

inline std::string muted(const std::string& text) {
    return stylize(text, {DIM, FG_GRAY});
}

inline std::string success(const std::string& text) {
    return stylize(text, {BOLD, FG_GREEN});
}

inline std::string warning(const std::string& text) {
    return stylize(text, {BOLD, FG_ORANGE});
}

inline std::string danger(const std::string& text) {
    return stylize(text, {BOLD, FG_RED});
}

inline std::string highlightNumber(int value) {
    return stylize("[" + std::to_string(value) + "]", {BOLD, FG_YELLOW});
}

inline void clearScreen() {
    std::cout << "\033[2J\033[H";
}

inline void slowPrint(const std::string& text, unsigned int delayMs = 12) {
    for (char ch : text) {
        std::cout << ch << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::flush;
}

inline void loadingPulse(const std::string& message = "Deploying fleets", int cycles = 3, unsigned int delayMs = 180) {
    static const std::vector<std::string> frames = {".", "..", "...", ".."};
    for (int i = 0; i < cycles; ++i) {
        for (const auto& frame : frames) {
            std::cout << "\r" << stylize(message + frame + "   ", {BOLD, FG_BLUE}) << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
    }
    std::cout << "\r" << std::string(40, ' ') << "\r";
}

inline void printDivider(char symbol = '=', int width = 40, const char* color = FG_NAVY) {
    if (width < 0) {
        width = 0;
    }
    std::string line(width, symbol);
    std::cout << stylize(line, {color}) << std::endl;
}

inline void printWaveDivider(int width = 48) {
    const std::string pattern = "~^";
    std::string wave;
    for (int i = 0; i < width; ++i) {
        wave += pattern[i % pattern.size()];
    }
    std::cout << stylize(wave, {FG_BLUE}) << std::endl;
}

inline std::string centerText(const std::string& text, int width) {
    if (static_cast<int>(text.size()) >= width) {
        return text;
    }
    int padding = (width - static_cast<int>(text.size())) / 2;
    return std::string(padding, ' ') + text;
}

inline void printSplash() {
    const std::vector<std::string> logo = {
        " ____        _   _   _           _     _       _ ",
        "|  _ \\      | | | | | |         | |   (_)     | |",
        "| |_) | __ _ | |_| |_| |  __ _   | |_   _  ___ | |_  ___  _ __ ",
        "|  _ < / _` || __| __| | / _` |  | __| | |/ __|| __|/ _ \\| '__|",
        "| |_) | (_| || |_| |_| || (_| |  | |_  | |\\__ \\| |_|  __/| |   ",
        "|____/ \\__,_| \\__|\\__|_| \\__,_|   \\__| |_|/___/ \\__|\\___||_|   "
    };

    const std::vector<const char*> gradient = {
        FG_CYAN, FG_BLUE, FG_NAVY, FG_PURPLE, FG_MAGENTA, FG_CYAN
    };

    for (std::size_t i = 0; i < logo.size(); ++i) {
        const char* color = gradient[i % gradient.size()];
        std::cout << stylize(centerText(logo[i], 58), {BOLD, color}) << std::endl;
    }
    printWaveDivider(58);
}

inline std::string menuOption(int index, const std::string& label, const std::string& detail = "") {
    std::ostringstream stream;
    stream << highlightNumber(index) << " " << stylize(label, {BOLD, FG_WHITE});
    if (!detail.empty()) {
        stream << " " << stylize(detail, {DIM, FG_GRAY});
    }
    return stream.str();
}

inline void printStepHeader(int step, const std::string& label) {
    std::ostringstream stream;
    stream << "Step " << step;
    std::cout << highlightNumber(step) << " " << stylize(label, {BOLD, FG_WHITE}) << std::endl;
}

inline void printVictoryBanner(const std::string& winner) {
    const std::vector<std::string> confetti = {
        "✧ ✦ ✧ ✦ ✧ ✦ ✧ ✦ ✧ ✦",
        "  V I C T O R Y  C L A I M E D  ",
        "✦ ✧ ✦ ✧ ✦ ✧ ✦ ✧ ✦ ✧"
    };

    for (std::size_t i = 0; i < confetti.size(); ++i) {
        const char* color = (i == 1) ? FG_YELLOW : FG_MAGENTA;
        std::cout << stylize(centerText(confetti[i], 48), {BOLD, color}) << std::endl;
    }

    std::cout << stylize(centerText("Commander " + winner + " reigns supreme!", 48), {BOLD, FG_GREEN}) << std::endl;
    printWaveDivider(48);
}

inline std::string healthBar(int current, int maximum, int width = 10) {
    if (maximum <= 0) {
        return stylize("[----------]", {DIM, FG_GRAY});
    }

    if (current < 0) {
        current = 0;
    }
    if (current > maximum) {
        current = maximum;
    }

    int filled = static_cast<int>(static_cast<double>(current) / maximum * width + 0.5);
    if (filled > width) {
        filled = width;
    }

    std::ostringstream stream;
    stream << "[";
    for (int i = 0; i < width; ++i) {
        if (i < filled) {
            stream << stylize("█", {FG_GREEN});
        } else {
            stream << stylize("░", {FG_GRAY});
        }
    }
    stream << stylize("]", {FG_GRAY});

    return stream.str();
}

} // namespace theme
} // namespace ui

#endif // UI_THEME_H
