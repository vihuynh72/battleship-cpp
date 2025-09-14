#include "../include/setup.h"
#include "../../gameplay/board/board.h"
#include "../../gameplay/ship/ship.h"

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
    Ship ship;
    ship.setShipProperties(name, direction, length);
    return ship;
}