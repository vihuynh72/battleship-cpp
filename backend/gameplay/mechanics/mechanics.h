#ifndef MECHANICS_H
#define MECHANICS_H

#include "../board/board.h"
#include "../ship/ship.h"
#include <string>

// Main Game Control functions
void startNewGame();
void endGame();

// Main Game Mechanics functions
Board addShipToBoard(Board&, Ship&, int, int, std::string);
Board attackShipOnBoard(Board&, int, int);

// Helper functions
bool checkEmptyCell(std::string);
bool checkOutOfBounds(Board&, int, int);
bool checkAvailableSpace(Board&, Ship&, int, int, std::string);

// Check for sunk ships
bool checkShipSunk(Ship&);
bool checkAllShipsSunk(Board&);

#endif // MECHANICS_H