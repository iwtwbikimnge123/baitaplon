#pragma once
#include "Game3x3.h"

class Game3x3bot : public Game3x3 {
protected:
	int gameLevelStatus;
	int depth;
	int depthMedium;
	int depthHard;

	Button base;
	Button chooseLevelMedium;
	Button chooseLevelHard;
public:
	Game3x3bot();
	void SetDepthMedium(const int& n) {
		depthMedium = n;
	}
	void SetDepthHard(const int& n) {
		depthHard = n;
	}

	int minimax(int depth_, bool isBotTurn, int alpha, int beta);
	virtual int value(bool isBotTurn);
	void chooseBestMove();

	void logic(SDL_Event& e, bool& quit);
	void Click();

	void HandleEvent(SDL_Event& e, bool& quit);

	void RenderRunningstate();
	void RenderEndStage();
	void RenderEndMenu();
};