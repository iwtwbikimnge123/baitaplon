
#pragma once
#include "Game.h"

class Game15x15 : public Game {
public:
	bool CheckWinRow(const int& x, const int& y);

	bool CheckWinCol(const int& x, const int& y);

	bool CheckWinDiag1(const int& x, const int& y);

	bool CheckWinDiag2(const int& x, const int& y);
};
