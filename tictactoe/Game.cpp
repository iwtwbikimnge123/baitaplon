
#include "Game.h"

Game::Game() {
	N = CELL_HEIGHT = CELL_WIDTH = 0;
	cntXwin = cntOwin = 0;

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

void Game::InitBoard() {
	board = new Player * [N];
	for (int i = 0; i < N; i++) board[i] = new Player[N];
	state = RUNNING_STATE;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) board[i][j] = EMPTY;
	}
}

void Game::ChangeTurn() {
	if (player == PLAYER_O) player = PLAYER_X;
	else player = PLAYER_O;
}

bool Game::CheckTie() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == EMPTY) return false;
		}
	}
	return true;
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

void Game::Click(const int& x, const int& y, int& timer) {
	if (board[y][x] == EMPTY) {
		timer = 0;
		ChangeTurn();
		board[y][x] = player;
	}
}

void Game::logic(SDL_Event& e, bool& quit) {
	int x = -1;
	int y = -1;
	while (menuType != STARTMENU && !quit) {
		if (state == RUNNING_STATE) {
			Uint32 starttime = SDL_GetTicks() / 1000;
			int timer = 0;

			while (!quit) {
				std::string displaytime = "time : " + std::to_string(timer);
				Text timetext;
				if (!timetext.OpenFont(10, "imageandsound/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				timetext.SetColor(black);
				timetext.SetText(displaytime);

				RenderRunningstate(x, y);

				timetext.RenderText(10, 10);

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
							if (player == PLAYER_O) state = O_WON_STATE;
							else state = X_WON_STATE;
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
					timer++;
					starttime = SDL_GetTicks() / 1000;
				}

				if (timer == 45) {
					if (player == PLAYER_O) state = O_WON_STATE;
					else state = X_WON_STATE;
					break;
				}
				if (state != RUNNING_STATE) break;
			}
		}

		Text a, b;
		if (state == X_WON_STATE || state == O_WON_STATE || state == TIE_STATE) {
			x = y = -1;
			RenderEndStage();
		}
		while (!quit && (state == X_WON_STATE || state == O_WON_STATE || state == TIE_STATE)) {
			CheckClickWinMenu(e, quit, a, b);
		}
	}
}


void Game::RenderRunningstate(const int& x, const int& y) {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
	SDL_RenderClear(gRenderer);

	//to mau cho bang
	SDL_SetRenderDrawColor(gRenderer, 144, 238, 144, 0);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH;
	rect.w = rect.h = SCREEN_WIDTH;
	SDL_RenderFillRect(gRenderer, &rect);

	// render diem
	Text xPoint;
	Text oPoint;
	if (!xPoint.OpenFont(20, "img/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	xPoint.SetText(std::to_string(cntXwin));
	xPoint.SetColor(black);
	xPoint.RenderText(132, 100);

	if (!oPoint.OpenFont(20, "img/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	oPoint.SetText(std::to_string(cntOwin));
	oPoint.SetColor(black);
	oPoint.RenderText(345, 100);


	DrawGrid();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == PLAYER_X) DrawXCell(j, i);
			else if (board[i][j] == PLAYER_O) DrawOCell(j, i);
		}
	}
	SDL_Rect rect1;
	rect.x = CELL_WIDTH * x;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * y;
	rect.w = CELL_WIDTH;
	rect.h = CELL_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(gRenderer, &rect1);

}

void Game::RenderEndStage() {
	SDL_Delay(50);
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

}

