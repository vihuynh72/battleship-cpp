#include "../include/startgame.h"
#include "../include/ingameHelper.h"
#include "../../../gameplay/board/board.h"
#include "../../../gameplay/ship/ship.h"

#include <iostream>
#include <string>

using namespace std;

void startGame(Board& player1, Board& player2) {
    cout << "Starting game between " << player1.getPlayerName() << " and " << player2.getPlayerName() << "!" << endl;
    cout << "Let the battle begin!" << endl;
    printBoard(player1);
    printBoard(player2);
}