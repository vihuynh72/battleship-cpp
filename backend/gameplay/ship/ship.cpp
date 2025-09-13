#include "ship.h"
#include <iostream>

using namespace std;

Ship::Ship() {
    name = "Unnamed Ship";
    direction = "horizontal";
    length = 1;
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

Ship::placeShip(int x, int y, string dir) {
    
}

Ship::attackShip(int x, int y) {

}

Ship::getShipInfo() {

}