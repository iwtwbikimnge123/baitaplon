#include "Game3x3.h"

bool Game3x3::CheckWinRow() {
	for (int i = 0; i < N; i++) {
		if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
			winCells[0] = std::make_pair(0, i);
			winCells[1] = std::make_pair(1, i);
			winCells[2] = std::make_pair(2, i);
			return true;
		}
	}
	return false;
}

bool Game3x3::CheckWinCol() {
	for (int i = 0; i < N; i++) {
		if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
			winCells[0] = std::make_pair(i, 0);
			winCells[1] = std::make_pair(i, 1);
			winCells[2] = std::make_pair(i, 2);
			return true;
		}
	}
	return false;
}

bool Game3x3::CheckWinDiag1() {
	if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		winCells[0] = std::make_pair(0, 0);
		winCells[1] = std::make_pair(1, 1);
		winCells[2] = std::make_pair(2, 2);
		return true;
	}
	return false;
}

bool Game3x3::CheckWinDiag2() {
	if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		winCells[0] = std::make_pair(0, 2);
		winCells[1] = std::make_pair(1, 1);
		winCells[2] = std::make_pair(2, 0);
		return true;
	}
	return false;
}

void Game3x3::RenderEndStage() {
	RenderRunningstate();
	if (state == O_WON_STATE) {
		cntOwin++;

		for (int i = 0; i < 3; i++) {
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

		for (int i = 0; i < 3; i++) {
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

	Mix_PlayChannel(-1, gChunk_over, 0);

}