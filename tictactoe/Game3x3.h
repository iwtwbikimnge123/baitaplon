#pragma once
#include "Game.h"

class Game3x3 : public Game {
public:
	bool CheckWinRow();

	bool CheckWinCol();

	bool CheckWinDiag1();

	bool CheckWinDiag2();

	void RenderEndStage();
};

