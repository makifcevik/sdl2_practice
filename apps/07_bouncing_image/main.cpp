#include "main.h"

int main(int argc, char* argv[]) {
  SDLContext context;
  if (!context.Ok()) {
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

    SDL_Surface* surface = SDL_LoadBMP("images/trio.bmp");
    if (!surface) {
      std::cerr << "Failed to load surface: " << SDL_GetError() << "\n";
      return 1;
    }
    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(renderer.get(), surface);
    SDL_FreeSurface(surface);

    if (!texture) {
      std::cerr << "Failed to load texture: " << SDL_GetError() << "\n";
      return 1;
    }

    SDL_Rect srcRect{0, 0, 32, 32};
    SDL_Rect destRect{100, 100, 64, 64};

    Velocity velocity = {5, 8};

    bool is_running = true;
    SDL_Event event;

    while (is_running) {

      SDL_RenderClear(renderer.get());

      SDL_RenderCopy(renderer.get(), texture, &srcRect, &destRect);

      Move(&destRect, &velocity);

      SDL_RenderPresent(renderer.get());

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          is_running = false;
        }
      }  // PollEvent loop ends
    }  // is_running loop ends

    SDL_DestroyTexture(texture);

  }  // RAII scope ends
}