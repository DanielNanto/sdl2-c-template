// Title:    jdl-template
// Author:   Jun
// Company:  Joonko Art
// Date:     2021.10.08 (ISO 8601)
// Standard: JSF-AV C++ 

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <jdl_global.h>

int main(int argc, char ** argv)
{
  // Supressing compiler warnings - Thanks FD!
  (void)argc;
  (void)argv;
  
  // Initialize
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDL_Window * window = SDL_CreateWindow("SDL2-Template", 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          640, 
                                          480,
                                          SDL_WINDOW_RESIZABLE);
  if(!window){
    fprintf(stderr, "SDL_CreateWindow failed. SDL Error: %s\n", SDL_GetError());
  }
  SDL_Renderer * renderer = SDL_CreateRenderer(window, 
                                                -1, 
                                                SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
  if(!renderer){
    fprintf(stderr, "SDL_CreateRenderer failed. SDL Error: %s\n", SDL_GetError());
  }
  if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
    fprintf(stderr, "Mix_OpenAudio failed. SDL_mixer Error: %s\n", Mix_GetError());
  }
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) ){
    fprintf(stderr, "IMG_Init failed. SDL_IMG Error: %s\n", IMG_GetError() );
  }
  
  // Variables
  bool live = true;
  SDL_Rect background = {0,0,0,0};
  SDL_GetWindowSize(window, &background.w, &background.h);
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderFillRect(renderer, &background);
  
  //BEGIN MAIN LOOP
  while (live == true){
    time_current = SDL_GetTicks();
    // Handling SDL_Events:
    SDL_Event mainEvent;
    while(SDL_PollEvent(&mainEvent)){
      if (mainEvent.type == SDL_QUIT || (mainEvent.type == SDL_KEYDOWN && mainEvent.key.keysym.sym == SDLK_ESCAPE)){
          live = 0; // Exit
      }
      else if (mainEvent.type == SDL_WINDOWEVENT && mainEvent.window.event == SDL_WINDOWEVENT_RESIZED){
          SDL_GetWindowSize(window, &background.w, &background.h);
          SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
          SDL_RenderFillRect(renderer, &background);
      }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(5);// ~Limit refresh~
  }
  // Memory clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
