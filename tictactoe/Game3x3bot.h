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
	virtual int value1();
	virtual int value(bool isBotTurn);

	void logic(SDL_Event& e, bool& quit);
	void Click();

	void HandleEvent(SDL_Event& e, bool& quit);

	void RenderRunningstate();
	void RenderEndStage();
	void RenderEndMenu();
};