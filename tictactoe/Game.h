#pragma once

#include "Common.h"
#include "text.h" 
#include "SwitchButton.h"

class Game {
public:
	Game();
	~Game();

	void DrawGrid();

	void SetN(const int& n) {
		N = n;
		CELL_WIDTH = CELL_HEIGHT = SCREEN_WIDTH / N;
	}

	void SetTimeForEachMove(const int& n) {
		timeForEachMove = n;
	}

	void InitBoard();

	void ChangeTurn();

	virtual void logic(SDL_Event& e, bool& quit);

	virtual void Click();

	virtual bool CheckWinRow();

	virtual bool CheckWinCol();

	virtual bool CheckWinDiag2();

	virtual bool CheckWinDiag1();

	bool CheckTie();

	void RenderRunningstate();

	void DrawXCell(const int& i, const int& j);

	void DrawOCell(const int& i, const int& j);

	virtual void RenderEndStage();

	virtual void RenderEndMenu();

	void CheckClickWinMenu(SDL_Event& e, bool& quit);

	virtual void HandleEvent(SDL_Event& e, bool& quit);
protected:
	int N;
	int CELL_WIDTH;
	int CELL_HEIGHT;
	int cntXwin;
	int cntOwin;
	int x;
	int y;
	int timer;
	int timeForEachMove;
	int numOfmoves;

	Button continue_;
	Button return_;
	Button home;
	Button speaker;
	Button no;
	Button yes;
	Button replay;
	Button next;
	Button previous;

	Player** board;
	Player player;
	GameState state;

	SDL_Color boardColor;

	std::pair <int, int> winCells[5];
	std::vector <std::pair <std::pair <int, int>, Player>> moves;
};