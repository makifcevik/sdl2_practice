#include <iostream>
#include <memory>

#include <SDL.h>

struct SDLDeleter {
  void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
};

constexpr int WIDTH = 400;
constexpr int HEIGHT = 400;
constexpr int GRID_SIZE = 20;

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
    return 1;
  }

  // We open a scope here so the smart pointers are destroyed BEFORE SDL_Quit()
  {
    std::unique_ptr<SDL_Window, SDLDeleter> window(SDL_CreateWindow(
        "03_grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
        HEIGHT, SDL_WINDOW_RESIZABLE));
    if (!window.get()) {
      std::cerr << "Error creating window: " << SDL_GetError() << "\n";
      return 1;
    }

    std::unique_ptr<SDL_Renderer, SDLDeleter> renderer(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!renderer.get()) {
      std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
      return 1;
    }

    bool is_running = true;
    SDL_Event event;

    while (is_running) {
      SDL_SetRenderDrawColor(renderer.get(), 120, 150, 30, 255);
      SDL_RenderClear(renderer.get());

      SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);

      for (int x = 0; x < WIDTH; x += GRID_SIZE) {
        SDL_RenderDrawLine(renderer.get(), x, 0, x, HEIGHT);
      }
      for (int y = 0; y < HEIGHT; y += GRID_SIZE) {
        SDL_RenderDrawLine(renderer.get(), 0, y, WIDTH, y);
      }

      SDL_RenderPresent(renderer.get());

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          is_running = false;
        }
      }  // End of PollEvent loop

      SDL_Delay(16);
    }  // End of is_running loop

  }  // End of RAII Scope

  SDL_Quit();
}