#include"Game3x3bot.h"

int Game3x3bot::minimax(int depth, bool isBotTurn, int alpha, int beta, int x, int y) {
	if (CheckWinCol(x, y) || CheckWinRow(x, y) || CheckWinDiag1(x, y) || CheckWinDiag2(x, y)) {
		if (isBotTurn) return INT_MIN;
		else return INT_MAX;
	}
	else if (CheckTie()) return 0;
	if (isBotTurn) {
		int res = INT_MIN;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == EMPTY) {
					board[i][j] = PLAYER_O;
					int score = minimax(depth - 1, false, alpha, beta, j, i);
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
					board[i][j] = PLAYER_X;
					int score = minimax(depth - 1, true, alpha, beta, j, i);
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
	int x = -1;
	int y = -1;
	while (menuType != STARTMENU && !quit) {
		if (state == RUNNING_STATE) {
			Uint32 starttime = SDL_GetTicks() / 1000;
			int timer = 45;

			while (!quit && state == RUNNING_STATE) {
				std::string displaytime = "00:" + std::to_string(timer);
				Text timetext;
				if (!timetext.OpenFont(15, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				timetext.SetColor(red);
				timetext.SetText(displaytime);

				RenderRunningstate(x, y);

				if (player == PLAYER_X) {
					timetext.RenderText(80, 120);
				}
				SDL_RenderPresent(gRenderer);

				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

				if (player == PLAYER_X) {
					while (SDL_PollEvent(&e)) {

						if (e.type == SDL_QUIT) {
							quit = true;
							return;
						}
						else if (e.type == SDL_MOUSEBUTTONDOWN) {
							if (e.button.y >= (SCREEN_HEIGHT - SCREEN_WIDTH)) {
								x = e.button.x / CELL_WIDTH;
								y = (e.button.y - (SCREEN_HEIGHT - SCREEN_WIDTH)) / CELL_HEIGHT;
								Click(x, y, timer);
							}

							RenderRunningstate(x, y);
							SDL_RenderPresent(gRenderer);
						}
					}
				}
				else if (player == PLAYER_O) {
					int res = INT_MIN;

					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							if (board[i][j] == EMPTY) {
								board[i][j] = PLAYER_O;
								int score = minimax(1, false, INT_MIN, INT_MAX, j, i);
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
				if (CheckWinCol(x, y) || CheckWinRow(x, y) || CheckWinDiag1(x, y) || CheckWinDiag2(x, y)) {
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

void Game3x3bot::Click(const int& x, const int& y, int& timer) {
	if (board[y][x] == EMPTY) {
		timer = 45;
		player = PLAYER_O;
		board[y][x] = PLAYER_X;
	}
}