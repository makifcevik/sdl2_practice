#include <iostream>
#include <memory>

#include <SDL.h>

struct SDLContext {
  SDLContext() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      throw std::runtime_error(SDL_GetError());
    }
  }
  ~SDLContext() { SDL_Quit(); }
};

struct SDLDeleter {
  void operator()(SDL_Window* p) { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer* p) { SDL_DestroyRenderer(p); }
};

constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

int main(int argc, char* argv[]) {
  try {
    SDLContext sdl_context;

    {  // Scope for smart pointer cleanup
      std::unique_ptr<SDL_Window, SDLDeleter> window(
          SDL_CreateWindow("04_pulsing_square", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0));
      if (!window.get()) {
        throw std::runtime_error(SDL_GetError());
      }

      std::unique_ptr<SDL_Renderer, SDLDeleter> renderer(
          SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
      if (!renderer.get()) {
        throw std::runtime_error(SDL_GetError());
      }

      bool is_running = true;
      SDL_Event event;

      struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        void Increment() {
          r++;
          g += 2;
          b += 3;
        }
      };

      Color color{0, 0, 0, 255};

      while (is_running) {

        // Background
        SDL_SetRenderDrawColor(renderer.get(), 25, 25, 25, 255);
        SDL_RenderClear(renderer.get());

        SDL_Rect rect{(WIDTH / 2) - 40, (HEIGHT / 2) - 40, 80, 80};

        // Fill Rect
        SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b,
                               color.a);
        color.Increment();
        SDL_RenderFillRect(renderer.get(), &rect);

        // Rect Lines
        SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer.get(), &rect);

        // Present
        SDL_RenderPresent(renderer.get());

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            is_running = false;
          }
        }
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}