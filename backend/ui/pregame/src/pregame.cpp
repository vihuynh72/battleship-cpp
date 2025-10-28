#include "../include/pregame.h"
#include "../include/pregameHelper.h"
#include "../../ingame/include/startgame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/bot/include/bot.h"
#include "../../../gameplay/mechanics/ship/include/ship.h"
#include "../../ingame/include/ingameHelper.h"


#include <iostream>
#include <string>
#include <vector>

using namespace std;


void displayHome() {
    cout << "========================================" << endl;
    cout << "     ~~~ COMMAND BRIDGE TERMINAL ~~~    " << endl;
    cout << "========================================" << endl;
    cout << "1. Engage the AI Armada" << endl;
    cout << "2. Challenge Another Captain" << endl;
    cout << "3. Stand Down" << endl;
    cout << "Choose your mission (1-3): ";

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            personVsComputer();
            break;
        case 2:
            // TODO: Implement human vs human mode
            cout << "Two-player skirmishes are still being charted. Check back after the next briefing." << endl;
            displayHome();
            break;
        case 3:
            cout << "Powering down tactical console. Fair winds and following seas!" << endl;
            exit(0);
            break;
        default:
            cout << "That selection drifted off course. Try plotting it again." << endl;
            displayHome();
    }
}


void displaySetup() {
    cout << "========================================" << endl;
    cout << "            STRATEGY BRIEFING           " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Configure your ocean battlefield\n" << endl;
    
    vector<int> dimensions = dimensionSetup();
    int rows = dimensions[0];
    int cols = dimensions[1];
    
    cout << "----------------------------------------" << endl;
    cout << "2. Register commanding officers\n" << endl;
    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);
    
    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << "----------------------------------------" << endl;
    cout << "3. Deploy your naval fleet" << endl;
    cout << "\nEach admiral commands 5 ships of varying tonnage." << endl;
    cout << "Plotting courses for " << player1 << "\n" << endl;
    
    placeShip(player1Board, rows, cols);

    cout << "Plotting courses for " << player2 << "\n" << endl;
    randomizeShipOnBoard(player2Board);

    player2Board.setHideShips(true);

    promptBeginGame(player1Board, player2Board, true);
}

void personVsComputer() {
    cout << "========================================" << endl;
    cout << "           PERSON VS COMPUTER           " << endl;
    cout << "========================================" << endl;
    cout << "1. Immediate Engagement" << endl;
    cout << "2. Custom Battle Plan" << endl;
    cout << "3. Return to Command Bridge" << endl;
    cout << "Select your directive (1-3): ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            pvcQuickGame();
            break;
        case 2:
            displaySetup();
            break;
        case 3:
            displayHome();
            break;
        default:
            cout << "Command unclear. Please issue a valid order." << endl;
            personVsComputer();
    }
}

void pvcQuickGame() {
    cout << "========================================" << endl;
    cout << "             QUICK DEPLOYMENT           \n" << endl;

    string player1 = "Player";
    string player2 = "Computer";

    Board player1Board;
    player1Board.setBoardProperties(player1, 10, 10);
    Board player2Board;
    player2Board.setBoardProperties(player2, 10, 10);
    
    cout << "----------------------------------------" << endl;
    cout << "Do you want to place your fleet manually? (y/n): ";
    string choice;
    cin >> choice;

    if (choice == "y") {
        vector<Ship> defaultShips = getDefaultShips();
        // get coordinate and place each ship
        for (Ship& ship : defaultShips) {
            cout << "Deploying: " << ship.getName() << " (Length: " << ship.getLength() << ")\n" << endl;

            string direction = directionSetup();
            ship.setShipProperties(ship.getName(), direction, ship.getLength());

            vector<int> shipCoord = coordinateSetup(player1Board, ship);
            int ship_y_coord = shipCoord[0];
            int ship_x_coord = shipCoord[1];

            addShipToBoard(player1Board, ship, ship_y_coord, ship_x_coord, ship.getDirection());
            printBoard(player1Board);
            cout << "Ship anchored successfully!" << endl;
        }

    } else {
        randomizeShipOnBoard(player1Board);
    }
    randomizeShipOnBoard(player2Board);

    player2Board.setHideShips(true);

    printBoardSideBySide(player1Board, player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void promptBeginGame(Board& player1Board, Board& player2Board, bool isPvC) {
    if (isPvC) {
        startPvcGame(player1Board, player2Board);
    } else {
        startPvPGame(player1Board, player2Board);
    }
}
