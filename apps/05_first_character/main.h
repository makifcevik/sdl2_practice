#pragma once

#include <iostream>
#include <memory>

#include <SDL.h>

const char* TITLE = "05_first_character";
constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;
constexpr int POS_X = WIDTH / 2;
constexpr int POS_Y = HEIGHT / 2;
constexpr int SPEED = 5;

class SDLContext {
 public:
  SDLContext() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
      ok_ = false;
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
  void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
};