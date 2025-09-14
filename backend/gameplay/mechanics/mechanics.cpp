#include "board.h"
#include "ship.h"
#include "mechanics.h"

// Main Game Control functions
void startNewGame() {

}

void endGame() {
    
}

// Main Game Mechanics functions

Board addShipToBoard(Board &board, Ship &ship, int row, int col, string direction) {
    
}

Board attackShipOnBoard(Board &board, int row, int col) {
    
}

// Helper functions

bool checkOutOfBounds(Board &board, Ship &ship, int row, int col) {
    
}

bool checkOverlap(Board &board, Ship &ship, int row, int col, string direction) {
    
}

// Check for sunk ships

bool checkShipSunk(Ship &ship) {
    return ship.isSunk();    
}

bool checkAllShipsSunk(Board &board) {
    if (board.getTotalShips() == 0) {
        return true; // No ships on board
    }
}