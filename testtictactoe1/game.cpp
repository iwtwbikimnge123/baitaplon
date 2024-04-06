#include "game.h"

Game::Game() {
	N = CELL_HEIGHT = CELL_WIDTH = 0;
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
	while (menutype != CHOOSEMAP && !quit) {
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
			RenderEndStage(a, b);
		}
		while (!quit && ( state == X_WON_STATE || state == O_WON_STATE || state == TIE_STATE )) {
			CheckClickWinMenu(e, quit, a, b);
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
		timer = 0;
		ChangeTurn();
		board[y][x] = player;
	}
}

void Game::RenderRunningstate(const int& x, const int& y) {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
	SDL_RenderClear(gRenderer);
	DrawGrid();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == PLAYER_X) DrawXCell(j, i);
			else if (board[i][j] == PLAYER_O) DrawOCell(j, i);
		}
	}
	SDL_Rect rect;
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

	SDL_Surface* surface = IMG_Load("imageandsound/X.png");
	if (!surface) {
		std::cout << SDL_GetError();
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (!texture) {
		std::cout << SDL_GetError();
		return;
	}
	SDL_FreeSurface(surface);

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Game::DrawOCell(const int& x, const int& y) {
	SDL_Rect rect;
	rect.x = CELL_WIDTH * x;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * y;
	rect.w = CELL_WIDTH;
	rect.h = CELL_HEIGHT;

	SDL_Surface* surface = IMG_Load("imageandsound/O.png");
	if (!surface) {
		std::cout << SDL_GetError();
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (!texture) {
		std::cout << SDL_GetError();
		return;
	}
	SDL_FreeSurface(surface);

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
	texture = NULL;
}


void Game::RenderEndStage(Text returnmenu2, Text continueplay) {
	SDL_Delay(50);
	RenderRunningstate(-1, -1);
	if (state == O_WON_STATE) {
		for (int i = 0; i < 5; i++) {
			SDL_Rect rect;
			rect.x = CELL_WIDTH * winCells[i].second;
			rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * winCells[i].first;
			rect.w = CELL_WIDTH;
			rect.h = CELL_HEIGHT;

			SDL_Surface* surface;

			surface = IMG_Load("imageandsound/winO.png");

			if (!surface) {
				std::cout << SDL_GetError();
				return;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
			if (!texture) {
				std::cout << SDL_GetError();
				return;
			}
			SDL_FreeSurface(surface);

			SDL_RenderCopy(gRenderer, texture, NULL, &rect);

			SDL_DestroyTexture(texture);
			texture = NULL;
		}
	}
	else if (state == X_WON_STATE) {
		for (int i = 0; i < 5; i++) {
			SDL_Rect rect;
			rect.x = CELL_WIDTH * winCells[i].second;
			rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * winCells[i].first;
			rect.w = CELL_WIDTH;
			rect.h = CELL_HEIGHT;

			SDL_Surface* surface;

			surface = IMG_Load("imageandsound/winX.png");

			if (!surface) {
				std::cout << SDL_GetError();
				return;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
			if (!texture) {
				std::cout << SDL_GetError();
				return;
			}
			SDL_FreeSurface(surface);

			SDL_RenderCopy(gRenderer, texture, NULL, &rect);

			SDL_DestroyTexture(texture);
			texture = NULL;
		}
	}

	SDL_RenderPresent(gRenderer);

	SDL_Delay(300);


}

void Game::CheckClickWinMenu(SDL_Event& e, bool& quit, Text returnmenu2, Text continueplay) {
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	if (state == O_WON_STATE) RenderImage("imageandsound/O.png");
	else if (state == X_WON_STATE) RenderImage("imageandsound/X.png");
	else RenderImage("imageandsound/anh1.png");

	if (!returnmenu2.OpenFont(30, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	if (!continueplay.OpenFont(40, "imageandsound/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}

	returnmenu2.SetColor(green);
	continueplay.SetColor(green);

	returnmenu2.SetText("return");
	continueplay.SetText("continue");

	returnmenu2.RenderText(180, 100);
	continueplay.RenderText(130, 450);
	SDL_RenderPresent(gRenderer);

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			quit = true;
			return;
		}

		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (CheckClick(*returnmenu2.GetRect(), e.button.x, e.button.y)) {
				menutype = CHOOSEMAP;
				state = RUNNING_STATE;
			}
			else if (CheckClick(*continueplay.GetRect(), e.button.x, e.button.y)) InitBoard();
		}
	}
}