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

// Method to increment hit count and check if sunk
void Ship::incrementHitCount() {
    hitCount++;
    if (hitCount >= length) {
        isSunk = true;
    }
}

bool Ship::isSunk() {
    return isSunk;
}

// Other getters methods for ship properties
string Ship::getName() {
    return name;
}

int Ship::getLength() {
    return length;
}

int Ship::getHitCount() {
    return hitCount;
}

std::string Ship::getDirection() {
    return direction;
}
