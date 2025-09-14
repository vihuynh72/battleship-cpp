#ifndef INGAME_H
#define INGAME_H

#include "../../../gameplay/board/board.h"
#include "../../../gameplay/ship/ship.h"

void ingame(Board&, Board&);

void playerTurn(Board&);
void attackTurn(Board&, int, int);

#endif // INGAME_H
