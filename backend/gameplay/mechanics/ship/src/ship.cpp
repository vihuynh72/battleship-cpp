#include "../include/ship.h"
#include "../../../board/include/board.h"
#include "../../../ship/include/ship.h"
#include "../../space/include/space.h"
#include <iostream>
#include <string>

using namespace std;

void addShipToBoard(Board &board, Ship &ship, int row, int col, string direction) {
    /*
    If direction is "horizontal", place the ship to the right from (row, col).
    If direction is "vertical", place the ship downwards from (row, col).
    */
    if (checkAvailableSpace(board, ship, row, col, direction)) {
        string shipSymbol = "[" + ship.getName().substr(0, 1) + "]"; // e.g., "[W]" for "Wok"
        if (direction == "horizontal") {
            for (int i = 0; i < ship.getLength(); i++) {
                board.getBoard()[row][col + i] = shipSymbol;
            }
        } else if (direction == "vertical") {
            for (int i = 0; i < ship.getLength(); i++) {
                board.getBoard()[row + i][col] = shipSymbol;
            }
        }
        board.addShip(ship);
    }
    board.updateBoard(board.getBoard());
}

void attackShipOnBoard(Board &board, int row, int col) {
    if (!checkOutOfBounds(board, row, col)) {
        if (!checkEmptyCell(board.getBoard()[row][col])) {
            board.getBoard()[row][col] = "[X]"; // Hit
        } else {
            board.getBoard()[row][col] = "[.]"; // Miss
        }
    }
    board.updateBoard(board.getBoard());
}

bool checkShipSunk(Ship &ship) {
    return ship.checkIsSunk();    
}

vector<Ship> getDefaultShips() { // Default ships with predefined names and lengths
    vector<Ship> defaultShips;
    defaultShips.push_back(Ship("Carrier", "horizontal", 5));
    defaultShips.push_back(Ship("Battleship", "horizontal", 4));
    defaultShips.push_back(Ship("Destroyer", "horizontal", 3));
    defaultShips.push_back(Ship("Submarine", "horizontal", 3));
    defaultShips.push_back(Ship("Frigate", "horizontal", 2));

    return defaultShips;
}