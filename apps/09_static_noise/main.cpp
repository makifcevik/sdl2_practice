#include "main.h"

#include <vector>

int main(int argc, char* argv[]) {
  SDLContext sdl_context;
  if (!sdl_context.Ok()) {
    return 1;
  }

  {  // Smart pointer scope
    // Create window
    std::unique_ptr<SDL_Window, SDLDeleter> window(
        SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WINDOW_WIDTH, WINDOW_HEIGHT, 0));
    if (!window.get()) {
      std::cerr << "Error creating window: " << SDL_GetError() << "\n";
      return 1;
    }

    // Create renderer
    std::unique_ptr<SDL_Renderer, SDLDeleter> renderer(SDL_CreateRenderer(
        window.get(), -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!renderer.get()) {
      std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
      return 1;
    }

    // Create texture
    std::unique_ptr<SDL_Texture, SDLDeleter> texture(SDL_CreateTexture(
        renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH, WINDOW_HEIGHT));
    if (!texture.get()) {
      std::cerr << "Error creating texture: " << SDL_GetError() << "\n";
      return 1;
    }

    // Pixels buffer ram
    std::vector<uint32_t> pixel_buffer(WINDOW_WIDTH * WINDOW_HEIGHT);

    bool is_running = true;
    SDL_Event event;

    while (is_running) {

      // Generate noise
      for (int i = 0; i < pixel_buffer.size(); ++i) {
        uint8_t random_val = rand() % 255;
        uint32_t color =
            (random_val << 24) | (random_val << 16) | (random_val << 8) | 255;
        pixel_buffer[i] = color;
      }

      // GPU side
      void* texture_pixels;
      int pitch;

      // --- LOCK GPU texture to access it with CPU
      SDL_LockTexture(texture.get(), NULL, &texture_pixels, &pitch);
      // Cast the GPU pointer to bytes so we can do math
      uint8_t* dest_ptr = static_cast<uint8_t*>(texture_pixels);
      // Get the pointer to the buffer in ram
      uint32_t* src_ptr = pixel_buffer.data();

      // Copy row by row (from CPU ram buffer to GPU texture)
      for (int row = 0; row < WINDOW_HEIGHT; ++row) {
        uint8_t* dest_row = dest_ptr + (row * pitch);
        uint32_t* src_row = src_ptr + (row * WINDOW_WIDTH);

        memcpy(dest_row, src_row, 4 * WINDOW_WIDTH);  // 4 bytes per pixel
      }
      // --- UNLOCK texture
      SDL_UnlockTexture(texture.get());

      SDL_RenderClear(renderer.get());
      SDL_RenderCopy(renderer.get(), texture.get(), NULL, NULL);
      SDL_RenderPresent(renderer.get());

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          is_running = false;
        }
      }
    }

  }  // End of Smart pointer scope
}