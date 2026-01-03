#pragma once

#include <iostream>
#include <memory>

#include <SDL.h>

const char* TITLE = "07_bouncing_image";
constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

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

struct Velocity {
  int x;
  int y;
};

void Move(SDL_Rect* rect, Velocity* v) {
  if (rect->x >= WIDTH - rect->w || rect->x <= 0) {
    v->x = -(v->x);
  }
  if (rect->y >= HEIGHT - rect->h || rect->y <= 0) {
    v->y = -(v->y);
  }
  *rect = {rect->x + v->x, rect->y + v->y, rect->w, rect->h};
}