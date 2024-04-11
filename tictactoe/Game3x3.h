#pragma once
#include "Game.h"

class Game3x3 : public Game {
public:
	bool CheckWinRow(const int& x, const int& y);

	bool CheckWinCol(const int& x, const int& y);

	bool CheckWinDiag1(const int& x, const int& y);

	bool CheckWinDiag2(const int& x, const int& y);

	void RenderEndStage();
};

