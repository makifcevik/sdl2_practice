#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>

const char* TITLE = "10_gpu_paint";
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr int BRUSH_SIZE = 5;

class SDLContext {
 public:
  SDLContext() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      ok_ = false;
      std::cerr << "Could not initialize SDL: " << SDL_GetError() << "\n";
    } else {
      ok_ = true;
    }
  }
  ~SDLContext() noexcept {
    if (ok_) {
      SDL_Quit();
    }
  }

  bool Ok() const { return ok_; }

 private:
  bool ok_;
};

struct SDLDeleter {
  void operator()(SDL_Window* p) { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer* p) { SDL_DestroyRenderer(p); }
  void operator()(SDL_Surface* p) { SDL_FreeSurface(p); }
  void operator()(SDL_Texture* p) { SDL_DestroyTexture(p); }
};

void SetPixel(std::vector<uint32_t>& buffer, int x, int y, uint32_t color);
void DrawBrush(std::vector<uint32_t>& buffer, int x, int y, uint32_t color,
               int radius);