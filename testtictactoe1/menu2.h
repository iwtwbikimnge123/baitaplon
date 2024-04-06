#pragma once
#include "text.h"

void RenderMenu2(Text returnmenu1, Text gototictactoe, Text goto5x5, Text goto15x15, SDL_Color colorreturn, SDL_Color colortictactoe, SDL_Color color5x5, SDL_Color color15x15);

void CheckClickMenu2(SDL_Event& e, bool& quit, Text returnMenu1, Text goToTictactoe, Text goTo5x5, Text goTo15x15);