#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

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
  // Suppress compiler warnings:
  (void)argc;
  (void)argv;
  
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
    printf("SDL_CreateWindow failed. SDL Error: %s\n", SDL_GetError());
  }
  SDL_Renderer * renderer = SDL_CreateRenderer(window, 
                                               -1, 
                                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (!renderer)
  {
    printf("SDL_CreateRenderer failed. SDL Error: %s\n", SDL_GetError());
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) 
  {
    printf("Mix_OpenAudio failed. SDL_mixer Error: %s\n", Mix_GetError());
  }
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags))
  {
    printf("IMG_Init failed. SDL_IMG Error: %s\n", IMG_GetError() );
  }
  
  // Variables
  bool live = true;
  uint32_t time_new, time_old;
  uint32_t time_delay = 16; // 62.5fps // Framerate = 1000 / time_delay
  SDL_Rect background = {0,0,0,0};
  SDL_GetWindowSize(window, &background.w, &background.h);
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderFillRect(renderer, &background);
  
  //BEGIN MAIN LOOP
  while (live == true)
  {
    time_new = SDL_GetTicks();
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
      if (Event.type == SDL_QUIT || (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE))
      {
        live = 0; // Exit
      }
      else if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED)
      {
        SDL_GetWindowSize(window, &background.w, &background.h);
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderFillRect(renderer, &background);
      }
    }
    if (time_new - time_old > time_delay)
    {
      SDL_SetRenderDrawColor(renderer,  rand(),  rand(),  rand(), 0xff);
      SDL_RenderFillRect(renderer, &background);
      time_old = time_new;
      SDL_RenderPresent(renderer);
    }
  }
  // Memory clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
