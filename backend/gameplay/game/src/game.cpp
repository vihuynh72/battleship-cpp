#include "../include/game.h"
#include "../include/gameMode.h"

Game::Game() : player1Board(nullptr), player2Board(nullptr), isPvP(false), rules(*(new GameMode())) {
    // Default constructor implementation
}
  