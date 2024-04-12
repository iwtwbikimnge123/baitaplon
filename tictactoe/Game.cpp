#include "game.h"

Game::Game() {
	N = CELL_HEIGHT = CELL_WIDTH = 0;
	cntXwin = cntOwin = 0;

	continue_.SetButtonType(CONTINUE);
	continue_.SetPath();
	continue_.SetRect(132, 350, 230, 90);

	focusContinue.SetButtonType(FOCUS_CONTINUE);
	focusContinue.SetPath();
	focusContinue.SetRect(132, 350, 230, 90);

	return_.SetButtonType(RETURN);
	return_.SetPath();
	return_.SetRect(132, 450, 230, 90);

	focusReturn.SetButtonType(FOCUS_RETURN);
	focusReturn.SetPath();
	focusReturn.SetRect(132, 450, 230, 90);

	player = PLAYER_X;
	state = RUNNING_STATE;
	winCells[0] = std::make_pair(-1, -1);
	winCells[1] = std::make_pair(-1, -1);
	winCells[2] = std::make_pair(-1, -1);
	winCells[3] = std::make_pair(-1, -1);
	winCells[4] = std::make_pair(-1, -1);
}

Game::~Game() {
	for (int i = 0; i < N; i++) {
		delete[] board[i];
	}
	delete[] board;
}


void Game::InitBoard() {
	board = new Player * [N];
	for (int i = 0; i < N; i++) board[i] = new Player[N];
	state = RUNNING_STATE;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) board[i][j] = EMPTY;
	}
}

void Game::DrawGrid() {
	SDL_SetRenderDrawColor(gRenderer, 128, 128, 128, 255);
	SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT - SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_HEIGHT - SCREEN_WIDTH);

	for (int i = 1; i < N; i++) {
		SDL_RenderDrawLine(gRenderer, CELL_WIDTH * i, SCREEN_HEIGHT - SCREEN_WIDTH, CELL_WIDTH * i, SCREEN_HEIGHT);
		for (int i = 1; i < N; i++) {
			SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * i, SCREEN_WIDTH, SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * i);
		}
	}
}

void Game::ChangeTurn() {
	if (player == PLAYER_O) player = PLAYER_X;
	else player = PLAYER_O;
}

