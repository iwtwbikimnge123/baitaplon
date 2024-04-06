#include "menu2.h"

void RenderMenu2(Text returnMenu1, Text goToTictactoe, Text goTo5x5, Text goTo15x15, SDL_Color colorreturn, SDL_Color colortictactoe, SDL_Color color5x5, SDL_Color color15x15) {
	if (!returnMenu1.OpenFont(30, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	if (!goToTictactoe.OpenFont(50, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	if (!goTo5x5.OpenFont(50, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}

	if (!goTo15x15.OpenFont(50, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}

	returnMenu1.SetText("return");
	goToTictactoe.SetText("tic tac toe");
	goTo5x5.SetText("5x5");
	goTo15x15.SetText("15x15");

	returnMenu1.SetColor(colorreturn);
	goToTictactoe.SetColor(colortictactoe);
	goTo5x5.SetColor(color5x5);
	goTo15x15.SetColor(color15x15);

	returnMenu1.RenderText(180, 500);
	goToTictactoe.RenderText(70, 300);
	goTo5x5.RenderText(190, 350);
	goTo15x15.RenderText(160, 400);
}


void CheckClickMenu2(SDL_Event& e, bool& quit, Text returnMenu1, Text goToTictactoe, Text goTo5x5, Text goTo15x15) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) quit = true;

		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (CheckClick(*returnMenu1.GetRect(), e.button.x, e.button.y)) {
				menutype = STARTMENU;
			}
			else if (CheckClick(*goToTictactoe.GetRect(), e.button.x, e.button.y)) menutype = CHOOSETICTACTOE;
			else if (CheckClick(*goTo5x5.GetRect(), e.button.x, e.button.y)) menutype = PLAY5X5;
			else if (CheckClick(*goTo15x15.GetRect(), e.button.x, e.button.y)) menutype = PLAY15X15;
		}
	}
	SDL_RenderPresent(gRenderer);
}