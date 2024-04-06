#include "Game.h"

Game::Game() {
	N = CELL_HEIGHT = CELL_WIDTH = 0;
	player = PLAYER_X;
	state = RUNNING_STATE;
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

bool Game::CheckWinRow(const int& x, const int& y) {
	int minrow = std::max(0, x - 4);
	int maxrow = std::min(N - 1, x + 4);
	for (int i = minrow; i <= maxrow - 4; i++) {
		if (board[y][i] != EMPTY &&
			board[y][i] == board[y][i + 1] &&
			board[y][i + 1] == board[y][i + 2] &&
			board[y][i + 2] == board[y][i + 3] &&
			board[y][i + 3] == board[y][i + 4])
			return true;
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
			board[i + 3][x] == board[i + 4][x])
			return true;
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
			board[y + i + 3][x - i - 3] == board[y + i + 4][x - i - 4])
			return true;
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
			board[y + i + 3][x + i + 3] == board[y + i + 4][x + i + 4])
			return true;
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