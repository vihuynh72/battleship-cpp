#include "../include/startgame.h"
#include "../include/ingameHelper.h"
#include "../include/ingame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>

using namespace std;

void startGame(Board& player1, Board& player2) {
    cout << "========================================" << endl;
    cout << "         BATTLESTATIONS REPORT!         " << endl;
    cout << "========================================" << endl;
    cout << "Admiral " << player1.getPlayerName() << " and Admiral " << player2.getPlayerName()
         << " have taken the helm." << endl;
    cout << "Waves crash, cannons are primed, and the fate of the fleet hangs in the balance." << endl;
    cout << "\nDeploying tactical maps..." << endl;
    printBoard(player1);
    printBoard(player2);

    cout << "The fog lifts. First shot goes to the boldest admiral!" << endl;
    ingame(player1, player2);
}
