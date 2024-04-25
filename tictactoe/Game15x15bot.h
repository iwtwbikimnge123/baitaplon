#pragma once
#include "Game3x3bot.h"

class Game15x15bot : public Game3x3bot {
public:

	int value(bool isBotTurn);

	int value1();

	bool checkinside(int i, int j) {
		if (i < 0 || j < 0 || i >= N || j >= N) return false;
		return true;
	}

	bool CheckWinRow();

	bool CheckWinCol();

	bool CheckWinDiag1();

	bool CheckWinDiag2();

	void RenderEndStage();

};
