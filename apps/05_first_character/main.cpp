#include <random>

#include "color.h"
#include "main.h"

int main(int argc, char* argv[]) {

  SDLContext sdl_context;
  if (!sdl_context.Ok()) {
    return 1;
  }

  {  // Scope for smart pointer auto cleanup (RAII)
    std::unique_ptr<SDL_Window, SDLDeleter> window(
        SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WIDTH, HEIGHT, 0));
    if (!window.get()) {
      std::cerr << "Error creating window: " << SDL_GetError() << "\n";
      return 1;
    }

    std::unique_ptr<SDL_Renderer, SDLDeleter> renderer(SDL_CreateRenderer(
        window.get(), -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!renderer.get()) {
      std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
      return 1;
    }

    bool is_running = true;
    SDL_Event event;
    SDL_Rect player{POS_X - 20, POS_Y - 20, 40, 40};

    const auto colors = Palette::GetAll();
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<> dist(0, colors.size() - 1);
    int color_index = dist(gen);

    while (is_running) {

      // Clean canvas
      Palette::SetRendererDrawColor(renderer.get(), Palette::Black);
      SDL_RenderClear(renderer.get());

      // Paint player
      Palette::SetRendererDrawColor(renderer.get(), colors[color_index]);
      SDL_RenderFillRect(renderer.get(), &player);

      // Present layer
      SDL_RenderPresent(renderer.get());

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          is_running = false;
        } else if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_SPACE) {
            color_index = dist(gen);
          }
        }
      }  // PollEvent loop ends

      // KEYBOARD STATE (Continuous Movement)
      // Get the pointer to the array of key states
      const uint8_t* current_key_states = SDL_GetKeyboardState(NULL);

      if (current_key_states[SDL_SCANCODE_UP]) {
        player.y -= SPEED;
      }
      if (current_key_states[SDL_SCANCODE_DOWN]) {
        player.y += SPEED;
      }
      if (current_key_states[SDL_SCANCODE_LEFT]) {
        player.x -= SPEED;
      }
      if (current_key_states[SDL_SCANCODE_RIGHT]) {
        player.x += SPEED;
      }

    }  // is_running loop ends
  }  // RAII scope ends
}