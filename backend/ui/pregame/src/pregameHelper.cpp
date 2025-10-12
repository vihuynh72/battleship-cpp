#include "../include/pregameHelper.h"
#include "../../ingame/include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"
#include "../../common/include/uiTheme.h"

#include <iostream>
#include <limits>

using namespace std;
using namespace ui::theme;

vector<int> dimensionSetup() {
    string dimension;
    cout << accent("Enter board dimensions ")
         << muted("(RowsxColumns, e.g., 10x10)") << ": ";
    cin >> dimension;
    // find x or X
    size_t xPos = dimension.find('x');
    if (xPos == string::npos) { // if 'x' not found
        if ((xPos = dimension.find('X')) == string::npos) {
            cout << danger("Invalid format. Please use the format RowsxColumns (e.g., 10x10).\n") << endl;
            return dimensionSetup();
        }
    }

    int rows = stoi(dimension.substr(0, xPos));
    int cols = stoi(dimension.substr(xPos + 1));
    cout << success("Grid size confirmed: " + to_string(rows) + " x " + to_string(cols) + "\n") << endl;
    return {rows, cols};
}


vector<string> playerSetup(bool isPvC) {
    string player1;
    string player2;

    if (isPvC) {
        cout << accent("Enter your callsign, Admiral: ");
        cin >> player1;
        cout << success("Welcome aboard, " + player1 + "!\n") << endl;
        return {player1, "Computer"};
    } else {
        cout << accent("Enter Player 1 Callsign: ");
        cin >> player1;

        cout << accent("Enter Player 2 Callsign: ");
        cin >> player2;
        cout << success("Commanders " + player1 + " and " + player2 + " are ready for battle!\n") << endl;
        return {player1, player2};
    }
}

string directionSetup() {
    string direction;
    cout << accent("Enter ship direction ")
         << muted("(h for horizontal / v for vertical)") << ": ";
    cin >> direction;
    direction = (direction == "h" || direction == "H") ? "horizontal" : 
                (direction == "v" || direction == "V") ? "vertical" : "";

    if (direction == "") {
        cout << danger("Invalid direction. Please enter 'h' or 'v'.\n") << endl;
        return directionSetup();
    }
    return direction;
}

int lengthSetup() {
    int length;
    cout << accent("Enter ship length ")
         << muted("(2-5)") << ": ";
    cin >> length;

    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(10000, '\n'); // Ignore the invalid input
        cout << danger("Invalid input. Please enter a number between 2 and 5.\n") << endl;
        return lengthSetup();
    }

    if (length < 2 || length > 5) {
        cout << danger("Invalid length. Please enter a value between 2 and 5.\n") << endl;
        return lengthSetup();
    }
    return length;
}
  
Ship shipSetup(Board& board) {
    string name;
    string direction;
    int length;
    int ship_x_coord, ship_y_coord;
    
    cout << accent("Enter ship name: ");
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
    cout << success("Ship placed successfully!\n") << endl;
    return ship;
}

vector<int> coordinateSetup(Board& board, Ship& ship) {
    string coord;

    cout << "\n" << accent("Enter desired coordinates ")
         << muted("(e.g., A5)") << ": ";
    cin >> coord;

    if (!validateCoord(coord, board)) {
        return coordinateSetup(board, ship);
    }

    return coordToInt(coord);
}

void placeShip(Board& board, int row, int col) {
    for (int i = 0; i < 5; i++) {
        printDivider('-', 44, FG_BLUE);
        cout << accent("Placing ship number ") << success(to_string(i + 1)) << "\n" << endl;
        shipSetup(board);
    }
    cout << "\n" << success("All ships placed for ") << success(board.getPlayerName()) << "!" << endl;
}
