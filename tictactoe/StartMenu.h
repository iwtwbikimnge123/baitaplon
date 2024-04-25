#pragma once
#include "SwitchButton.h"

class MenuStart{
private:
	Button start;
	Button choosePlayer1;
	Button choosePlayer2;
	Button chooseSize3x3;
	Button chooseSize15x15;
	Button base;
	Button speaker;
	int choosePlayerStatus;
	int chooseSizeStatus;
public:
	MenuStart();
	~MenuStart();
	void RenderBaseMenu();
	void HandleEvent(SDL_Event& e, bool& quit);
	void RestartMenu();
};
