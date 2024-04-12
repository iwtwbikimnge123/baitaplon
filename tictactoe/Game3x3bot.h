#pragma once
#include "Game3x3.h"

class Game3x3bot : public Game3x3 {
private:
	int gamemode;
public:
	int minimax(int depth, bool isBotTurn, int alpha, int beta, int x, int y);
	void logic(SDL_Event& e, bool& quit);
	void Click(const int& x, const int& y, int& timer);
};