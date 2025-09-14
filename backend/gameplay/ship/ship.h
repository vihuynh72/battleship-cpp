#ifndef SHIP_H
#define SHIP_H

#include "../board/board.h"

using namespace std;

class Ship {
    public:
        Ship(); // Constructor to initialize the ship
        void setShipProperties(string, string, int); // Method to set ship properties
        void displayShipInfo(); // Method to get ship information

    private:
        // Ship properties
        string name;
        string direction; // "horizontal" or "vertical"
        int length;
        int hitCount;
        bool isSunk;
}

#endif // SHIP_H