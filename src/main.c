#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

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

int main(int argc, char ** argv)
{
  int errors = 0;
  // Suppress compiler warnings:
  // (void)argc;
  // (void)argv;
  
  // Initialize
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // SDL_INIT_EVERYTHING
  SDL_Window * window = SDL_CreateWindow("SDL2-Template", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          640, 
                                          480,
                                          SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    ++errors;
    printf("SDL_CreateWindow failed. SDL Error: %s\n", SDL_GetError());
  }
  SDL_Renderer * renderer = SDL_CreateRenderer(window, 
                                               -1, 
                                               SDL_RENDERER_ACCELERATED | 
                                               SDL_RENDERER_TARGETTEXTURE);
  if (!renderer)
  {
    ++errors;
    printf("SDL_CreateRenderer failed. SDL Error: %s\n", SDL_GetError());
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
  {
    ++errors;
    printf("Mix_OpenAudio failed. SDL_mixer Error: %s\n", Mix_GetError());
  }
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    ++errors;
    printf("IMG_Init failed. SDL_IMG Error: %s\n", IMG_GetError() );
  }

  // Run-time variables:
  bool live = true;
  uint32_t time_new = 0;
  uint32_t time_old = 0;
  uint32_t time_delay = 16; // 1000ms / 16frames = 62.5fps
  // Draw initial state:
  SDL_Rect background = {0,0,0,0};
  SDL_GetWindowSize(window, &background.w, &background.h);
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderFillRect(renderer, &background);
  
  //BEGIN MAIN LOOP
  while (live == true)
  {
    time_new = SDL_GetTicks();
    if (time_new - time_old > time_delay)
    {
    SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
      SDL_RenderFillRect(renderer, &background);
      SDL_RenderPresent(renderer);
      time_old = time_new;
    }
    // Default events:
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
      if (Event.type == SDL_QUIT ||
          (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE))
      {
        // Default exit method:
        live = 0;
      }
      else if (Event.type == SDL_WINDOWEVENT && 
               Event.window.event == SDL_WINDOWEVENT_RESIZED)
      {
        // Default resize behavior:
        SDL_GetWindowSize(window, &background.w, &background.h);
        SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
        SDL_RenderFillRect(renderer, &background);
      }
    }
  }
  // Memory clean up on exit:
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return errors;
}
