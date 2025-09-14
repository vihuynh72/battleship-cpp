#include "board.h"
#include "ship.h"
#include "mechanics.h"
#include <iostream>
#include <string>

using namespace std;

// Main Game Control functions
void startNewGame() {

}

void endGame() {
    
}

// Main Game Mechanics functions

Board addShipToBoard(Board &board, Ship &ship, int row, int col, string direction) {
    return board; // Placeholder, actual implementation needed
}

Board attackShipOnBoard(Board &board, int row, int col) {
    return board; // Placeholder, actual implementation needed
}

// Helper functions
bool checkEmptyCell(std::string cell) {
    return cell == "[ ]"; // Assuming "[ ]" represents an empty cell
}

bool checkOutOfBounds(Board &board, int row, int col) {
    if (row < 0 || row >= board.getBoard().size() || col < 0 || col >= board.getBoard()[0].size()) {
        return true; // Out of bounds
    }
    return false; // Within bounds
}

bool checkAvailableSpace(Board &board, Ship &ship, int row, int col, string direction) {
    // The logic is to have the ship if horizontal expand to right, vertical expand downwards
    if (direction == "horizontal") {
        for (int i = 0; i < ship.getLength(); i++) {
            if (checkOutOfBounds(board, row, col + i) || !checkEmptyCell(board.getBoard()[row][col + i])) {
                return false; // Out of bounds or cell not empty
            }
        }
    } else if (direction == "vertical") {
        for (int i = 0; i < ship.getLength(); i++) {
            if (checkOutOfBounds(board, row + i, col) || !checkEmptyCell(board.getBoard()[row + i][col])) {
                return false; // Out of bounds or cell not empty
            }
        }
    } else {
        return false; // Invalid direction
    }
    return true; // Space is available
}

// Check for sunk ships

bool checkShipSunk(Ship &ship) {
    return ship.checkIsSunk();    
}

bool checkAllShipsSunk(Board &board) {
    if (board.getTotalShips() == 0) {
        return true; // No ships on board
    }
    return false; // Placeholder, actual implementation needed
}