#include "../include/pregame.h"
#include "../include/setup.h"
#include "../../ingame/include/startgame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/bot/include/bot.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void displayHome() {
    cout << "========================================" << endl;
    cout << "   Welcome to the Ultimate Battleship  " << endl;
    cout << "========================================" << endl;
    cout << "1. Quick Start" << endl;
    cout << "2. Setup Game" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1: // Implement default setting here
            // startGame(player1Board, player2Board);
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
    cout << "========================================" << endl;
    cout << "            Game Setup Menu             " << endl;
    cout << "========================================" << endl;
    cout << "               Game Setup               " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Set up board dimensions\n" << endl;
    cout << "Number of Rows (min 5, max 26): ";

    int rows = dimensionSetup();

    cout << "Number of Columns (min 5, max 26): ";

    int cols = dimensionSetup();
    
    cout << "----------------------------------------" << endl;
    cout << "2. Set up player names\n" << endl;
    cout << "Enter Player 1 Name: ";

    string player1 = playerSetup();

    cout << "Enter Player 2 Name: ";

    string player2 = playerSetup();

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);
    
    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "----------------------------------------" << endl;
    cout << "3. Set up ships for each player" << endl;
    cout << "\nEach person will have 5 ships of varying sizes." << endl;
    cout << "Placing ships for " << player1 << "\n" << endl;
    
    placeShip(player1Board, rows, cols);

    cout << "Placing ships for " << player2 << "\n" << endl;
    randomizeShipOnBoard(player2Board);

    cout << "========================================" << endl;

    cout << "Setup complete! Do you want to start the game? (yes/no)" << endl;
    
    string choice;
    cin >> choice;
    if (choice == "yes") {
        startGame(player1Board, player2Board);
    } else {
        displayHome();
    }
  }