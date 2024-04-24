#include "StartMenu.h"
#include "Text.h"

MenuStart::MenuStart() {
	choosePlayerStatus = 1;
	chooseSizeStatus = 1;

	start.SetButtonType(START);
	start.SetPath();
	start.SetRect(150, 450, 200, 110);

	focusStart.SetButtonType(FOCUSSTART);
	focusStart.SetPath();
	focusStart.SetRect(150, 450, 200, 110);

	speaker.SetButtonType(SPEAKER);
	speaker.SetPath();
	speaker.SetRect(30, 550, 50, 50);

	focusSpeaker.SetButtonType(FOCUS_SPEAKER);
	focusSpeaker.SetPath();
	focusSpeaker.SetRect(30, 550, 50, 50);

	base.SetButtonType(BASE);
	base.SetPath();

	choosePlayer1.SetButtonType(CHOOSEPLAYER_1);
	choosePlayer1.SetPath();
	choosePlayer1.SetRect(105, 375, 145, 50);

	choosePlayer2.SetButtonType(CHOOSEPLAYER_2);
	choosePlayer2.SetPath();
	choosePlayer2.SetRect(250, 375, 145, 50);

	chooseSize3x3.SetButtonType(CHOOSESIZE_3x3);
	chooseSize3x3.SetPath();
	chooseSize3x3.SetRect(105, 305, 145, 50);

	chooseSize15x15.SetButtonType(CHOOSESIZE_15x15);
	chooseSize15x15.SetPath();
	chooseSize15x15.SetRect(250, 305, 145, 50);

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);

	Text player, size;
	player.OpenFont(15, "img/gamecuben.ttf");
	player.SetColor(red);
	player.SetText("mode>");
	player.RenderText(30, 390);

	size.OpenFont(15, "img/gamecuben.ttf");
	size.SetColor(red);
	size.SetText("size>");
	size.RenderText(43, 320);

	SDL_Rect choosePlayerBaseRect = { 100, 370, 300, 60 };
	RenderImage("img/nut2.png", choosePlayerBaseRect);

	SDL_Rect chooseSizeBaseRect = { 100, 300, 300, 60 };
	RenderImage("img/nut7.png", chooseSizeBaseRect);

	SDL_Rect logoRect = { 175, 80, 150, 195 };
	RenderImage("img/CARO.png", logoRect);

	start.RenderButton();
	choosePlayer1.RenderButton();
	chooseSize3x3.RenderButton();
	speaker.RenderButton();
	SDL_RenderPresent(gRenderer);

}
MenuStart::~MenuStart() {

}

void MenuStart::RenderBaseMenu() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
	SDL_RenderClear(gRenderer);

	SDL_Rect choosePlayerBaseRect = { 100, 370, 300, 60 };
	RenderImage("img/nut2.png", choosePlayerBaseRect);

	SDL_Rect chooseSizeBaseRect = { 100, 300, 300, 60 };
	RenderImage("img/nut7.png", chooseSizeBaseRect);

	Text player, size;
	player.OpenFont(15, "img/gamecuben.ttf");
	player.SetColor(red);
	player.SetText("mode>");
	player.RenderText(30, 390);

	size.OpenFont(15, "img/gamecuben.ttf");
	size.SetColor(red);
	size.SetText("size>");
	size.RenderText(43, 320);

	SDL_Rect logoRect = { 175, 80, 150, 195 };
	RenderImage("img/CARO.png", logoRect);

	speaker.RenderButton();
	start.RenderButton();
}

