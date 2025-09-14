#include "pregame.h"
#include "../../gameplay/board/board.h"
#include "../../gameplay/ship/ship.h"

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
    cout << "========================================" << endl;
    cout << "            Game Setup Menu             " << endl;
    cout << "========================================" << endl;
    cout << "               Game Setup               " << endl;
    cout << "1. Set up board dimensions" << endl;
    cout << "Number of Rows (min 5, max 26): ";

    int rows = dimensionSetup();

    cout << "Number of Columns (min 5, max 26): ";

    int cols = dimensionSetup();

    cout << "2. Set up player names" << endl;
    cout << "Enter Player 1 Name: ";

    string player1 = playerSetup();

    cout << "Enter Player 2 Name: ";

    string player2 = playerSetup();

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);
    
    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "3. Set up ships for each player" << endl;
    cout << "Each person will have 5 ships of varying sizes." << endl;
    for (int i = 0; i < 2; i++) {
        cout << "For player " << i + 1 << ":" << endl;
        Ship ship = shipSetup(player1Board);
        cout << "Ship " << (i + 1) << " - Name: " << ship.getName() << "\n Direction: " << ship.getDirection() << "\n Length: " << ship.getLength() << endl;
      }

    cout << "========================================" << endl;

    cout << "Setup complete! Do you want to start the game? (yes/no)" << endl;
    
    string choice;
    cin >> choice;
    if (choice == "yes") {
        startGame();
    } else {
        displayHome();
    }
  }

void startGame() {
}

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