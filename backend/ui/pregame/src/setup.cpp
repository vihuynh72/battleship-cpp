#include "../include/setup.h"
#include "../../gameplay/board/board.h"
#include "../../gameplay/ship/ship.h"
#include "../../gameplay/mechanics/ship/ship.h"
#include "../../gameplay/mechanics/space/space.h"

#include <iostream>

using namespace std;

int dimensionSetup() {
    int dimension;
    cin >> dimension;
    if (dimension < 5 || dimension > 26) {
        cout << "Invalid dimension. Please enter a value between 5 and 26." << endl;
        return dimensionSetup();
    }
    return dimension;
}

string playerSetup() {
    string playerName;
    cin >> playerName;
    return playerName;
}
  
Ship shipSetup(Board& board) {
    string name;
    string direction;
    int length;
    int ship_x_coord, ship_y_coord;
    
    cout << "Enter ship name: ";
    cin >> name;
    cout << "Enter ship direction (horizontal/vertical): ";
    cin >> direction;
    cout << "Enter ship length (2-5): ";
    cin >> length;
    if (length < 2 || length > 5) {
        cout << "Invalid length. Please enter a value between 2 and 5." << endl;
        return shipSetup(board);
    }

    // Create and add ship to board
    Ship ship;
    ship.setShipProperties(name, direction, length);

    cout << "Enter ship starting X coordinate (0 to " << board.getColumns() - 1 << "): ";
    cin >> ship_x_coord;

    cout << "Enter ship starting Y coordinate (0 to " << board.getRows() - 1 << "): ";
    cin >> ship_y_coord;

    if (checkAvailableSpace(board, ship, ship_y_coord, ship_x_coord, direction) == false) {
        cout << "Invalid coordinates. Please try again." << endl;
        return shipSetup(board);
    }

    addShipToBoard(board, ship, ship_y_coord, ship_x_coord, direction);
    return ship;
}