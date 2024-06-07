#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #ifdef _WIN64
      #include <SDL2/SDL.h>
      #include <SDL2/SDL_image.h>
      #include <SDL2/SDL_mixer.h>
   #endif
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
#include <stdbool.h>

#include "../include/settings.h"

int main(int argc, char ** argv)
{
  int errors = 0;
  // Suppress compiler warnings:
  (void)argc;
  (void)argv;
  
  // Initialize SDL:
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* window = SDL_CreateWindow("sdl2-c-template",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         640,
                                         480,
                                         SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    printf("SDL_CreateWindow failed. SDL Error: %s\n", SDL_GetError());
    ++errors;
  }
  SDL_Renderer* renderer = SDL_CreateRenderer(window, 
                                               -1, 
                                               SDL_RENDERER_ACCELERATED | 
                                               SDL_RENDERER_TARGETTEXTURE);
  if (!renderer)
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

  // Placeholder SDL items:
  SDL_Rect background = 
  {
    .x = 0,
    .y = 0,
    .w = 0,
    .h = 0
  };
  SDL_Color bg_color = 
  {
    .r = 0xDA, 
    .g = 0xDA, 
    .b = 0xDA, 
    .a = 0xFF
  };
  SDL_GetWindowSize(window,
                    &background.w,
                    &background.h);
  
  // Run-time variables:
  bool live = true;
  // Begin main loop:
  while (live == true)
  {
    time_new = SDL_GetTicks();
    if (time_new - time_old > time_delay)
    {
      SDL_SetRenderDrawColor(renderer, 
                              bg_color.r, 
                              bg_color.g, 
                              bg_color.b, 
                              bg_color.a);
      SDL_RenderFillRect(renderer, &background);
      SDL_RenderPresent(renderer);
      time_old = time_new;
    }
    // Default events:
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
      // Default exit method:
      if (Event.type == SDL_QUIT ||
          (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE))
      {
        live = 0;
      }
      // Default resize behavior:
      else if (Event.type == SDL_WINDOWEVENT && 
               Event.window.event == SDL_WINDOWEVENT_RESIZED)
      {
        SDL_GetWindowSize(window, &background.w, &background.h);
      }
    }
  }
  // Memory clean-up upon exit:
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return errors;
}