void Game::logic(SDL_Event& e, bool& quit) {
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

				Text otherTime;
				if (!otherTime.OpenFont(15, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				otherTime.SetColor(grey);
				otherTime.SetText("00:45");

				RenderRunningstate(x, y);

				if (player == PLAYER_X) {
					timetext.RenderText(80, 120);
					otherTime.RenderText(360, 120);
				}
				else {
					timetext.RenderText(360, 120);
					otherTime.RenderText(80, 120);
				}

				SDL_RenderPresent(gRenderer);
				while (SDL_PollEvent(&e)) {

					SDL_RenderClear(gRenderer);
					SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
					if (e.type == SDL_QUIT) {
						quit = true;
						return;
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN) {
						x = e.button.x / CELL_WIDTH;
						y = (e.button.y - (SCREEN_HEIGHT - SCREEN_WIDTH)) / CELL_HEIGHT;
						Click(x, y, timer);
						if (CheckWinCol(x, y) || CheckWinRow(x, y) || CheckWinDiag1(x, y) || CheckWinDiag2(x, y)) {
							if (player == PLAYER_O) state = X_WON_STATE;
							else state = O_WON_STATE;
							break;
						}
						else if (CheckTie()) {
							state = TIE_STATE;
							break;
						}
						RenderRunningstate(x, y);
						SDL_RenderPresent(gRenderer);
					}
				}
				Uint32 finaltime = SDL_GetTicks() / 1000;
				if (finaltime - starttime >= 1) {
					timer--;
					starttime = SDL_GetTicks() / 1000;
				}

				if (timer == 0) {
					if (player == PLAYER_O) state = X_WON_STATE;
					else state = O_WON_STATE;
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

bool Game::CheckWinRow(const int& x, const int& y) {
	int minrow = std::max(0, x - 4);
	int maxrow = std::min(N - 1, x + 4);
	for (int i = minrow; i <= maxrow - 4; i++) {
		if (board[y][i] != EMPTY &&
			board[y][i] == board[y][i + 1] &&
			board[y][i + 1] == board[y][i + 2] &&
			board[y][i + 2] == board[y][i + 3] &&
			board[y][i + 3] == board[y][i + 4]) {
			winCells[0] = std::make_pair(y, i);
			winCells[1] = std::make_pair(y, i + 1);
			winCells[2] = std::make_pair(y, i + 2);
			winCells[3] = std::make_pair(y, i + 3);
			winCells[4] = std::make_pair(y, i + 4);
			return true;
		}
	}
	return false;
}
bool Game::CheckWinCol(const int& x, const int& y) {
	int mincol = std::max(0, y - 4);
	int maxcol = std::min(N - 1, y + 4);
	for (int i = mincol; i <= maxcol - 4; i++) {
		if (board[i][x] != EMPTY &&
			board[i][x] == board[i + 1][x] &&
			board[i + 1][x] == board[i + 2][x] &&
			board[i + 2][x] == board[i + 3][x] &&
			board[i + 3][x] == board[i + 4][x]) {
			winCells[0] = std::make_pair(i, x);
			winCells[1] = std::make_pair(i + 1, x);
			winCells[2] = std::make_pair(i + 2, x);
			winCells[3] = std::make_pair(i + 3, x);
			winCells[4] = std::make_pair(i + 4, x);
			return true;
		}
	}
	return false;
}
bool Game::CheckWinDiag2(const int& x, const int& y) {
	int upd, downd;
	if (x >= N - 4 || y < 4) {
		upd = -std::min(y, N - x - 1);
	}
	else upd = -4;
	if (x < 4 || y >= N - 4) {
		downd = std::min(N - y - 1, x);
	}
	else downd = 4;
	for (int i = upd; i <= downd - 4; i++) {
		if (board[y + i][x - i] != EMPTY &&
			board[y + i][x - i] == board[y + i + 1][x - i - 1] &&
			board[y + i + 1][x - i - 1] == board[y + i + 2][x - i - 2] &&
			board[y + i + 2][x - i - 2] == board[y + i + 3][x - i - 3] &&
			board[y + i + 3][x - i - 3] == board[y + i + 4][x - i - 4]) {
			winCells[0] = std::make_pair(y + i, x - i);
			winCells[1] = std::make_pair(y + i + 1, x - i - 1);
			winCells[2] = std::make_pair(y + i + 2, x - i - 2);
			winCells[3] = std::make_pair(y + i + 3, x - i - 3);
			winCells[4] = std::make_pair(y + i + 4, x - i - 4);
			return true;
		}
	}
	return false;
}
bool Game::CheckWinDiag1(const int& x, const int& y) {
	int upd, downd;
	if (x < 4 || y < 4) {
		upd = -std::min(y, x);
	}
	else upd = -4;
	if (x >= N - 4 || y >= N - 4) {
		downd = std::min(N - y, N - x) - 1;
	}
	else downd = 4;
	for (int i = upd; i <= downd - 4; i++) {
		if (board[y + i][x + i] != EMPTY &&
			board[y + i][x + i] == board[y + i + 1][x + i + 1] &&
			board[y + i + 1][x + i + 1] == board[y + i + 2][x + i + 2] &&
			board[y + i + 2][x + i + 2] == board[y + i + 3][x + i + 3] &&
			board[y + i + 3][x + i + 3] == board[y + i + 4][x + i + 4]) {
			winCells[0] = std::make_pair(y + i, x + i);
			winCells[1] = std::make_pair(y + i + 1, x + i + 1);
			winCells[2] = std::make_pair(y + i + 2, x + i + 2);
			winCells[3] = std::make_pair(y + i + 3, x + i + 3);
			winCells[4] = std::make_pair(y + i + 4, x + i + 4);
			return true;
		}
	}
	return false;
}
bool Game::CheckTie() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == EMPTY) return false;
		}
	}
	return true;
}

void Game::Click(const int& x, const int& y, int& timer) {
	if (board[y][x] == EMPTY) {
		timer = 45;
		board[y][x] = player;
		ChangeTurn();
	}
}

