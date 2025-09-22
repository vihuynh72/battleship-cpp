#include "../include/game.h"
#include "../include/gameMode.h"

Game::Game() : player1Board(nullptr), player2Board(nullptr), isPvP(false), rules(*(new GameMode())) {
    // Default constructor implementation
}

Game::Game(Board& p1Board, Board& p2Board) : player1Board(p1Board), player2Board(p2Board), isPvP(false), rules(*(new GameMode())) {
    // Constructor with boards to start a PVC game
}
  