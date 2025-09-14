#include "ship.h"
#include <iostream>

using namespace std;

Ship::Ship() {
    name = "Unnamed Ship";
    direction = "horizontal";
    length = 2;
    hitCount = 0;
    isSunk = false;
}

void Ship::setShipProperties(string shipName, string shipDirection, int shipLength) {
    name = shipName;
    direction = shipDirection;
    length = shipLength;
    hitCount = 0;
    isSunk = false;
}

// TODO: Move to UI
Ship::displayShipInfo() {
    cout << "Ship Name: " << name << endl;
    cout << "Direction: " << direction << endl;
    cout << "Length: " << length << endl;
    cout << "Hit Count: " << hitCount << endl;
    cout << "Is Sunk: " << (isSunk ? "Yes" : "No") << endl;
}