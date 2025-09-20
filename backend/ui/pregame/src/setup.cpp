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

string directionSetup() {
    string direction;
    cout << "Enter ship direction (h for horizontal/v for vertical): ";
    cin >> direction;
    direction = (direction == "h" || direction == "H") ? "horizontal" : 
                (direction == "v" || direction == "V") ? "vertical" : "";

    if (direction == "") {
        cout << "Invalid direction. Please enter 'h' or 'v'.\n" << endl;
        return directionSetup();
    }
    return direction;
}
  
Ship shipSetup(Board& board) {
    string name;
    string direction;
    int length;
    int ship_x_coord, ship_y_coord;
    
    cout << "Enter ship name: ";
    cin >> name;
    
    direction = directionSetup();

    cout << "Enter ship length (2-5): ";
    cin >> length;
    if (length < 2 || length > 5) {
        cout << "Invalid length. Please enter a value between 2 and 5.\n" << endl;
        return shipSetup(board);
    }

    // Create and add ship to board
    Ship ship;
    ship.setShipProperties(name, direction, length);
    
    vector<int> shipCoord = coordinateSetup(board, ship);
    ship_y_coord = shipCoord[0];
    ship_x_coord = shipCoord[1];

    addShipToBoard(board, ship, ship_y_coord, ship_x_coord, direction);
    printBoard(board);
    cout << "Ship placed successfully!\n" << endl;
    return ship;
}

vector<int> coordinateSetup(Board& board, Ship& ship) {
    string coord;

    cout << "Enter desired coordinates (e.g., A5): ";
    cin >> coord;

    if (coord.length() < 2 || 
        !isalpha(coord[0]) || 
        !isdigit(coord[1]) || 
        (coord.length() == 3 && !isdigit(coord[2]))) {
        cout << "Invalid format. Please use the format LetterNumber (e.g., A5).\n" << endl;
        return coordinateSetup(board, ship);
    }
    
    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;
    
    if (checkOutOfBounds(board, row, col) || 
        checkEmptyCell(board.getBoard()[row][col]) == false) {
        cout << "Invalid coordinates. Please try again.\n" << endl;
        return coordinateSetup(board, ship);
    }
    return {row, col};
}

void placeShip(Board& board, int row, int col) {
    for (int i = 0; i < 5; i++) {
        cout << "----------------------------------------" << endl;
        cout << "Placing ship number " << i + 1 << "\n" << endl;
        shipSetup(board);
    }
    cout << "\nAll ships placed for " << board.getPlayerName() << "!" << endl;
}