#include "../include/pregame.h"
#include "../include/pregameHelper.h"
#include "../../ingame/include/startgame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/bot/include/bot.h"
#include "../../../gameplay/mechanics/ship/include/ship.h"
#include "../../ingame/include/ingameHelper.h"
#include "../../common/include/uiTheme.h"


#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;
using namespace ui::theme;


void displayHome() {
    clearScreen();
    printSplash();
    slowPrint(accent("Command your fleet and dominate the seas!"));
    cout << endl << endl;

    cout << menuOption(1, "vs Computer", "- Challenge the adaptive AI armada") << endl;
    cout << menuOption(2, "vs Human", "- Duel with a friend (coming soon)") << endl;
    cout << menuOption(3, "Exit", "- Retreat for now") << endl;
    cout << endl << accent("Select an option (1-3): ");

    int choice;
    cin >> choice;
    cout << endl;
    switch (choice) {
        case 1:
            personVsComputer();
            break;
        case 2:
            cout << warning("Human vs Human mode is under development. Return soon, Commander!\n") << endl;
            displayHome();
            break;
        case 3:
            cout << muted("Exiting game. Fair winds and following seas!") << endl;
            exit(0);
            break;
        default:
            cout << warning("Invalid choice. Please try again.\n") << endl;
            displayHome();
    }
}


void displaySetup() {
    clearScreen();
    printDivider('=', 56);
    cout << accent("           Advanced Battle Configuration           ") << endl;
    printDivider('=', 56);
    cout << endl;

    printStepHeader(1, "Set up board dimensions");
    cout << muted("   Tip: Larger oceans mean longer engagements.") << endl << endl;

    vector<int> dimensions = dimensionSetup();
    int rows = dimensions[0];
    int cols = dimensions[1];

    cout << endl;
    printStepHeader(2, "Assign your fleet's callsigns");
    cout << muted("   Your name echoes across the seas.") << endl << endl;
    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, rows, cols);

    Board player2Board;
    player2Board.setBoardProperties(player2, rows, cols);

    cout << endl;
    printStepHeader(3, "Deploy your fleet");
    cout << muted("   Each admiral commands 5 vessels of varying strength.") << endl;
    cout << endl << accent("Placing ships for ") << success(player1) << "\n" << endl;

    placeShip(player1Board, rows, cols);

    cout << endl << accent("Automating deployment for ") << success(player2) << "\n" << endl;
    loadingPulse("Deploying computer fleet");
    cout << endl;
    randomizeShipOnBoard(player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void personVsComputer() {
    clearScreen();
    printDivider('=', 50);
    cout << accent("          Mission Control: PvC Mode          ") << endl;
    printDivider('=', 50);
    cout << endl;
    cout << menuOption(1, "Quick Game", "- Default 10x10 skirmish") << endl;
    cout << menuOption(2, "Setup Game", "- Customize every detail") << endl;
    cout << menuOption(3, "Back to Main Menu") << endl;
    cout << endl << accent("Choose your operation (1-3): ");
    int choice;
    cin >> choice;
    cout << endl;

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
            cout << warning("Invalid choice. Try again, Commander.\n") << endl;
            personVsComputer();
    }
}

void pvcQuickGame() {
    clearScreen();
    printDivider('=', 48);
    cout << accent("              Quick Battle Setup              ") << endl;
    printDivider('=', 48);
    cout << endl;

    vector<string> players = playerSetup(true);
    string player1 = players[0];
    string player2 = players[1];

    Board player1Board;
    player1Board.setBoardProperties(player1, 10, 10);
    Board player2Board;
    player2Board.setBoardProperties(player2, 10, 10);

    cout << menuOption(0, "Fleet Deployment", "Manual or automatic?") << endl;
    cout << accent("Do you want to place your ships manually? (y/n): ");
    string choice;
    cin >> choice;
    cout << endl;

    if (choice == "y" || choice == "Y") {
        vector<Ship> defaultShips = getDefaultShips();
        for (Ship& ship : defaultShips) {
            cout << accent("Deploying ship: ") << success(ship.getName())
                 << muted(" (Length: " + to_string(ship.getLength()) + ")") << "\n" << endl;

            string direction = directionSetup();
            ship.setShipProperties(ship.getName(), direction, ship.getLength());

            vector<int> shipCoord = coordinateSetup(player1Board, ship);
            int ship_y_coord = shipCoord[0];
            int ship_x_coord = shipCoord[1];

            addShipToBoard(player1Board, ship, ship_y_coord, ship_x_coord, ship.getDirection());
            printBoard(player1Board);
            cout << success("Ship placed successfully!\n") << endl;
        }

    } else {
        cout << muted("Auto-deploying your squadron...") << endl;
        loadingPulse("Auto-deploy in progress");
        cout << endl;
        randomizeShipOnBoard(player1Board);
    }
    cout << muted("Calibrating enemy sonar...") << endl;
    loadingPulse("Calibrating enemy sonar");
    cout << endl;
    randomizeShipOnBoard(player2Board);

    printBoardSideBySide(player1Board, player2Board);

    promptBeginGame(player1Board, player2Board, true);
}

void promptBeginGame(Board& player1Board, Board& player2Board, bool isPvC) {
    cout << endl << accent("Press ENTER to launch the offensive!") << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    if (isPvC) {
        startPvcGame(player1Board, player2Board);
    } else {
        startPvPGame(player1Board, player2Board);
    }
}