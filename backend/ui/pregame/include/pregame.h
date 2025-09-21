#ifndef PREGAME_H
#define PREGAME_H

#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <string>
#include <vector>

void displayHome();
void displaySetup();

void personVsComputer();
void pvcQuickGame();

void promptBeginGame(Board&, Board&, bool);
#endif // PREGAME_H