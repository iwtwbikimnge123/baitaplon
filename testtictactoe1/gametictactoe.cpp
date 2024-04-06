#include "gametictactoe.h"

bool GameTictactoe::CheckWinRow(const int& x, const int& y) {
	for (int i = 0; i < N; i++) {
		if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
	}
	return false;
}

bool GameTictactoe::CheckWinCol(const int& x, const int& y) {
	for (int i = 0; i < N; i++) {
		if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
	}
	return false;
}

bool GameTictactoe::CheckWinDiag1(const int& x, const int& y) {
	if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
	return false;
}

bool GameTictactoe::CheckWinDiag2(const int& x, const int& y) {
	if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
	return false;
}