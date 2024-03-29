#include "menu1.h"

void RenderMenu1(Text start, Text out) {
	RenderImage("imageandsound/backgr.png");

	if (!start.OpenFont(50, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	if (!out.OpenFont(50, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}

	start.SetText("start");
	out.SetText("exit");
	start.SetColor(white);
	out.SetColor(white);
	start.RenderText(100, 400);
	out.RenderText(100, 450);
}




