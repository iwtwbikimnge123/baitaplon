#include "text.h"

Text::Text(){
	text = "";
	font = NULL;
	color = { 255, 255, 255, 255 };
	rect = new SDL_Rect();
}

Text::~Text(){
	text = "";
	TTF_CloseFont(font);
	font = NULL;
	rect = NULL;
}

bool Text::OpenFont(int fontsize, std::string path) {
	font = TTF_OpenFont(path.c_str(), fontsize);
	if (!font) return false;

	return true;
}

void Text::RenderText(int x, int y) {
	SDL_Surface* fontSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(gRenderer, fontSurface);

	rect->x = x;
	rect->y = y;
	rect->w = fontSurface->w;
	rect->h = fontSurface->h;


	SDL_FreeSurface(fontSurface);

	SDL_RenderCopy(gRenderer, fontTexture, NULL, rect);
	SDL_DestroyTexture(fontTexture);
}


