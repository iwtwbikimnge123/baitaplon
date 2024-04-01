#pragma once
#include "Common.h"

class Button{
private:
	ButtonType buttonType;
	SDL_Rect rect;
	std::string path;
public:
	Button();
	~Button();

	void SetButtonType(const ButtonType& type) { buttonType = type; }
	void SetPath();
	void SetRect(const int& x, const int& y, const int& w, const int& h);

	SDL_Rect GetRect() { return rect; }

	void RenderButton();


};