#include "../../board/board.h"
#include <iostream>

using namespace std;

bool checkAllShipsSunk(Board &board) {
    if (board.getTotalShips() == 0) {
        return true; // No ships on board
    }
    return false; // Placeholder, actual implementation needed
}