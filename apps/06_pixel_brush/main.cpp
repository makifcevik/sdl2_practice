#include "main.h"

#include <vector>

#include <SDL.h>

int main(int argc, char* argv[]) {
  SDLContext sdl_context;
  if (!sdl_context.Ok()) {
    return 1;
  }

  {  // RAII Scope
    std::unique_ptr<SDL_Window, SDLDeleter> window(
        SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WIDTH, HEIGHT, 0));
    if (!window.get()) {
      return 1;
    }

    std::unique_ptr<SDL_Renderer, SDLDeleter> renderer(SDL_CreateRenderer(
        window.get(), -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!renderer.get()) {
      return 1;
    }

    bool is_running = true;
    SDL_Event event;

    // VERY inefficent yes! :D
    std::vector<SDL_Rect> rects;
    rects.reserve(16);

    while (is_running) {

      // Clean screen
      SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
      SDL_RenderClear(renderer.get());

      // Track mouse movement & clicks
      int mouse_x, mouse_y;
      uint32_t mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
      // Oh no! Using emplace_back to optimze? (:
      if (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        rects.emplace_back(mouse_x - 8, mouse_y - 8, 16, 16);
      }

      // Draw rects
      SDL_SetRenderDrawColor(renderer.get(), 180, 60, 40, 255);
      // Optimization is crying very hard now!
      for (const auto& rect : rects) {
        SDL_RenderFillRect(renderer.get(), &rect);
      }

      // Draw cursor
      SDL_Rect cursor{mouse_x - 8, mouse_y - 8, 16, 16};
      SDL_SetRenderDrawColor(renderer.get(), 60, 60, 60, 255);
      SDL_RenderFillRect(renderer.get(), &cursor);

      // Present screen
      SDL_RenderPresent(renderer.get());

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          is_running = false;
        }
      }  // PollEvent loop ends

    }  // is_running loop ends
  }  // RAII Scope ends
}