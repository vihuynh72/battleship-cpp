#include "../include/startgame.h"
#include "../include/ingameHelper.h"
#include "../include/ingame.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"

#include <iostream>
#include <string>

using namespace std;

// ANSI color codes
const string CYAN = "\033[36m";
const string YELLOW = "\033[33m";
const string BRIGHT_RED = "\033[91m";
const string BOLD = "\033[1m";
const string RESET = "\033[0m";

void startPvcGame(Board& player1, Board& player2) {
    cout << "\n" << BRIGHT_RED << BOLD << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << BRIGHT_RED << "║" << RESET << "                                        " << BRIGHT_RED << "║" << RESET << endl;
    cout << BRIGHT_RED << "║" << RESET << "          " << BRIGHT_RED << "⚔" << RESET << " BATTLE STATIONS " << BRIGHT_RED << "⚔" << RESET << "           " << BRIGHT_RED << "║" << RESET << endl;
    cout << BRIGHT_RED << "║" << RESET << "                                        " << BRIGHT_RED << "║" << RESET << endl;
    cout << BRIGHT_RED << "╚════════════════════════════════════════╝" << RESET << endl;
    cout << "\n" << CYAN << "┌──────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << " Engaging " << player1.getPlayerName() << " and " << player2.getPlayerName() << " in naval combat!" << CYAN <<"│" << endl;
    cout << CYAN << "└──────────────────────────────────────────────┘" << RESET << endl;
    cout << "\n" << YELLOW << "💡 TIP:" << RESET << " Type \"show\" to reveal enemy fleet" << endl;
    cout << YELLOW << "💡 TIP:" << RESET << " Type \"hide\" to restore fog of war" << endl;
    cout << YELLOW << "💡 TIP:" << RESET << " Type \"kill\" to instantly win (debug)" << endl;
    cout << "\n" << CYAN << "⚓" << RESET << " All hands to action stations!\n" << endl;
    printBoardSideBySide(player1, player2);
    pvcIngame(player1, player2);
}


void startPvPGame(Board& player1, Board& player2) {
    cout << "\n" << BRIGHT_RED << BOLD << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << BRIGHT_RED << "║" << RESET << "                                        " << BRIGHT_RED << "║" << RESET << endl;
    cout << BRIGHT_RED << "║" << RESET << "          " << BRIGHT_RED << "⚔" << RESET << " BATTLE STATIONS " << BRIGHT_RED << "⚔" << RESET << "           " << BRIGHT_RED << "║" << RESET << endl;
    cout << BRIGHT_RED << "║" << RESET << "                                        " << BRIGHT_RED << "║" << RESET << endl;
    cout << BRIGHT_RED << "╚════════════════════════════════════════╝" << RESET << endl;
    cout << "\n" << CYAN << "┌────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << " Engaging " << player1.getPlayerName() << " and " << player2.getPlayerName() << " in naval combat!" << endl;
    cout << CYAN << "└────────────────────────────────────────┘" << RESET << endl;
    cout << "\n" << YELLOW << "💡 TIP:" << RESET << " Type \"show\" to reveal enemy fleet" << endl;
    cout << YELLOW << "💡 TIP:" << RESET << " Type \"hide\" to restore fog of war" << endl;
    cout << "\n" << CYAN << "⚓" << RESET << " All hands to action stations!\n" << endl;
    printBoardSideBySide(player1, player2);
    pvcIngame(player1, player2);
}