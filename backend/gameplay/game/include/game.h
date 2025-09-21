#ifndef GAME_H
#define GAME_H

#include "../../../gameplay/board/include/board.h"
#include "./gameMode.h"

class Game {
    public:
        Game();
        Game(Board& p1Board, Board& p2Board);
        Game(Board& p1Board, Board& p2Board, bool pvp, GameMode& gameRules);
            
    private:
        Board& player1Board;
        Board& player2Board;

        bool isPvP;
        GameMode& rules;
};