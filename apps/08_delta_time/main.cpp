#include "main.h"

#include <memory>
#include <string>

#include <SDL_image.h>

int main(int argc, char* argv[]) {
  SDLContext sdl_context;
  if (!sdl_context.Ok()) {
    return 1;
  }

  {  // Smart pointer scope
    // Create window
    std::unique_ptr<SDL_Window, SDLDeleter> window(
        SDL_CreateWindow("FPS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WINDOW_WIDTH, WINDOW_HEIGHT, 0));
    if (!window.get()) {
      std::cerr << "Error creating window: " << SDL_GetError() << "\n";
      return 1;
    }

    // Create renderer
    std::unique_ptr<SDL_Renderer, SDLDeleter> renderer(SDL_CreateRenderer(
        window.get(), -1,
        SDL_RENDERER_ACCELERATED));
    if (!renderer.get()) {
      std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
      return 1;
    }

    // Load Surface
    std::unique_ptr<SDL_Surface, SDLDeleter> surface(
        IMG_Load("images/trio.png"));
    if (!surface.get()) {
      std::cerr << "Error loading image (surface): " << SDL_GetError() << "\n";
      return 1;
    }

    // Load Texture
    std::unique_ptr<SDL_Texture, SDLDeleter> texture(
        SDL_CreateTextureFromSurface(renderer.get(), surface.get()));
    surface.reset();  // Clean surface;
    if (!texture.get()) {
      std::cerr << "Error loading image (texture): " << SDL_GetError() << "\n";
      return 1;
    }

    float pos_x = 300;
    float pos_y = 200;

    SDL_Rect src_rect{64, 0, 32, 32};
    SDL_Rect dest_rect{pos_x, pos_y, 64, 64};
    double angle{0.0};
    bool rotate_right = true;

    bool is_running = true;
    SDL_Event event;

    uint64_t last_time = SDL_GetTicks64();
    float dt{0.0f};

    int frame_count = 0;
    float fps_timer = 0.0f;

    while (is_running) {
      uint64_t current_time = SDL_GetTicks64();
      uint64_t frame_time = current_time - last_time;
      last_time = current_time;
      dt = static_cast<float>(frame_time) / 1000.0;

      SDL_RenderClear(renderer.get());
      SDL_RenderCopyEx(renderer.get(), texture.get(), &src_rect, &dest_rect,
                       angle, NULL, SDL_FLIP_NONE);
      SDL_RenderPresent(renderer.get());

      angle += rotate_right ? (SPEED * dt) / 2 : (SPEED * -dt) / 2;

      frame_count++;
      fps_timer += dt;

      if (fps_timer > 1) {
        std::string title = "FPS: " + std::to_string(frame_count);
        SDL_SetWindowTitle(window.get(), title.c_str());

        frame_count = 0;
        fps_timer = 0.0f;
      }

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          is_running = false;
        }
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_SPACE) {
            rotate_right = !rotate_right;
          }
        }
      }  // End of PollEvent loop

      // SDL_GetKeyboardState returns a VIEW of its internal array, WE SHOULDN'T DELETE IT
      // Thus, do not attempt to use something like an std::unique_ptr :D
      const uint8_t* current_key_states = SDL_GetKeyboardState(NULL);
      if (current_key_states[SDL_SCANCODE_UP]) {
        if (pos_y > 0) {
          pos_y -= SPEED * dt;
        }
      }
      if (current_key_states[SDL_SCANCODE_DOWN]) {
        if (pos_y < WINDOW_HEIGHT - 64) {
          pos_y += SPEED * dt;
        }
      }
      if (current_key_states[SDL_SCANCODE_LEFT]) {
        if (pos_x > 0) {
          pos_x -= SPEED * dt;
        }
      }
      if (current_key_states[SDL_SCANCODE_RIGHT]) {
        if (pos_x < WINDOW_WIDTH - 64) {
          pos_x += SPEED * dt;
        }
      }

      dest_rect.x = static_cast<int>(pos_x);
      dest_rect.y = static_cast<int>(pos_y);

    }  // End of is_running loop

  }  // End of smart pointer scope
}