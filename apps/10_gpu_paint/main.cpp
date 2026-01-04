#include "main.h"

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

    // Set blending mode to NONE
    SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_NONE);

    std::vector<uint32_t> pixel_buffer(WINDOW_WIDTH * WINDOW_HEIGHT);

    bool is_running = true;
    SDL_Event event;

    while (is_running) {

      int mouse_x, mouse_y;
      uint32_t current_mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

      if (current_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        DrawBrush(pixel_buffer, mouse_x, mouse_y, 0xFFFFFFFF, BRUSH_SIZE);
      }

      void* pixels;
      int pitch;
      SDL_LockTexture(texture.get(), NULL, &pixels, &pitch);

      uint8_t* dest_ptr = static_cast<uint8_t*>(pixels);
      uint32_t* src_ptr = pixel_buffer.data();
      for (int row = 0; row < WINDOW_HEIGHT; ++row) {
        uint8_t* dest_row = dest_ptr + (row * pitch);
        uint32_t* src_row = src_ptr + (row * WINDOW_WIDTH);

        memcpy(dest_row, src_row, 4 * WINDOW_WIDTH);  // 4 bytes per pixel
      }

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

void SetPixel(std::vector<uint32_t>& buffer, int x, int y, uint32_t color) {
  if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
    buffer[y * WINDOW_WIDTH + x] = color;
  }
}
void DrawBrush(std::vector<uint32_t>& buffer, int x, int y, uint32_t color,
               int radius) {
  for (int dy = -radius; dy <= radius; ++dy) {
    for (int dx = -radius; dx <= radius; ++dx) {
      SetPixel(buffer, x + dx, y + dy, color);
    }
  }
}