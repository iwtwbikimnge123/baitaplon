
#pragma once
#include "Common.h"
class Text {
public:
	Text();
	~Text();
	void SetText(const std::string& t) {
		text = t;
	}

	void SetColor(const SDL_Color& c) {
		color = c;
	}

	bool OpenFont(int fonsize, std::string path);

	void RenderText(int x, int y);


	SDL_Rect* GetRect() { return rect; }
private:
	std::string text;
	TTF_Font* font;
	SDL_Color color;
	SDL_Rect* rect;
};
