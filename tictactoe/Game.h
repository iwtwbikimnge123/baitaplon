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

	void InitBoard();

	void ChangeTurn();

	virtual void logic(SDL_Event& e, bool& quit);

	virtual void Click(int& timer);

	virtual bool CheckWinRow();

	virtual bool CheckWinCol();

	virtual bool CheckWinDiag2();

	virtual bool CheckWinDiag1();

	bool CheckTie();

	void RenderRunningstate();

	void DrawXCell(const int& i, const int& j);

	void DrawOCell(const int& i, const int& j);

	virtual void RenderEndStage();

	void CheckClickWinMenu(SDL_Event& e, bool& quit);

	virtual void HandleEvent(SDL_Event& e, bool& quit, int& timer);
protected:
	int N;
	int CELL_WIDTH;
	int CELL_HEIGHT;
	int cntXwin;
	int cntOwin;
	int x;
	int y;

	Button continue_;
	Button return_;
	Button focusContinue;
	Button focusReturn;
	Button home;
	Button speaker;

	Player** board;
	Player player;
	GameState state;

	SDL_Color boardColor;
	std::pair <int, int> winCells[5];
};