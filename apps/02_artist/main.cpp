#include <iostream>

#include <SDL.h>

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
    return 1;
  }

  SDL_Window* window =
      SDL_CreateWindow("02_artist", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::cerr << "Error creating window: " << SDL_GetError() << "\n";
    return 1;
  }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
  }

  bool is_running = true;
  SDL_Event event;

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_running = false;
      }
    }  // PollEvent while ends

    // Set background color to black
    // You must explicitly set the color for the background before clearing,
    // and then set the color for the rectangle before drawing it.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear screen
    SDL_RenderClear(renderer);

    // Set color to red
    SDL_SetRenderDrawColor(renderer, 180, 0, 0, 255);

    // Create SDL Rectangle (x, y, w, h)
    SDL_Rect rect = {100, 100, 50, 50};
    /*rect.x = 100;
    rect.y = 100;
    rect.w = 50;
    rect.h = 50;*/

    // SDL_RenderFillRect fills it. SDL_RenderDrawRect makes an outline.
    SDL_RenderFillRect(renderer, &rect);

    // Present the back buffer to the screen
    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }  // is_running while ends

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}