#include "Common.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Mix_Music* gMusic = NULL;
Mix_Chunk* gChunk = NULL;
Mix_Chunk* gChunk_toggle = NULL;
Mix_Chunk* gChunk_click = NULL;
Mix_Chunk* gChunk_over = NULL;

MenuType menuType = STARTMENU;

bool Init() {
	if (SDL_INIT_EVERYTHING < 0) return false;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << Mix_GetError();
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return false;

	if (TTF_Init() < 0) return false;

	gWindow = SDL_CreateWindow("tictactoe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gWindow) return false;

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!gRenderer) return false;

	gChunk = Mix_LoadWAV("img/click.wav");
	if (!gChunk) {
		std::cout << Mix_GetError();
		return false;
	}

	gChunk_toggle = Mix_LoadWAV("img/toggle.wav");
	if (!gChunk_toggle) {
		std::cout << Mix_GetError();
		return false;
	}

	gChunk_click = Mix_LoadWAV("img/pick.wav");
	if (!gChunk_click) {
		std::cout << Mix_GetError();
		return false;
	}

	gChunk_over = Mix_LoadWAV("img/gameover.wav");
	if (!gChunk_over) {
		std::cout << Mix_GetError();
		return false;
	}

	gMusic = Mix_LoadMUS("img/music.wav");
	if (!gMusic) {
		std::cout << Mix_GetError();
		return false;
	}

	Mix_PlayMusic(gMusic, -1);

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

	Mix_FreeChunk(gChunk_toggle);
	gChunk_toggle = NULL;

	Mix_FreeChunk(gChunk_click);
	gChunk_toggle = NULL;

	Mix_FreeChunk(gChunk_over);
	gChunk_toggle = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


