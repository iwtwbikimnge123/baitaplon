#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <algorithm>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;
extern Mix_Chunk* gChunk;

const SDL_Color white = { 255, 255, 255, 255 };
const SDL_Color red = { 255, 0, 0, 0 };
const SDL_Color green = { 0, 255, 0, 0 };
const SDL_Color black = { 0, 0, 0, 0 };


const int SCREEN_WIDTH = 495;
const int SCREEN_HEIGHT = 640;
const int FPS = 70;
const int frameDelay = 1000 / FPS;

enum Player {
	PLAYER_X,
	PLAYER_O,
	EMPTY,
};

enum GameState {
	X_WON_STATE,
	O_WON_STATE,
	TIE_STATE,
	RUNNING_STATE,
};

enum MenuType {
	STARTMENU,
	CHOOSETICTACTOE,
	PLAYTICTACTOE,
	PLAY5X5,
	PLAY15X15,
};

enum ButtonType {
	START,
	FOCUSSTART,

	BASE,

	CHOOSEPLAYER_1,
	CHOOSEPLAYER_2,

	CHOOSESIZE_3x3,
	CHOOSESIZE_15x15,

	SWITCHLEVEL_MEDIUM,
	SWITCHLEVEL_HARD,

	HOME,
	SPEAKER,
};

extern MenuType menuType;

bool Init();

void RenderImage(std::string path, SDL_Rect rect);

bool CheckClick(SDL_Rect rect, int x, int y);

void Close();
