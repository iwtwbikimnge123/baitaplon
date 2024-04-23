#include"Game3x3bot.h"

Game3x3bot::Game3x3bot():Game3x3() {
	gameLevelStatus = 1;
	depth = 1;
	numOfmoves = 0;

	base.SetButtonType(BASE);
	base.SetPath();
	base.SetRect(85, 10, 85, 30);

	chooseLevelMedium.SetButtonType(SWITCHLEVEL_MEDIUM);
	chooseLevelMedium.SetPath();
	chooseLevelMedium.SetRect(300, 15, 85, 35);

	chooseLevelHard.SetButtonType(SWITCHLEVEL_HARD);
	chooseLevelHard.SetPath();
	chooseLevelHard.SetRect(377, 15, 85, 35);

	
}

int Game3x3bot::minimax(int depth_, bool isBotTurn, int alpha, int beta) {
	if (CheckWinCol() || CheckWinRow() || CheckWinDiag1() || CheckWinDiag2()) {
		if (isBotTurn) return INT_MIN;
		else return INT_MAX;
	}
	else if (CheckTie()) return 0;

	if (depth_ == 0) return value(isBotTurn);

	if (isBotTurn) {
		int res = INT_MIN;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == EMPTY) {
					int tmpX = x;
					int tmpY = y;
					x = j;
					y = i;
					board[i][j] = PLAYER_O;
					int score = minimax(depth_ - 1, false, alpha, beta);
					x = tmpX;
					y = tmpY;
					board[i][j] = EMPTY;
					alpha = std::max(alpha, score);
					if (alpha >= beta) return alpha;
				}
			}
		}
		return alpha;
	}
	else {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == EMPTY) {
					int tmpX = x;
					int tmpY = y;
					x = j;
					y = i;
					board[i][j] = PLAYER_X;
					int score = minimax(depth_ - 1, true, alpha, beta);
					x = tmpX;
					y = tmpY;
					board[i][j] = EMPTY;
					beta = std::min(beta, score);
					if (alpha >= beta) return beta;
				}
			}
		}
		return beta;
	}
}

void Game3x3bot::logic(SDL_Event& e, bool& quit) {
	
	while (menuType != STARTMENU && !quit) {
		if (state == RUNNING_STATE) {
			Uint32 starttime = SDL_GetTicks() / 1000;

			while (!quit && state == RUNNING_STATE && menuType != STARTMENU) {
				
				RenderRunningstate();

				SDL_RenderPresent(gRenderer);

				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

				if (player == PLAYER_X) {
					HandleEvent(e, quit, timer);
				}
				else if (player == PLAYER_O) {
					//chon buoc toi uu
					int res = INT_MIN;
					std::vector<std::pair<int, int>> sameRes;

					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							if (board[i][j] == EMPTY) {
								board[i][j] = PLAYER_O; 
								int tmpX = x;
								int tmpY = y;
								x = j;
								y = i;
								int score = minimax(depth, false, INT_MIN, INT_MAX);
								board[i][j] = EMPTY;
								std::cout << score << std::endl;
								if (res == score) {
									sameRes.push_back(std::make_pair(i, j));
								}
								else if (res < score) {
									res = score;
									std::vector<std::pair<int, int>> emptyVector;
									sameRes = emptyVector;
									sameRes.push_back(std::make_pair(i, j));
								}
								else {
									x = tmpX;
									y = tmpY;
								}
							}
						}
					}

					std::cout << "final score:"<< res << std::endl;
					srand(time(NULL));
					int num = rand() % sameRes.size();
					y = sameRes[num].first;
					x = sameRes[num].second;

					moves.push_back(std::make_pair(std::make_pair(y, x), player));

					board[y][x] = PLAYER_O;
					player = PLAYER_X;

					numOfmoves++;
				}
				if (CheckWinCol() || CheckWinRow() || CheckWinDiag1() || CheckWinDiag2()) {
					if (player == PLAYER_O) state = X_WON_STATE;
					else state = O_WON_STATE;
					break;
				}
				else if (CheckTie()) {
					state = TIE_STATE;
					break;
				}

				Uint32 finaltime = SDL_GetTicks() / 1000;
				if (finaltime - starttime >= 1) {
					timer--;
					starttime = SDL_GetTicks() / 1000;
				}

				if (timer == 0) {
					state = O_WON_STATE;
					timer = 45;
				}
			}
		}

		if (state == X_WON_STATE || state == O_WON_STATE || state == TIE_STATE) {
			x = y = -1;
			RenderEndStage();
		}
		while (!quit && (state == X_WON_STATE || state == O_WON_STATE || state == TIE_STATE)) {
			CheckClickWinMenu(e, quit);
		}
	}
}

