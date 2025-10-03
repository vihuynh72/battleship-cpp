#include "../include/startgame.h"
#include "../include/ingameHelper.h"
#include "../include/ingame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>

using namespace std;

void startPvcGame(Board& player1, Board& player2) {
    cout << "================================" << endl;
    cout << "         STARTING GAME          " << endl;
    cout << "Starting game between " << player1.getPlayerName() << " and " << player2.getPlayerName() << "!" << endl;
    cout << "Let the battle begin!" << endl;

    ingame(player1, player2);
}

void startPvPGame(Board& player1, Board& player2) {
    cout << "================================" << endl;
    cout << "         STARTING GAME          " << endl;
    cout << "Starting game between " << player1.getPlayerName() << " and " << player2.getPlayerName() << "!" << endl;
    cout << "Let the battle begin!" << endl;

    ingame(player1, player2);
}