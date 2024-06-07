#if _WIN64 || _WIN32
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #include <SDL2/SDL_mixer.h>
#elif __linux__
  #include <SDL.h>
  #include <SDL_image.h>
  #include <SDL_mixer.h>
#elif __APPLE__
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #include <SDL2/SDL_mixer.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../include/utils.h"

int main(int argc, char** argv)
{
  int errors = 0;
  // Suppress compiler warnings:
  (void)argc;
  (void)argv;
  
  // Initialize SDL:
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* Window = SDL_CreateWindow("sdl2-c-template",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         640,
                                         480,
                                         SDL_WINDOW_RESIZABLE);
  if (!Window)
  {
    printf("SDL_CreateWindow failed. SDL Error: %s\n", SDL_GetError());
    ++errors;
  }
  SDL_Renderer* Renderer = SDL_CreateRenderer(Window, 
                                              -1, 
                                              SDL_RENDERER_ACCELERATED | 
                                              SDL_RENDERER_TARGETTEXTURE);
  if (!Renderer)
  {
    printf("SDL_CreateRenderer failed. SDL Error: %s\n", SDL_GetError());
    ++errors;
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
  {
    printf("Mix_OpenAudio failed. SDL_mixer Error: %s\n", Mix_GetError());
    ++errors;
  }
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    printf("IMG_Init failed. SDL_IMG Error: %s\n", IMG_GetError());
    ++errors;
  }

  // Various default variables:
  SDL_Color bg_color = {0xDA, 0xDA, 0xDA, 0xFF}; // RGBA
  SDL_Rect background = {0, 0, 0, 0}; // X Y W H
  SDL_GetWindowSize(Window,
                    &background.w,
                    &background.h);
  uint32_t runtime_ms = 0;
  uint32_t time_last_rendered = 0;
  uint32_t fps_target = 120;
  uint32_t render_delay_ms = 1000 / fps_target;
  bool live = (errors == 0) ? true : false;
  // Main loop:
  while (live == true)
  {
    runtime_ms = SDL_GetTicks();
    if (unsigned_delta(runtime_ms, time_last_rendered) > render_delay_ms)
    {
      SDL_SetRenderDrawColor(Renderer, 
                              bg_color.r, 
                              bg_color.g, 
                              bg_color.b, 
                              bg_color.a);
      SDL_RenderFillRect(Renderer, &background);
      SDL_RenderPresent(Renderer);
      time_last_rendered = runtime_ms;
    }
    // Default events:
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
      // Default exit method:
      if (Event.type == SDL_QUIT ||
          (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE))
      {
        printf("Exiting...\n");
        live = 0;
      }
      // Default resize behavior:
      else if (Event.type == SDL_WINDOWEVENT && 
               Event.window.event == SDL_WINDOWEVENT_RESIZED)
      {
        SDL_GetWindowSize(Window, &background.w, &background.h);
      }
    }
  }
  // Memory clean-up upon exit:
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
  return errors;
}
