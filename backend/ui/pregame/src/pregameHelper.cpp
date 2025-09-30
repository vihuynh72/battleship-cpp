#include "../include/pregameHelper.h"
#include "../../ingame/include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"

#include <iostream>

using namespace std;

vector<int> dimensionSetup() {
    string dimension;
    cout << "Enter board dimensions (RowsxColumns) separated by 'x' (e.g., 10x10): ";
    cin >> dimension;
    // find x or X
    size_t xPos = dimension.find('x');
    if (xPos == string::npos) { // if 'x' not found
        if ((xPos = dimension.find('X')) == string::npos) {
            cout << "Invalid format. Please use the format RowsxColumns (e.g., 10x10).\n" << endl;
            return dimensionSetup();
        }
    }

    int rows = stoi(dimension.substr(0, xPos));
    int cols = stoi(dimension.substr(xPos + 1));
    return {rows, cols};
}


vector<string> playerSetup(bool isPvC) {
    string player1;
    string player2;

    if (isPvC) {
        cout << "Enter Your Name: ";
        cin >> player1;
        return {player1, "Computer"};
    } else {
        cout << "Enter Player 1 Name: ";
        cin >> player1;

        cout << "Enter Player 2 Name: ";
        cin >> player2;
        return {player1, player2};
    }
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

int lengthSetup() {
    int length;
    cout << "Enter ship length (2-5): ";
    cin >> length;
 
    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(10000, '\n'); // Ignore the invalid input
        cout << "Invalid input. Please enter a number between 2 and 5.\n" << endl;
        return lengthSetup();
    }
    
    if (length < 2 || length > 5) {
        cout << "Invalid length. Please enter a value between 2 and 5.\n" << endl;
        return lengthSetup();
    }
    return length;
}
  
Ship shipSetup(Board& board) {
    string name;
    string direction;
    int length;
    int ship_x_coord, ship_y_coord;
    
    cout << "Enter ship name: ";
    cin >> name;
    
    direction = directionSetup();
    length = lengthSetup();

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

    if (!validateCoord(coord, board)) {
        return coordinateSetup(board, ship);
    }

    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;
    
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