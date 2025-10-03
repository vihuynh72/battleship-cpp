#include "../include/board.h"
#include "../../../board/include/board.h"
#include <iostream>

using namespace std;

bool checkAllShipsSunk(Board &board) {
    vector<Ship>& ships = board.getShipList();

    if (ships.empty()) {
        return false; // No ships on the board
    }

    for (Ship& ship : ships) {
        if (!ship.checkIsSunk()) {
            return false; // Found a ship that is not sunk
        }
    }
    return true; // All ships are sunk
}