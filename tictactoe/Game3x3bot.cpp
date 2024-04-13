#include"Game3x3bot.h"

Game3x3bot::Game3x3bot():Game3x3() {
	gameLevelStatus = 1;
	depth = 0;

	base.SetButtonType(BASE);
	base.SetPath();
	base.SetRect(85, 10, 85, 30);

	chooseLevelMedium.SetButtonType(SWITCHLEVEL_MEDIUM);
	chooseLevelMedium.SetPath();
	chooseLevelMedium.SetRect(300, 15, 85, 35);

	chooseLevelHard.SetButtonType(SWITCHLEVEL_HARD);
	chooseLevelHard.SetPath();
	chooseLevelHard.SetRect(377, 15, 85, 35);
}

int Game3x3bot::minimax(int depth_, bool isBotTurn, int alpha, int beta) {
	if (CheckWinCol() || CheckWinRow() || CheckWinDiag1() || CheckWinDiag2()) {
		if (isBotTurn) return INT_MIN;
		else return INT_MAX;
	}
	else if (CheckTie()) return 0;

	if (depth_ == 0) return value(isBotTurn);

	if (isBotTurn) {
		int res = INT_MIN;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == EMPTY) {
					int tmpX = x;
					int tmpY = y;
					x = j;
					y = i;
					board[i][j] = PLAYER_O;
					int score = minimax(depth_ - 1, false, alpha, beta);
					x = tmpX;
					y = tmpY;
					board[i][j] = EMPTY;
					alpha = std::max(alpha, score);
					if (alpha >= beta) return alpha;
				}
			}
		}
		return alpha;
	}
	else {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == EMPTY) {
					int tmpX = x;
					int tmpY = y;
					x = j;
					y = i;
					board[i][j] = PLAYER_X;
					int score = minimax(depth_ - 1, true, alpha, beta);
					x = tmpX;
					y = tmpY;
					board[i][j] = EMPTY;
					beta = std::min(beta, score);
					if (alpha >= beta) return beta;
				}
			}
		}
		return beta;
	}
}

void Game3x3bot::logic(SDL_Event& e, bool& quit) {
	
	while (menuType != STARTMENU && !quit) {
		if (state == RUNNING_STATE) {
			Uint32 starttime = SDL_GetTicks() / 1000;
			int timer = 45;

			while (!quit && state == RUNNING_STATE && menuType != STARTMENU) {
				std::string displaytime = "00:" + std::to_string(timer);
				Text timetext;
				if (!timetext.OpenFont(15, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				timetext.SetColor(red);
				timetext.SetText(displaytime);

				RenderRunningstate();

				if (player == PLAYER_X) {
					timetext.RenderText(80, 120);
				}
				SDL_RenderPresent(gRenderer);

				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

				if (player == PLAYER_X) {
					HandleEvent(e, quit, timer);
				}
				else if (player == PLAYER_O) {
					int res = INT_MIN;

					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							if (board[i][j] == EMPTY) {
								board[i][j] = PLAYER_O;
								int score = minimax(depth, false, INT_MIN, INT_MAX);
								board[i][j] = EMPTY;
								if (res <= score) {
									res = score;
									x = j;
									y = i;
								}
							}
						}
					}
					board[y][x] = PLAYER_O;
					player = PLAYER_X;
				}
				if (CheckWinCol() || CheckWinRow() || CheckWinDiag1() || CheckWinDiag2()) {
					if (player == PLAYER_O) state = X_WON_STATE;
					else state = O_WON_STATE;
					break;
				}
				else if (CheckTie()) {
					state = TIE_STATE;
					break;
				}

				Uint32 finaltime = SDL_GetTicks() / 1000;
				if (finaltime - starttime >= 1) {
					timer--;
					starttime = SDL_GetTicks() / 1000;
				}

				if (timer == 0) {
					if (player == PLAYER_O) state = O_WON_STATE;
					else state = X_WON_STATE;
					break;
				}
			}
		}

		if (state == X_WON_STATE || state == O_WON_STATE || state == TIE_STATE) {
			x = y = -1;
			RenderEndStage();
		}
		while (!quit && (state == X_WON_STATE || state == O_WON_STATE || state == TIE_STATE)) {
			CheckClickWinMenu(e, quit);
		}
	}
}

void Game3x3bot::Click(int& timer) {
	if (board[y][x] == EMPTY) {
		timer = 45;
		player = PLAYER_O;
		board[y][x] = PLAYER_X;
	}
}

void Game3x3bot::HandleEvent(SDL_Event& e, bool& quit, int& timer) {
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			quit = true;
			return;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (CheckClick(chooseLevelMedium.GetRect(), e.button.x, e.button.y) && gameLevelStatus == 2) {
				boardColor = green;
				gameLevelStatus = 0;

				int x = chooseLevelHard.GetRect().x - 11;
				while (x >= chooseLevelMedium.GetRect().x) {
					base.SetRect(x, chooseLevelMedium.GetRect().y, chooseLevelMedium.GetRect().w, chooseLevelMedium.GetRect().h);

					RenderRunningstate();
					base.RenderButton();

					SDL_RenderPresent(gRenderer);
					x -= 11;
				}
				gameLevelStatus = 1;
				cntOwin = cntXwin = 0;
				timer = 45;
				depth = 0;
			}
			else if (CheckClick(chooseLevelHard.GetRect(), e.button.x, e.button.y) && gameLevelStatus == 1) {
				boardColor = lightRed;
				gameLevelStatus = 0;

				int x = chooseLevelMedium.GetRect().x + 11;
				while (x <= chooseLevelHard.GetRect().x) {
					base.SetRect(x, chooseLevelMedium.GetRect().y, chooseLevelMedium.GetRect().w, chooseLevelMedium.GetRect().h);

					RenderRunningstate();
					base.RenderButton();

					SDL_RenderPresent(gRenderer);
					x += 11;
				}
				gameLevelStatus = 2;
				cntOwin = cntXwin = 0;
				timer = 45;
				depth = 3;
			}
			else if (CheckClick(home.GetRect(), e.button.x, e.button.y)) {
				menuType = STARTMENU;
				break;
			}
			else if (e.button.y >= (SCREEN_HEIGHT - SCREEN_WIDTH)) {
				x = e.button.x / CELL_WIDTH;
				y = (e.button.y - (SCREEN_HEIGHT - SCREEN_WIDTH)) / CELL_HEIGHT;
				Click(timer);
			}

			RenderRunningstate();
			SDL_RenderPresent(gRenderer);
		}
	}
}

void Game3x3bot::RenderRunningstate() {
	Game3x3::RenderRunningstate();
	
	SDL_Rect rect = { 295, 10, 170, 45 };
	RenderImage("img/nut9.png", rect);

	if (gameLevelStatus == 1) {
		chooseLevelMedium.RenderButton();
	}
	else if (gameLevelStatus == 2) {
		chooseLevelHard.RenderButton();
	}
}

int Game3x3bot::value(bool isBotTurn) {
	if (CheckWinCol() || CheckWinRow() || CheckWinDiag1() || CheckWinDiag2()) {
		if (isBotTurn) return INT_MIN;
		else return INT_MAX;
	}
	else return 0;
}