#include "../include/pregame.h"
#include "../include/pregameHelper.h"
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
    cout << "1. Quick Game (10x10 with default 5 ships)" << endl;
    cout << "2. Setup Game" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            quickGame();
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
    
    vector<int> dimensions = dimensionSetup();
    int rows = dimensions[0];
    int cols = dimensions[1];
    
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


void quickGame() {
    cout << "=================================" << endl;
    cout << "            Quick Game           \n" << endl;

    cout << "Enter Player 1 Name: ";
    string player1 = playerSetup();
    cout << "Enter Player 2 Name: ";
    string player2 = playerSetup();

    Board player1Board;
    player1Board.setBoardProperties(player1, 10, 10);
    Board player2Board;
    player2Board.setBoardProperties(player2, 10, 10);
    
    cout << "---------------------------------\n" << endl;
    cout << "Do you want to place your ships manually? (y/n): ";
    string choice;
    cin >> choice;

    if (choice == "y") {
        // TODO: Implement manual ship placement for player 1
    } else {
        randomizeShipOnBoard(player1Board);
    }
    randomizeShipOnBoard(player2Board);

}