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
        // Use ship index as identifier to handle ships with same first letter
        int shipIndex = board.getShipList().size(); // Current size = index of new ship
        string shipSymbol = "[" + to_string(shipIndex) + "]"; // e.g., "[0]", "[1]", etc.
        
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
        string cell = board.getBoard()[row][col];
        if (!checkEmptyCell(cell)) {
            // Mark X for hit
            board.getBoard()[row][col] = "[X]";
            
            // Extract ship index from cell symbol (e.g., "[0]" -> 0)
            // Cell format is "[number]", so extract the number
            if (cell.length() >= 3 && cell[0] == '[' && cell[cell.length()-1] == ']') {
                string indexStr = cell.substr(1, cell.length() - 2);
                int shipIndex = stoi(indexStr);
                
                // Increment hit count for the correct ship
                vector<Ship>& ships = board.getShipList();
                if (shipIndex >= 0 && shipIndex < ships.size()) {
                    ships[shipIndex].incrementHitCount();
                }
            }
        } else {
            board.getBoard()[row][col] = "[O]"; // Miss
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