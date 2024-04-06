#pragma once
#pragma once
#include "Common.h"
#include "text.h" 

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

	void logic(SDL_Event& e, bool& quit);

	void Click(const int& x, const int& y, int& timer);


	virtual bool CheckWinRow(const int& x, const int& y);

	virtual bool CheckWinCol(const int& x, const int& y);

	virtual bool CheckWinDiag1(const int& x, const int& y);

	virtual bool CheckWinDiag2(const int& x, const int& y);

	bool CheckTie();

	void RenderRunningstate(const int& x, const int& y);

	void DrawXCell(const int& x, const int& y);

	void DrawOCell(const int& x, const int& y);

	void RenderEndStage(Text returnmenu2, Text continueplay);

	void CheckClickWinMenu(SDL_Event& e, bool& quit, Text returnmenu2, Text continueplay);
protected:
	int N;
	int CELL_WIDTH;
	int CELL_HEIGHT;
	Player** board;
	Player player;
	GameState state;
	std::pair <int, int> winCells[5];
};