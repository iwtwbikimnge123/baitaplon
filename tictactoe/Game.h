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

	void HandleBeforeMenu(SDL_Event& e, bool& quit);

	void logic(SDL_Event& e, bool& quit);

	void Click(const int& x, const int& y, int& timer);

	virtual bool CheckWinRow(const int& x, const int& y);

	virtual bool CheckWinCol(const int& x, const int& y);

	virtual bool CheckWinDiag2(const int& x, const int& y);

	virtual bool CheckWinDiag1(const int& x, const int& y);

	bool CheckTie();

    void RenderRunningstate(const int& x, const int& y);

	void DrawXCell(const int& x, const int& y);

	void DrawOCell(const int& x, const int& y);

	void RenderEndStage();

	void CheckClickWinMenu(SDL_Event& e, bool& quit);
protected:
	int N;
	int CELL_WIDTH;
	int CELL_HEIGHT;
	int cntXwin;
	int cntOwin;

	Button continue_;
	Button return_;
	Button focusContinue;
	Button focusReturn;

	Player** board;
	Player player;
	GameState state;

	std::pair <int, int> winCells[5];
};