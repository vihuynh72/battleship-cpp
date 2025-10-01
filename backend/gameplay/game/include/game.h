#ifndef GAME_H
#define GAME_H

#include "../../../gameplay/board/include/board.h"
#include "./gameMode.h"

class Game {
    public:
        Game(Board& p1Board, Board& p2Board);
        Game(Board& p1Board, Board& p2Board, bool pvp);
        Game(Board& p1Board, Board& p2Board, bool pvp, GameMode& gameRules);

        //getter setters for players' boards
        Board& getPlayer1Board() { return player1Board; };
        Board& getPlayer2Board() { return player2Board; };
        void setPlayer1Board(Board& board) { player1Board = board; };
        void setPlayer2Board(Board& board) { player2Board = board; };

        // getter setter for if PvP
        bool getIsPvP() { return isPvP; };
        void setIsPvP(bool pvp) { isPvP = pvp; };

        // getter setter for game rules
        GameMode& getGameRules()    { return rules; };
        void setGameRules(GameMode& gameRules) { rules = gameRules; };

    protected:
        Board& player1Board;
        Board& player2Board;

        bool isPvP;
        GameMode rules;
};

class pvcGame : public Game {
    public:
        pvcGame(Board& p1Board, Board& p2Board) : Game(p1Board, p2Board, false) {};

        void playerTurn();
        void computerTurn();
};

class pvpGame : public Game {
    
};

#endif // GAME_H