#ifndef SHIP_H
#define SHIP_H

using namespace std;

class Ship() {
    public:
        Ship(); // Constructor to initialize the ship
        editShipName(); // Method to edit the ship's name

        placeShip(int, int, string); // Method to place the ship on the board
        attackShip(int, int); // Method to attack the ship
        
        getShipInfo(); // Method to get ship information

    private:
        // Ship properties
        string name;
        string direction; // "horizontal" or "vertical"
        int length;
        int hitCount;
        bool isSunk;
        
}

#endif // SHIP_H