void Game::RenderRunningstate(const int& x, const int& y) {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 144, 238, 144, 0);

	SDL_Rect rect;

	rect.x = 0;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH;
	rect.w = rect.h = SCREEN_WIDTH;

	SDL_RenderFillRect(gRenderer, &rect);

	rect.x = 50;
	rect.y = 67;
	rect.w = 120;
	rect.h = 50;
	if (player == PLAYER_X) {
		RenderImage("img/logoX2.png", rect);
		rect.x = 325;
		RenderImage("img/logoO.png", rect);
	}
	else {
		RenderImage("img/logoX.png", rect);
		rect.x = 325;
		RenderImage("img/logoO2.png", rect);
	}

	Text xPoint;
	Text oPoint;
	if (!xPoint.OpenFont(21, "img/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	xPoint.SetText(std::to_string(cntXwin));
	xPoint.SetColor(white);
	xPoint.RenderText(132, 80);

	if (!oPoint.OpenFont(21, "img/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	oPoint.SetText(std::to_string(cntOwin));
	oPoint.SetColor(white);
	oPoint.RenderText(345, 80);


	DrawGrid();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == PLAYER_X) DrawXCell(j, i);
			else if (board[i][j] == PLAYER_O) DrawOCell(j, i);
		}
	}
	rect.x = CELL_WIDTH * x;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * y;
	rect.w = CELL_WIDTH;
	rect.h = CELL_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(gRenderer, &rect);

}

void Game::DrawXCell(const int& x, const int& y) {
	SDL_Rect rect;
	rect.x = CELL_WIDTH * x;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * y;
	rect.w = CELL_WIDTH;
	rect.h = CELL_HEIGHT;

	RenderImage("img/X.png", rect);
}

void Game::DrawOCell(const int& x, const int& y) {
	SDL_Rect rect;
	rect.x = CELL_WIDTH * x;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * y;
	rect.w = CELL_WIDTH;
	rect.h = CELL_HEIGHT;

	RenderImage("img/O.png", rect);
}


void Game::RenderEndStage() {
	RenderRunningstate(-1, -1);
	if (state == O_WON_STATE) {
		cntOwin++;

		for (int i = 0; i < 5; i++) {
			SDL_Rect rect;
			rect.x = CELL_WIDTH * winCells[i].second;
			rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * winCells[i].first;
			rect.w = CELL_WIDTH;
			rect.h = CELL_HEIGHT;

			RenderImage("img/winO.png", rect);
		}
	}
	else if (state == X_WON_STATE) {
		cntXwin++;

		for (int i = 0; i < 5; i++) {
			SDL_Rect rect;
			rect.x = CELL_WIDTH * winCells[i].second;
			rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * winCells[i].first;
			rect.w = CELL_WIDTH;
			rect.h = CELL_HEIGHT;

			RenderImage("img/winX.png", rect);
		}
	}

	SDL_RenderPresent(gRenderer);

	SDL_Delay(300);

	SDL_SetRenderDrawColor(gRenderer, 176, 224, 208, 0);
	SDL_RenderClear(gRenderer);

	SDL_Rect rect = { 25, 150, 450, 170 };
	if (state == X_WON_STATE) {
		RenderImage("img/xwin.png", rect);
	}
	else if (state == O_WON_STATE) {
		RenderImage("img/owin.png", rect);
	}
	else RenderImage("img/tie.png", rect);
	return_.RenderButton();
	continue_.RenderButton();
	SDL_RenderPresent(gRenderer);

}

void Game::CheckClickWinMenu(SDL_Event& e, bool& quit) {

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			quit = true;
			return;
		}

		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (CheckClick(return_.GetRect(), e.button.x, e.button.y)) {
				menuType = STARTMENU;
				state = RUNNING_STATE;
			}
			else if (CheckClick(continue_.GetRect(), e.button.x, e.button.y)) InitBoard();
		}
		else if (e.type == SDL_MOUSEMOTION) {
			if (CheckClick(focusReturn.GetRect(), e.motion.x, e.motion.y)) {
				focusReturn.RenderButton();
			}
			else if (CheckClick(focusContinue.GetRect(), e.motion.x, e.motion.y)) {
				focusContinue.RenderButton();
			}
			else {
				return_.RenderButton();
				continue_.RenderButton();
			}
			SDL_RenderPresent(gRenderer);
		}
	}
}


