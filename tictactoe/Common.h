#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <algorithm>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;

extern Mix_Music* gMusic;
extern Mix_Chunk* gChunk;
extern Mix_Chunk* gChunk_toggle;
extern Mix_Chunk* gChunk_click;
extern Mix_Chunk* gChunk_over;

const SDL_Color white = { 255, 255, 255, 255 };
const SDL_Color red = { 255, 0, 0, 0 };
const SDL_Color green = { 144, 238, 144, 0 };
const SDL_Color black = { 0, 0, 0, 0 };
const SDL_Color grey = { 128, 128, 128, 0 };
const SDL_Color lightRed = { 255, 192, 203, 0};


const int SCREEN_WIDTH = 495;
const int SCREEN_HEIGHT = 640;
const int FPS = 20;
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
	PLAY3x3_2PLAYER,
	PLAY15X15_2PLAYER,
	PLAY3X3_WITHBOT,
	PLAY15X15_WITHBOT,
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
	FOCUS_SPEAKER,

	CONTINUE,
	RETURN,
	FOCUS_CONTINUE,
	FOCUS_RETURN,

	YES,
	NO,
};

extern MenuType menuType;

bool Init();

void RenderImage(std::string path, SDL_Rect rect);

bool CheckClick(SDL_Rect rect, int x, int y);

void Close();