#ifndef MECHANICS_H
#define MECHANICS_H

#include "../board/board.h"
#include "../ship/ship.h"
#include <string>

// Main Game Control functions
void startNewGame();
void endGame();

bool checkAllShipsSunk(Board&);

#endif // MECHANICS_H