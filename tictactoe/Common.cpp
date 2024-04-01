#include "Common.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Mix_Chunk* gChunk = NULL;

MenuType menutype = STARTMENU;

bool Init() {
	if (SDL_INIT_EVERYTHING < 0) return false;

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return false;

	if (TTF_Init() < 0) return false;

	gWindow = SDL_CreateWindow("tictactoe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gWindow) return false;

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!gRenderer) return false;

	return true;

}



void RenderImage(std::string path, SDL_Rect rect) {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface) {
		std::cout << "render error : " << SDL_GetError() << std::endl;
		return;
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (!texture) {
		std::cout << SDL_GetError() << " ";
		return;
	}

	SDL_FreeSurface(surface);

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
}


bool CheckClick(SDL_Rect rect, int x, int y) {
	return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}


void Close() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;


	Mix_FreeChunk(gChunk);
	gChunk = NULL;
}


