#include "Game15x15bot.h"

const int di[4] = { 1, 1, 1, 0 };
const int dj[4] = { -1, 0, 1, 1 };

int Game15x15bot::value(bool isBotTurn) {
	/*
	int val = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == PLAYER_X) {
				for (int k = 0; k < 4; k++) {
					int curval = 1;
					bool block = false;
					for (int m = 1; m < 5; m++) {
						if (!checkinside(i + di[k] * m, j + dj[k] * m) ||
							board[i + di[k] * m][j + dj[k] * m] == PLAYER_O) {

							block = true;

							if (!checkinside(i - di[k], j - dj[k]) ||
								board[i - di[k]][j - dj[k]] == PLAYER_O ||
								curval == 1) {
								curval = 0;
							}

							else if (board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + di[k] * (m - 1)][j + dj[k] * (m - 1)] == PLAYER_X) {
									if (curval == 3) curval = 8;
									else if (curval == 2) curval = 0;
									else if (curval == 4) curval = 19;
									break;
								}
								else if (curval == 3) {
									if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
										board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) curval = 18;
									else curval = 8;
								}
								else if (curval == 2) {
									if (m == 4 && checkinside(i - di[k] * 2, j - dj[k] * 2) &&
										board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) curval = 7;
								}
								else {
									curval = 0;
								}
							}
							break;
						}
						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_X) curval++;
					}

					if (!block) {
						if (checkinside(i - di[k], j - dj[k]) &&
							board[i - di[k]][j - dj[k]] == EMPTY) {
							if (curval == 2) {
								if (board[i + di[k] * 4][j + dj[k] * 4] == PLAYER_X) curval = 0;
								else curval = 7;
							}
							else if (board[i + di[k] * 4][j + dj[k] * 4] != PLAYER_X) {
								if (curval == 4) curval = 1000;
								else if (curval == 3) curval = 18;
							}
							else if (checkinside(i + di[k] * 5, j + dj[k] * 5) &&
								board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {
								if (curval == 5) curval = 10000;
								else if (curval == 4) {
									if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) curval = 1000;
									else if (board[i + di[k] * 2][j + dj[k] * 2] == EMPTY) curval = 19;
									else curval = 20;
								}
								else if (curval == 3) curval = 18;
							}
							else {
								if (curval == 4) curval = 19;
								else if (curval == 3) curval = 8;
							}
						}

						else {
							if (curval == 5) curval = 10000;
							else if (curval == 4) curval = 19;
							else if (curval == 3) curval = 8;
							else curval = 0;
						}
					}
					val -= curval;
				}
			}
			else if (board[i][j] == PLAYER_O) {
				for (int k = 0; k < 4; k++) {
					int curval = 1;
					bool block = false;
					for (int m = 1; m < 5; m++) {
						if (!checkinside(i + di[k] * m, j + dj[k] * m) ||
							board[i + di[k] * m][j + dj[k] * m] == PLAYER_X) {
							block = true;


							if (!checkinside(i - di[k], j - dj[k]) ||
								board[i - di[k]][j - dj[k]] == PLAYER_X ||
								curval == 1) {
								curval = 0;
							}

							else if (board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + di[k] * (m - 1)][j + dj[k] * (m - 1)] == PLAYER_O) {
									if (curval == 3) curval = 8;
									else if (curval == 2) curval = 0;
									else if (curval == 4) curval = 19;
									break;
								}
								else if (curval == 3) {
									if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
										board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) curval = 18;
									else curval = 8;
								}
								else if (curval == 2) {
									if (m == 4 && checkinside(i - di[k] * 2, j - dj[k] * 2) &&
										board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) curval = 7;
								}
								else {
									curval = 0;
								}
							}
							break;
						}
						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_O) curval++;
					}
					if (!block) {

						if (checkinside(i - di[k], j - dj[k]) &&
							board[i - di[k]][j - dj[k]] == EMPTY) {
							if (curval == 2) {
								if (board[i + di[k] * 4][j + dj[k] * 4] == PLAYER_O) curval = 0;
								else curval = 7;
							}
							else if (board[i + di[k] * 4][j + dj[k] * 4] != PLAYER_O) {
								if (curval == 4) curval = 1000;
								else if (curval == 3) curval = 18;
							}
							else if (checkinside(i + di[k] * 5, j + dj[k] * 5) &&
								board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {
								if (curval == 5) curval = 10000;
								else if (curval == 4) {
									if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) curval = 1000;
									else if (board[i + di[k] * 2][j + dj[k] * 2] == EMPTY) curval = 19;
									else curval = 20;
								}
								else if (curval == 3) curval = 18;
							}
							else {
								if (curval == 4) curval = 19;
								else if (curval == 3) curval = 8;
							}
						}

						else {
							if (curval == 5) curval = 10000;
							else if (curval == 4) curval = 19;
							else if (curval == 3) curval = 8;
							else curval = 0;
						}
					}
					val += curval;
				}
			}
		}
	}
	return val;
	*/
	
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
								else point = pow(10, curR - 2) + 2;
							}
							else if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
								board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) {
								point = pow(10, curR - 1);
							}
							else point = pow(10, curR - 2) + 2;

							break;
						}	
						//o X

						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_X) curR++;
					}

					if (!block) {

						if (curR == 1) {
							if (checkinside(i - 5 * di[k], j - 5 * dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY &&
								board[i - 2 * di[k]][j - 2 * dj[k]] == EMPTY &&
								board[i - 3 * di[k]][j - 3 * dj[k]] == EMPTY && 
								board[i - 4 * di[k]][j - 4 * dj[k]] == EMPTY &&
								board[i - 5 * di[k]][j - 5 * dj[k]] == EMPTY ) point = 1;
							else point = 0;
						}
						else if (curR == 2) {
							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == PLAYER_X) point = 0;
								else point = pow(10, curR - 1);
							}
							else point = 0;
						}
						else if (curR == 5) point = 100000000;
						//_|_____|O


						else if (!checkinside(i + di[k] * 5, j + dj[k] * 5) ||
							board[i + di[k] * 5][j + dj[k] * 5] == PLAYER_O) {
							//_|_____|O
							if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) {
								//O|XXX__|O
								if (!checkinside(i - di[k], j - dj[k]) ||
									board[i - di[k]][j - dj[k]] == PLAYER_O) point = pow(10, curR - 2) + 2;
								//_|X_XX_|O
								else point = pow(10, curR - 1);

							}
							//_|X___X|O
							else  point = pow(10, curR - 2) + 2;

						}

						//_____|_
						else if (board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {

							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == EMPTY) point = pow(10, curR - 1);
								else point = pow(10, curR - 2) + 3;
							}
							else point = pow(10, curR - 2) + 2;

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
								else point = pow(10, curR - 2) + 2;
							}
							else if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
								board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) {
								point = pow(10, curR - 1);
							}
							else point = pow(10, curR - 2) + 2;

							break;
						}
						//o X

						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_O) curR++;
					}

					if (!block) {

						if (curR == 1) {
							if (checkinside(i - 5 * di[k], j - 5 * dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY &&
								board[i - 2 * di[k]][j - 2 * dj[k]] == EMPTY &&
								board[i - 3 * di[k]][j - 3 * dj[k]] == EMPTY &&
								board[i - 4 * di[k]][j - 4 * dj[k]] == EMPTY &&
								board[i - 5 * di[k]][j - 5 * dj[k]] == EMPTY) point = 1;
							else point = 0;
						}
						else if (curR == 2) {
							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == PLAYER_X) point = 0;
								else point = pow(10, curR - 1);
							}
							else point = 0;
						}
						else if (curR == 5) point = 100000000;
						//_|_____|O


						else if (!checkinside(i + di[k] * 5, j + dj[k] * 5) ||
							board[i + di[k] * 5][j + dj[k] * 5] == PLAYER_X) {
							//_|_____|O
							if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) {
								//O|XXX__|O
								if (!checkinside(i - di[k], j - dj[k]) ||
									board[i - di[k]][j - dj[k]] == PLAYER_X) point = pow(10, curR - 2) + 2;
								//_|X_XX_|O
								else point = pow(10, curR - 1);

							}
							//_|X___X|O
							else  point = pow(10, curR - 2) + 2;

						}

						//_____|_
						else if (board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {

							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == EMPTY) point = pow(10, curR - 1);
								else point = pow(10, curR - 2) + 3;
							}
							else point = pow(10, curR - 2) + 2;

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
	return Game::CheckWinRow();
}
bool Game15x15bot::CheckWinCol() {
	return Game::CheckWinCol();
}
bool Game15x15bot::CheckWinDiag2() {
	return Game::CheckWinDiag2();
}
bool Game15x15bot::CheckWinDiag1() {
	return Game::CheckWinDiag1();
}

void Game15x15bot::RenderEndStage() {
	Game::RenderEndStage();

}

