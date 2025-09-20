#ifndef SHIP_H
#define SHIP_H

#include <string>

class Ship {
    public:
        Ship(); // Constructor to initialize the ship
        Ship(std::string, std::string, int); // Overloaded constructor with parameters
        void setShipProperties(std::string, std::string, int); // Method to set ship properties
        

        void incrementHitCount(); // Method to increment hit count and check if sunk
        bool checkIsSunk(); // Method to check if the ship is sunk

        std::string getName(); // Method to get ship name
        int getLength(); // Method to get ship length
        int getHitCount(); // Method to get hit count
        std::string getDirection(); // Method to get ship direction
    private:
        // Ship properties
        std::string name;
        std::string direction; // "horizontal" or "vertical"
        int length;
        int hitCount;
        bool isSunk;
};

#endif // SHIP_H