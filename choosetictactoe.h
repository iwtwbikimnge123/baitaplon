#pragma once
#include "Common.h"
#include "text.h"

void RenderChooseTictactoe(Text goToTictactoe, Text PlayWithBot, Text Solo);

void CheckChooseTictactoe(SDL_Event& e, bool& quit, Text  goToTictactoe, Text PlayWithBot, Text Solo);