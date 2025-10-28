#include "../include/startgame.h"
#include "../include/ingameHelper.h"
#include "../include/ingame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>

using namespace std;

void startPvcGame(Board& player1, Board& player2) {
    cout << "========================================" << endl;
    cout << "             BATTLE STATIONS            " << endl;
    cout << "Engaging " << player1.getPlayerName() << " and " << player2.getPlayerName() << " in naval combat!" << endl;
    cout << "Type \"show\" during your turn to reveal the enemy fleet, or \"hide\" to restore the fog of war." << endl;
    cout << "All hands to action stations!\n" << endl;

    pvcIngame(player1, player2);
}


void startPvPGame(Board& player1, Board& player2) {
    cout << "========================================" << endl;
    cout << "             BATTLE STATIONS            " << endl;
    cout << "Engaging " << player1.getPlayerName() << " and " << player2.getPlayerName() << " in naval combat!" << endl;
    cout << "Type \"show\" during your turn to reveal the enemy fleet, or \"hide\" to restore the fog of war." << endl;
    cout << "All hands to action stations!\n" << endl;

    pvcIngame(player1, player2);
}