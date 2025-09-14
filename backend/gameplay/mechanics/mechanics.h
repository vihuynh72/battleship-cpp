#ifndef MECHANICS_H
#define MECHANICS_H
#include "../board/board.h"
#include "../ship/ship.h"

// Main Game Control functions
void startNewGame();
void endGame();

// Main Game Mechanics functions
Board addShipToBoard(Board&, Ship&, int, int, string);
Board attackShipOnBoard(Board&, int, int);

// Helper functions
bool checkOutOfBounds(Board&, Ship&, int, int);
bool checkOverlap(Board&, Ship&, int, int, string);

// Check for sunk ships
bool checkShipSunk(Ship&);
bool checkAllShipsSunk(Board&);

#endif // MECHANICS_H