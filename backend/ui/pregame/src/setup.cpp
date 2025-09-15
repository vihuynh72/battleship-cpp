#include "../include/setup.h"
#include "../../ingame/include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"

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
    cout << "Enter ship direction (h for horizontal/v for vertical): ";
    cin >> direction;
    direction = (direction == "h" || direction == "H") ? "horizontal" : 
                (direction == "v" || direction == "V") ? "vertical" : "";

    if (direction == "") {
        cout << "Invalid direction. Please enter 'h' or 'v'.\n" << endl;
        return shipSetup(board);
    }

    cout << "Enter ship length (2-5): ";
    cin >> length;
    if (length < 2 || length > 5) {
        cout << "Invalid length. Please enter a value between 2 and 5.\n" << endl;
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
        cout << "Invalid coordinates. Please try again.\n" << endl;
        return shipSetup(board);
    }

    addShipToBoard(board, ship, ship_y_coord, ship_x_coord, direction);
    printBoard(board);
    cout << "Ship placed successfully!\n" << endl;
    return ship;
}

void placeShip(Board& board, int row, int col) {
    for (int i = 0; i < 5; i++) {
        cout << "----------------------------------------" << endl;
        cout << "Placing ship number " << i + 1 << "\n" << endl;
        shipSetup(board);
    }
    cout << "\nAll ships placed for " << board.getPlayerName() << "!" << endl;
}