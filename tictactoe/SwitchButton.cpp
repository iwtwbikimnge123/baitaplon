#include "SwitchButton.h"
Button::Button(){
	buttonType = CHOOSEPLAYER_1;
	rect = { 0, 0, 0, 0 };
}
Button::~Button(){}

void Button::SetPath() {
	switch (buttonType) {
	case CHOOSEPLAYER_1:
		path = "img/nut5.png";
		break;
	case CHOOSEPLAYER_2:
		path = "img/nut3.png";
		break;
	case CHOOSESIZE_3x3:
		path = "img/nut8.png";
		break;
	case CHOOSESIZE_15x15:
		path = "img/nut6.png";
		break;
	case BASE:
		path = "img/nut4.png";
		break;
	case START:
		path = "img/start1.png";
		break;
	case SWITCHLEVEL_MEDIUM:
		//them
		break;
	case SWITCHLEVEL_HARD:
		//them
		break;
	}
}

void Button::SetRect(const int& x, const int& y, const int& w, const int& h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Button::RenderButton() {
	RenderImage(path, rect);
}