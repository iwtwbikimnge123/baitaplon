#pragma once
#include "game.h"

class GameTictactoe : public Game {
public:
	bool CheckWinRow(const int& x, const int& y);

	bool CheckWinCol(const int& x, const int& y);

	bool CheckWinDiag1(const int& x, const int& y);

	bool CheckWinDiag2(const int& x, const int& y);
};
