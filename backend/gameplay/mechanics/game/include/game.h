#ifndef MECHANICS_GAME_H
#define MECHANICS_GAME_H

#include "../../../board/include/board.h"

bool checkGameOver(Board& player1Board, Board& player2Board);

Board& checkWinner(Board& player1Board, Board& player2Board);

#endif // MECHANICS_GAME_H