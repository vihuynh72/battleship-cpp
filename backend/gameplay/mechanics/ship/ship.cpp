#include "../../board/board.h"
#include "../../ship/ship.h"
#include <iostream>
#include <string>

using namespace std;

Board addShipToBoard(Board &board, Ship &ship, int row, int col, string direction) {
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
        return board;
    }
}

Board attackShipOnBoard(Board &board, int row, int col) {
    if (!checkOutOfBounds(board, row, col)) {
        if (!checkEmptyCell(board.getBoard()[row][col])) {
            board.getBoard()[row][col] = "[X]"; // Hit
        } else {
            board.getBoard()[row][col] = "[.]"; // Miss
        }
    }
    return board;
}

bool checkShipSunk(Ship &ship) {
    return ship.checkIsSunk();    
}