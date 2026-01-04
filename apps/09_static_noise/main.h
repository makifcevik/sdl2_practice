#pragma once

#include <iostream>

#include <SDL.h>

const char* TITLE = "09_static_noise";
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;

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
