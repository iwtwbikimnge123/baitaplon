#include "choosetictactoe.h"

void RenderChooseTictactoe(Text  goToTictactoe, Text PlayWithBot, Text Solo) {
	if (!goToTictactoe.OpenFont(50, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	if (!Solo.OpenFont(40, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	if (!PlayWithBot.OpenFont(40, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}

	goToTictactoe.SetText("tic tac toe");
	Solo.SetText("solo");
	PlayWithBot.SetText("play with bot");

	goToTictactoe.SetColor(grey);
	Solo.SetColor(white);
	PlayWithBot.SetColor(white);

	goToTictactoe.RenderText(70, 300);
	Solo.RenderText(190, 370);
	PlayWithBot.RenderText(60, 420);
}

void CheckChooseTictactoe(SDL_Event& e, bool& quit, Text  goToTictactoe, Text PlayWithBot, Text Solo) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) quit = true;
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (CheckClick(*goToTictactoe.GetRect(), e.button.x, e.button.y)) {
				menutype = CHOOSEMAP;
			}
			else if (CheckClick(*Solo.GetRect(), e.button.x, e.button.y)) menutype = PLAYTICTACTOE;
			else if (CheckClick(*PlayWithBot.GetRect(), e.button.x, e.button.y)) quit = true;
		}
	}
	SDL_RenderPresent(gRenderer);
}