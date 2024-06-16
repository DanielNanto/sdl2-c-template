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
  errors = SDL_Init(SDL_INIT_EVERYTHING);
  if (errors != 0)
  {
    printf("SDL_Init failed. SDL Error: %s\n", SDL_GetError());
    ++errors;
  }
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

  // Various example variables:
  SDL_Color Background_color = {0xDA, 0xDA, 0xDA, 0xFF}; // RGBA
  SDL_Rect Background = {0, 0, 0, 0}; // X Y W H
  SDL_GetWindowSize(Window,
                    &Background.w,
                    &Background.h);
  uint32_t time_last_rendered = SDL_GetTicks();
  uint32_t render_delay_ms = 1000 / 120; // 120 FPS
  bool live = (errors == 0) ? true : false;
  // Main loop:
  while (live == true)
  {
    uint32_t runtime_ms = SDL_GetTicks();
    if (unsigned_delta(runtime_ms, time_last_rendered) > render_delay_ms)
    {
      SDL_SetRenderDrawColor(Renderer, 
                             Background_color.r, 
                             Background_color.g, 
                             Background_color.b, 
                             Background_color.a);
      SDL_RenderFillRect(Renderer, &Background);
      SDL_RenderPresent(Renderer);
      time_last_rendered = runtime_ms;
    }
    // Example events:
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
      // Exit event:
      if (Event.type == SDL_QUIT ||
          (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE))
      {
        printf("Exiting...\n");
        live = false;
      }
      // Resize event:
      else if (Event.type == SDL_WINDOWEVENT && 
               Event.window.event == SDL_WINDOWEVENT_RESIZED)
      {
        printf("Resizing SDL window...\n");
        SDL_GetWindowSize(Window,
                          &Background.w,
                          &Background.h);
      }
    }
  }
  // Memory clean-up upon exit:
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
  return errors;
}
