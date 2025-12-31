#include <iostream>

#include <SDL.h>

int main(int argc, char* argv[]) {
  // 1. Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed initializing SDL:" << SDL_GetError() << "\n";
    return 1;
  }

  // 2. Create Window
  // Arguments: Title, x, y, width, height, flags
  SDL_Window* window =
      SDL_CreateWindow("01_skeleton", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);

  if (!window) {
    std::cerr << "Failed to create window: " << SDL_GetError() << "\n";
    return 1;
  }

  // 3. The Game Loop
  bool is_running = true;
  SDL_Event event;

  while (is_running) {
    //std::cout << "." << std::flush;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_running = false;
      }
    }
    SDL_Delay(16);
  }

  // 4. Cleanup
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}