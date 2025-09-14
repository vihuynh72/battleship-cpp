#include "../include/space.h"
#include "../../../board/include/board.h"
#include "../../../ship/include/ship.h"
#include <iostream>
#include <string>

using namespace std;

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
    /*
    Check if the ship can be placed at the given position without going out of bounds or overlapping other ships.

    1. Check if the ship fits within the board boundaries based on its direction and length. Horizontal ships extend to the right, vertical ships extend downwards.

    2. Check each cell the ship would occupy to ensure it is empty (i.e., contains "[ ]").
    */
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