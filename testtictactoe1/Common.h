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
const SDL_Color white = { 255, 255, 255, 0 };
const SDL_Color red = { 255, 0, 0, 0 };
const SDL_Color green = { 0, 255, 0, 0 };
const SDL_Color black = { 0, 0, 0, 0 };
const SDL_Color grey = { 220, 220, 220, 0 };


const int SCREEN_WIDTH = 495;
const int SCREEN_HEIGHT = 640;

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
	CHOOSEMAP,
	CHOOSETICTACTOE,
	PLAYTICTACTOE,
	PLAY5X5,
	PLAY15X15,
};

extern MenuType menutype;

bool Init();

void RenderImage(std::string path);

void RenderImage(std::string path, SDL_Rect rect);

bool CheckClick(SDL_Rect rect, int x, int y);

void Close();