void Game3x3bot::Click(int& timer) {
	if (board[y][x] == EMPTY) {

		Mix_PlayChannel(-1, gChunk_click, 0);

		moves.push_back(std::make_pair(std::make_pair(y, x), player));

		numOfmoves++;

		timer = 45;
		player = PLAYER_O;
		board[y][x] = PLAYER_X;
	}
}

void Game3x3bot::HandleEvent(SDL_Event& e, bool& quit, int& timer) {
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			quit = true;
			return;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (CheckClick(chooseLevelMedium.GetRect(), e.button.x, e.button.y) && gameLevelStatus == 2) {

				//text
				Text deleteScore;
				if (!deleteScore.OpenFont(15, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				deleteScore.SetText("switching level will delete all the points");
				deleteScore.SetColor(black);

				Text areYouSure;
				if (!areYouSure.OpenFont(18, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				areYouSure.SetText("are you sure?");
				areYouSure.SetColor(black);

				//check yes no
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gRenderer);

				RenderRunningstate();
				DrawGrid();
				yes.RenderButton();
				no.RenderButton();
				deleteScore.RenderText(35, 330);
				areYouSure.RenderText(165, 360);

				SDL_RenderPresent(gRenderer);

				bool isContinue = false;
				while (!quit) {

					bool isBreak = false;
					while (SDL_PollEvent(&e)) {

						if (e.type == SDL_QUIT) {
							quit = true;
							return;
						}
						else if (e.type == SDL_MOUSEBUTTONDOWN) {
							if (CheckClick(yes.GetRect(), e.button.x, e.button.y)) {
								isBreak = true;
								break;
							}
							else if (CheckClick(no.GetRect(), e.button.x, e.button.y)) {

								Mix_PlayChannel(-1, gChunk, 0);

								isBreak = true;
								isContinue = true;
								break;
							}
						}
					}
					if (isBreak) break;
				}

				if (isContinue) {

					RenderRunningstate();
					SDL_RenderPresent(gRenderer);
					continue;
				}


				//render new level
				Mix_PlayChannel(-1, gChunk_toggle, 0);

				boardColor = green;
				gameLevelStatus = 0;

				int x = chooseLevelHard.GetRect().x - 19;
				while (x >= chooseLevelMedium.GetRect().x) {

					Uint32 frameStart = SDL_GetTicks();
					Uint32 frameTime;

					base.SetRect(x, chooseLevelMedium.GetRect().y, chooseLevelMedium.GetRect().w, chooseLevelMedium.GetRect().h);

					RenderRunningstate();
					base.RenderButton();

					SDL_RenderPresent(gRenderer);
					x -= 19;

					frameTime = SDL_GetTicks() - frameStart;
					if (frameDelay > frameTime) {
						SDL_Delay(frameDelay - frameTime);
					}

				}
				gameLevelStatus = 1;
				cntOwin = cntXwin = 0;
				timer = 45;
				depth = 1;

				InitBoard();
			}
			else if (CheckClick(chooseLevelHard.GetRect(), e.button.x, e.button.y) && gameLevelStatus == 1) {

				Text deleteScore;
				if (!deleteScore.OpenFont(15, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				deleteScore.SetText("switching level will delete all the points");
				deleteScore.SetColor(black);

				Text areYouSure;
				if (!areYouSure.OpenFont(18, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				areYouSure.SetText("are you sure?");
				areYouSure.SetColor(black);

				//check yes no
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gRenderer);

				RenderRunningstate();
				DrawGrid();
				yes.RenderButton();
				no.RenderButton();
				deleteScore.RenderText(35, 330);
				areYouSure.RenderText(165, 360);

				SDL_RenderPresent(gRenderer);

				bool isContinue = false;
				while (!quit) {

					bool isBreak = false;
					while (SDL_PollEvent(&e)) {

						if (e.type == SDL_QUIT) {
							quit = true;
							return;
						}
						else if (e.type == SDL_MOUSEBUTTONDOWN) {
							if (CheckClick(yes.GetRect(), e.button.x, e.button.y)) {
								isBreak = true;
								break;
							}
							else if (CheckClick(no.GetRect(), e.button.x, e.button.y)) {

								Mix_PlayChannel(-1, gChunk, 0);

								isBreak = true;
								isContinue = true;
								break;
							}
						}
					}
					if (isBreak) break;
				}

				if (isContinue) {

					RenderRunningstate();
					SDL_RenderPresent(gRenderer);
					continue;
				}


				Mix_PlayChannel(-1, gChunk_toggle, 0);

				boardColor = lightRed;
				gameLevelStatus = 0;

				int x = chooseLevelMedium.GetRect().x + 19;
				while (x <= chooseLevelHard.GetRect().x) {

					Uint32 frameStart = SDL_GetTicks();
					Uint32 frameTime;

					base.SetRect(x, chooseLevelMedium.GetRect().y, chooseLevelMedium.GetRect().w, chooseLevelMedium.GetRect().h);

					RenderRunningstate();
					base.RenderButton();

					SDL_RenderPresent(gRenderer);
					x += 19;

					frameTime = SDL_GetTicks() - frameStart;
					if (frameDelay > frameTime) {
						SDL_Delay(frameDelay - frameTime);
					}
				}
				gameLevelStatus = 2;
				cntOwin = cntXwin = 0;
				timer = 45;
				depth = 2;

				InitBoard();
			}
			else if (CheckClick(home.GetRect(), e.button.x, e.button.y)) {

				Text deleteScore;
				if (!deleteScore.OpenFont(15, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				deleteScore.SetText("return to home will delete all the points");
				deleteScore.SetColor(black);

				Text areYouSure;
				if (!areYouSure.OpenFont(18, "img/gamecuben.ttf")) {
					std::cout << SDL_GetError();
					return;
				}
				areYouSure.SetText("are you sure?");
				areYouSure.SetColor(black);

				//check yes no
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gRenderer);

				RenderRunningstate();
				DrawGrid();
				yes.RenderButton();
				no.RenderButton();
				deleteScore.RenderText(35, 330);
				areYouSure.RenderText(165, 360);

				SDL_RenderPresent(gRenderer);

				bool isContinue = false;
				while (!quit) {

					bool isBreak = false;
					while (SDL_PollEvent(&e)) {

						if (e.type == SDL_QUIT) {
							quit = true;
							return;
						}
						else if (e.type == SDL_MOUSEBUTTONDOWN) {
							if (CheckClick(yes.GetRect(), e.button.x, e.button.y)) {
								isBreak = true;
								break;
							}
							else if (CheckClick(no.GetRect(), e.button.x, e.button.y)) {

								Mix_PlayChannel(-1, gChunk, 0);

								isBreak = true;
								isContinue = true;
								break;
							}
						}
					}
					if (isBreak) break;
				}

				if (isContinue) {

					RenderRunningstate();
					SDL_RenderPresent(gRenderer);
					continue;
				}

				Mix_PlayChannel(-1, gChunk, 0);

				menuType = STARTMENU;
				break;
			}
			else if (CheckClick(speaker.GetRect(), e.button.x, e.button.y)) {

				Mix_PlayChannel(-1, gChunk, 0);

				if (Mix_PausedMusic() == 1) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}
			else if (e.button.y >= (SCREEN_HEIGHT - SCREEN_WIDTH)) {
				x = e.button.x / CELL_WIDTH;
				y = (e.button.y - (SCREEN_HEIGHT - SCREEN_WIDTH)) / CELL_HEIGHT;
				Click(timer);
			}

			RenderRunningstate();
			SDL_RenderPresent(gRenderer);
		}
	}
}

void Game3x3bot::RenderRunningstate() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, boardColor.r, boardColor.g, boardColor.b, boardColor.a);

	SDL_Rect rect;

	rect.x = 0;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH;
	rect.w = rect.h = SCREEN_WIDTH;

	SDL_RenderFillRect(gRenderer, &rect);

	rect.x = 50;
	rect.y = 67;
	rect.w = 120;
	rect.h = 50;
	if (player == PLAYER_X) {
		RenderImage("img/logoX2.png", rect);
		rect.x = 325;
		RenderImage("img/logoO.png", rect);
	}
	else {
		RenderImage("img/logoX.png", rect);
		rect.x = 325;
		RenderImage("img/logoO2.png", rect);
	}

	//point
	Text xPoint;
	Text oPoint;
	if (!xPoint.OpenFont(21, "img/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	xPoint.SetText(std::to_string(cntXwin));
	xPoint.SetColor(white);
	xPoint.RenderText(132, 80);

	if (!oPoint.OpenFont(21, "img/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	oPoint.SetText(std::to_string(cntOwin));
	oPoint.SetColor(white);
	oPoint.RenderText(345, 80);

	//board
	DrawGrid();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == PLAYER_X) DrawXCell(j, i);
			else if (board[i][j] == PLAYER_O) DrawOCell(j, i);
		}
	}
	rect.x = CELL_WIDTH * x;
	rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * y;
	rect.w = CELL_WIDTH;
	rect.h = CELL_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(gRenderer, &rect);

	//button
	home.RenderButton();
	speaker.RenderButton();

	//time
	std::string displaytime = "00:" + std::to_string(timer);
	Text timetext;
	if (!timetext.OpenFont(15, "img/gamecuben.ttf")) {
		std::cout << SDL_GetError();
		return;
	}
	timetext.SetColor(red);
	timetext.SetText(displaytime);

	if (player == PLAYER_X) {
		timetext.RenderText(80, 120);
	}
	
	//nut level
	rect = { 295, 10, 170, 45 };
	RenderImage("img/nut9.png", rect);

	if (gameLevelStatus == 1) {
		chooseLevelMedium.RenderButton();
	}
	else if (gameLevelStatus == 2) {
		chooseLevelHard.RenderButton();
	}
	if (player == PLAYER_O) {
		Text wait;
		wait.OpenFont(15, "img/gamecuben.ttf");
		wait.SetColor(red);
		wait.SetText("calculating...");
		wait.RenderText(320, 120);
	}
}

void Game3x3bot::RenderEndStage() {
	RenderRunningstate();
	if (state == O_WON_STATE) {
		cntOwin++;

		for (int i = 0; i < 3; i++) {
			SDL_Rect rect;
			rect.x = CELL_WIDTH * winCells[i].second;
			rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * winCells[i].first;
			rect.w = CELL_WIDTH;
			rect.h = CELL_HEIGHT;

			RenderImage("img/winO.png", rect);
		}
	}
	else if (state == X_WON_STATE) {
		cntXwin++;

		for (int i = 0; i < 3; i++) {
			SDL_Rect rect;
			rect.x = CELL_WIDTH * winCells[i].second;
			rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * winCells[i].first;
			rect.w = CELL_WIDTH;
			rect.h = CELL_HEIGHT;

			RenderImage("img/winX.png", rect);
		}
	}
	else if (state = TIE_STATE) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				SDL_Rect rect;
				rect.x = CELL_WIDTH * i;
				rect.y = SCREEN_HEIGHT - SCREEN_WIDTH + CELL_HEIGHT * j;
				rect.w = CELL_WIDTH;
				rect.h = CELL_HEIGHT;

				if (board[j][i] == PLAYER_X) RenderImage("img/tieX.png", rect);
				else RenderImage("img/tieO.png", rect);
			}
		}
	}

	SDL_RenderPresent(gRenderer);

	SDL_Delay(300);

	RenderEndMenu();

	Mix_PlayChannel(-1, gChunk_over, 0);

}

void Game3x3bot::RenderEndMenu() {
	SDL_SetRenderDrawColor(gRenderer, 176, 224, 208, 0);
	SDL_RenderClear(gRenderer);

	SDL_Rect rect = { 25, 150, 450, 170 };
	if (state == X_WON_STATE) {
		RenderImage("img/youwin.png", rect);
	}
	else if (state == O_WON_STATE) {
		RenderImage("img/youlose.png", rect);
	}
	else RenderImage("img/tie.png", rect);

	return_.RenderButton();
	continue_.RenderButton();
	replay.RenderButton();

	SDL_RenderPresent(gRenderer);

}

int Game3x3bot::value(bool isBotTurn) {
	if (CheckWinCol() || CheckWinRow() || CheckWinDiag1() || CheckWinDiag2()) {
		if (isBotTurn) return INT_MIN;
		else return INT_MAX;
	}
	else return 0;
}