void MenuStart::HandleEvent(SDL_Event& e, bool& quit) {

	
	while (SDL_PollEvent(&e)) {
		
		if (e.type == SDL_QUIT) {
			quit = true;
			return;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (CheckClick(choosePlayer1.GetRect(), e.button.x, e.button.y) && choosePlayerStatus == 2) {

				Mix_PlayChannel(-1, gChunk_toggle, 0);

				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);

				if (chooseSizeStatus == 1) chooseSize3x3.RenderButton();
				else chooseSize15x15.RenderButton();

				int x = choosePlayer2.GetRect().x - 29;

				while (x >= choosePlayer1.GetRect().x) {

					Uint32 frameStart = SDL_GetTicks();
					Uint32 frameTime;

					base.SetRect(x, choosePlayer1.GetRect().y, choosePlayer1.GetRect().w, choosePlayer1.GetRect().h);

					RenderBaseMenu();
					base.RenderButton();

					if (chooseSizeStatus == 1) chooseSize3x3.RenderButton();
					else chooseSize15x15.RenderButton();

					SDL_RenderPresent(gRenderer);
					x -= 29;

					//muot
					frameTime = SDL_GetTicks() - frameStart;
					if (frameDelay > frameTime) {
						SDL_Delay(frameDelay - frameTime);
					}
				}

				if (chooseSizeStatus == 1) chooseSize3x3.RenderButton();
				else chooseSize15x15.RenderButton();

				choosePlayer1.RenderButton();
				SDL_RenderPresent(gRenderer);
				choosePlayerStatus = 1;
			}
			else if (CheckClick(choosePlayer2.GetRect(), e.button.x, e.button.y) && choosePlayerStatus == 1) {

				Mix_PlayChannel(-1, gChunk_toggle, 0);

				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);

				if (chooseSizeStatus == 1) chooseSize3x3.RenderButton();
				else chooseSize15x15.RenderButton();

				int x = choosePlayer1.GetRect().x + 29;

				while (x <= choosePlayer2.GetRect().x) {

					Uint32 frameStart = SDL_GetTicks();
					Uint32 frameTime;

					base.SetRect(x, choosePlayer1.GetRect().y, choosePlayer1.GetRect().w, choosePlayer1.GetRect().h);

					RenderBaseMenu();
					base.RenderButton();

					if (chooseSizeStatus == 1) chooseSize3x3.RenderButton();
					else chooseSize15x15.RenderButton();

					SDL_RenderPresent(gRenderer);
					x += 29;

					//cho muot
					frameTime = SDL_GetTicks() - frameStart;
					if (frameDelay > frameTime) {
						SDL_Delay(frameDelay - frameTime);
					}
				}

				if (chooseSizeStatus == 1) chooseSize3x3.RenderButton();
				else chooseSize15x15.RenderButton();

				choosePlayer2.RenderButton();
				SDL_RenderPresent(gRenderer);
				choosePlayerStatus = 2;
			}
			else if (CheckClick(chooseSize3x3.GetRect(), e.button.x, e.button.y) && chooseSizeStatus == 2) {

				Mix_PlayChannel(-1, gChunk_toggle, 0);

				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);

				if (choosePlayerStatus == 1) choosePlayer1.RenderButton();
				else choosePlayer2.RenderButton();

				int x = chooseSize15x15.GetRect().x - 29;

				while (x >= chooseSize3x3.GetRect().x) {

					Uint32 frameStart = SDL_GetTicks();
					Uint32 frameTime;

					base.SetRect(x, chooseSize3x3.GetRect().y, chooseSize3x3.GetRect().w, chooseSize3x3.GetRect().h);

					RenderBaseMenu();
					base.RenderButton();

					if (choosePlayerStatus == 1) choosePlayer1.RenderButton();
					else choosePlayer2.RenderButton();

					SDL_RenderPresent(gRenderer);
					x -= 29;

					frameTime = SDL_GetTicks() - frameStart;
					if (frameDelay > frameTime) {
						SDL_Delay(frameDelay - frameTime);
					}

				}

				chooseSize3x3.RenderButton();
				SDL_RenderPresent(gRenderer);
				chooseSizeStatus = 1;
			}
			else if (CheckClick(chooseSize15x15.GetRect(), e.button.x, e.button.y) && chooseSizeStatus == 1) {

				Mix_PlayChannel(-1, gChunk_toggle, 0);

				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);

				if (choosePlayerStatus == 1) choosePlayer1.RenderButton();
				else choosePlayer2.RenderButton();

				int x = chooseSize3x3.GetRect().x + 29;

				while (x <= chooseSize15x15.GetRect().x) {

					Uint32 frameStart = SDL_GetTicks();
					Uint32 frameTime;

					base.SetRect(x, chooseSize3x3.GetRect().y, chooseSize3x3.GetRect().w, chooseSize3x3.GetRect().h);

					RenderBaseMenu();
					base.RenderButton();

					if (choosePlayerStatus == 1) choosePlayer1.RenderButton();
					else choosePlayer2.RenderButton();

					SDL_RenderPresent(gRenderer);
					x += 29;

					frameTime = SDL_GetTicks() - frameStart;
					if (frameDelay > frameTime) {
						SDL_Delay(frameDelay - frameTime);
					}
					std::cout << frameTime << std::endl;
				}

				chooseSize15x15.RenderButton();
				SDL_RenderPresent(gRenderer);
				chooseSizeStatus = 2;
			}
			else if (CheckClick(start.GetRect(), e.button.x, e.button.y)) {

				Mix_PlayChannel(-1, gChunk, 0);

				if (chooseSizeStatus == 1 && choosePlayerStatus == 2) menuType = PLAY3x3_2PLAYER;
				else if (chooseSizeStatus == 2 && choosePlayerStatus == 2) menuType = PLAY15X15_2PLAYER;
				else if (chooseSizeStatus == 1 && choosePlayerStatus == 1) menuType = PLAY3X3_WITHBOT;
				else if (chooseSizeStatus == 2 && choosePlayerStatus == 1) menuType = PLAY15X15_WITHBOT;
				return;
			}
			else if (CheckClick(speaker.GetRect(), e.button.x, e.button.y)) {
				
				Mix_PlayChannel(-1, gChunk, 0);

				if (Mix_PausedMusic() == 1) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}
		}
		else if (e.type = SDL_MOUSEMOTION) {
			if (CheckClick(start.GetRect(), e.motion.x, e.motion.y)) {
				focusStart.RenderButton();
				SDL_RenderPresent(gRenderer);
			}
			else if (CheckClick(speaker.GetRect(), e.motion.x, e.motion.y)) {
				focusSpeaker.RenderButton();
				SDL_RenderPresent(gRenderer);
			}

			else {
				speaker.RenderButton();
				start.RenderButton();
				SDL_RenderPresent(gRenderer);
			}
		}
		
	}
}

void MenuStart::RestartMenu() {
	RenderBaseMenu();
	choosePlayer1.RenderButton();
	chooseSize3x3.RenderButton();
	choosePlayerStatus = 1;
	chooseSizeStatus = 1;
	SDL_RenderPresent(gRenderer);
}