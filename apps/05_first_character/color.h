#pragma once

#include <cstdint>

#include <vector>

#include <SDL.h>

struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
};

namespace Palette {

static inline void SetRendererDrawColor(SDL_Renderer* renderer, Color color) {
  SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue,
                         color.alpha);
}

// --- Grayscale ---
constexpr Color White = {255, 255, 255, 255};
constexpr Color Silver = {189, 195, 199, 255};    // Light Gray
constexpr Color Concrete = {149, 165, 166, 255};  // Gray
constexpr Color Asphalt = {52, 73, 94, 255};      // Dark Blue-Gray
constexpr Color Black = {0, 0, 0, 255};

// --- Warm ---
constexpr Color Tomato = {231, 76, 60, 255};      // Bright Red
constexpr Color Brick = {192, 57, 43, 255};       // Dark Red
constexpr Color Carrot = {230, 126, 34, 255};     // Orange
constexpr Color Pumpkin = {211, 84, 0, 255};      // Dark Orange
constexpr Color Sunflower = {241, 196, 15, 255};  // Yellow
constexpr Color Gold = {243, 156, 18, 255};       // Dark Yellow

// --- Cool ---
constexpr Color Turquoise = {26, 188, 156, 255};   // Teal
constexpr Color Emerald = {46, 204, 113, 255};     // Bright Green
constexpr Color Nephritis = {39, 174, 96, 255};    // Dark Green
constexpr Color PeterRiver = {52, 152, 219, 255};  // Bright Blue
constexpr Color BelizeHole = {41, 128, 185, 255};  // Dark Blue
constexpr Color Amethyst = {155, 89, 182, 255};    // Purple
constexpr Color Wisteria = {142, 68, 173, 255};    // Dark Purple

// --- Pastel / Extra ---
constexpr Color Cream = {245, 245, 220, 255};
constexpr Color Mint = {152, 251, 152, 255};
constexpr Color Sky = {135, 206, 235, 255};
constexpr Color Coral = {255, 127, 80, 255};
constexpr Color Lavender = {230, 230, 250, 255};
constexpr Color Salmon = {250, 128, 114, 255};

inline std::vector<Color> GetAll() {
  return {White,   Silver,    Concrete,   Asphalt,    Black,    Tomato,
          Brick,   Carrot,    Pumpkin,    Sunflower,  Gold,     Turquoise,
          Emerald, Nephritis, PeterRiver, BelizeHole, Amethyst, Wisteria,
          Cream,   Mint,      Sky,        Coral,      Lavender, Salmon};
}

}  // namespace Palette