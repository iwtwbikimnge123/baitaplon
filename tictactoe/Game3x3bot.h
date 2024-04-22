#pragma once
#include "Game3x3.h"

class Game3x3bot : public Game3x3 {
protected:
	int gameLevelStatus;
	int depth;

	Button base;
	Button chooseLevelMedium;
	Button chooseLevelHard;
public:
	Game3x3bot();
	int minimax(int depth_, bool isBotTurn, int alpha, int beta);
	virtual int value(bool isBotTurn);
	void logic(SDL_Event& e, bool& quit);
	void Click(int& timer);
	void HandleEvent(SDL_Event& e, bool& quit, int& timer);
	void RenderRunningstate();
};