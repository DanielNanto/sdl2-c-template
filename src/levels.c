#include "levels.h"

SDL_Texture * loadTexture(char * path, SDL_Renderer * renderer){
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if(loadedSurface == NULL){
		printf( "Failed to load image %s. SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else{
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == NULL){
			printf("Failed to create texture from %s. SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
// jun-image.h
