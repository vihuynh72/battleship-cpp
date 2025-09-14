#include "pregame.h"
#include "../../gameplay/board/board.h"
#include "  ../gameplay/ship/ship.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void displayHome() {
    cout << "========================================" << endl;
    cout << "   Welcome to the Ultimate Battleship  " << endl;
    cout << "========================================" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Setup Game" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            startGame();
            break;
        case 2:
            displaySetup();
            break;
        case 3:
            cout << "Exiting game. Thank you for playing!" << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayHome();
    }
}

void displaySetup() {

}

void startGame() {

}