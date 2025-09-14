#ifndef PREGAME_H
#define PREGAME_H

#include "../../gameplay/board/board.h"
#include "../../gameplay/ship/ship.h"

#include <string>
#include <vector>

void displayHome();
void displaySetup();
void startGame(Board&, Board&);

#endif // PREGAME_H