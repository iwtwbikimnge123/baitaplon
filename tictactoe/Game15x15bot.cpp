#include "Game15x15bot.h"

const int di[4] = { 1, 1, 1, 0 };
const int dj[4] = { -1, 0, 1, 1 };

int Game15x15bot::value(bool isBotTurn) {
	int val = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == PLAYER_X) {
				for (int k = 0; k < 4; k++) {
					int curR = 1;
					int point = 0;
					bool block = false;
					for (int m = 1; m < 5; m++) {
						//bi chan

						if (!checkinside(i + di[k] * m, j + dj[k] * m) ||
							board[i + di[k] * m][j + dj[k] * m] == PLAYER_O) {

							block = true;

							if (!checkinside(i - di[k], j - dj[k]) ||
								board[i - di[k]][j - dj[k]] == PLAYER_O ||
								curR == 1) {
								point = 0;
							}
							else if (board[i + di[k] * (m - 1)][j + dj[k] * (m - 1)] == PLAYER_X) {
								if (curR == 2) point = 0;
								else point = pow(10, 2 * (curR - 1)) / 5;
							}
							else if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
								board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) {
								point = pow(10, 2 * (curR - 1));
							}
							else point = pow(10, 2 * (curR - 1)) / 4;

							break;
						}
						//o X

						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_X) curR++;
					}

					if (!block) {

						if (curR == 1) point = 0;
						else if (curR == 2) {
							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == PLAYER_X) point = 0;
								else point = pow(10, 2 * (curR - 1));
							}
							else point = 0;
						}
						else if (curR == 5) point = 10000000;
						//_|_____|O


						else if (!checkinside(i + di[k] * 5, j + dj[k] * 5) ||
							board[i + di[k] * 5][j + dj[k] * 5] == PLAYER_O) {
							//_|_____|O
							if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) {
								//O|XXX__|O
								if (!checkinside(i - di[k], j - dj[k]) ||
									board[i - di[k]][j - dj[k]] == PLAYER_O) point = pow(10, 2 * (curR - 1)) / 4;
								//_|X_XX_|O
								else point = pow(10, 2 * (curR - 1));

							}
							//_|X___X|O
							else  point = pow(10, 2 * (curR - 1)) / 4;

						}

						//_____|_
						else if (board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {

							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == EMPTY) point = pow(10, 2 * (curR - 1));
								else point = pow(10, 2 * (curR - 1)) / 3;
							}
							else point = pow(10, 2 * (curR - 1)) / 4;

						}
					}
					val -= point;
				}
			}
			else if (board[i][j] == PLAYER_O) {
				for (int k = 0; k < 4; k++) {
					int curR = 1;
					int point = 0;
					bool block = false;
					for (int m = 1; m < 5; m++) {
						//bi chan

						if (!checkinside(i + di[k] * m, j + dj[k] * m) ||
							board[i + di[k] * m][j + dj[k] * m] == PLAYER_X) {

							block = true;

							if (!checkinside(i - di[k], j - dj[k]) ||
								board[i - di[k]][j - dj[k]] == PLAYER_X ||
								curR == 1) {
								point = 0;
							}
							else if (board[i + di[k] * (m - 1)][j + dj[k] * (m - 1)] == PLAYER_O) {
								if (curR == 2) point = 0;
								else point = pow(10, 2 * (curR - 1)) / 5;
							}
							else if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
								board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) {
								point = pow(10, 2 * (curR - 1));
							}
							else point = pow(10, 2 * (curR - 1)) / 4;

							break;
						}
						//o X

						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_O) curR++;
					}

					if (!block) {

						if (curR == 1) point = 0;
						else if (curR == 2) {
							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == PLAYER_O) point = 0;
								else point = pow(10, 2 * (curR - 1));
							}
							else point = 0;
						}
						else if (curR == 5) point = 10000000;
						//_|_____|O


						else if (!checkinside(i + di[k] * 5, j + dj[k] * 5) ||
							board[i + di[k] * 5][j + dj[k] * 5] == PLAYER_X) {
							//_|_____|O
							if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) {
								//O|XXX__|O
								if (!checkinside(i - di[k], j - dj[k]) ||
									board[i - di[k]][j - dj[k]] == PLAYER_X) point = pow(10, 2 * (curR - 1)) / 4;
								//_|X_XX_|O
								else point = pow(10, 2 * (curR - 1));

							}
							//_|X___X|O
							else  point = pow(10, 2 * (curR - 1)) / 4;

						}

						//_____|_
						else if (board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {

							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == EMPTY) point = pow(10, 2 * (curR - 1));
								else point = pow(10, 2 * (curR - 1)) / 3;
							}
							else point = pow(10, 2 * (curR - 1)) / 4;

						}
					}
					val += point;
				}
			}
		}
	}
	return val;

}

bool Game15x15bot::CheckWinRow() {
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
bool Game15x15bot::CheckWinCol() {
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
bool Game15x15bot::CheckWinDiag2() {
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
bool Game15x15bot::CheckWinDiag1() {
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

void Game15x15bot::RenderEndStage() {
	RenderRunningstate();
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

