#include "../include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"
#include "../../pregame/include/pregameHelper.h"
#include "../../common/include/uiTheme.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace ui::theme;

namespace {

bool isShipIndex(const string& cell) {
    return cell.length() >= 3 && cell.front() == '[' && cell.back() == ']';
}

string shipInitial(Ship& ship) {
    string name = ship.getName();
    if (name.empty()) {
        return "?";
    }
    return string(1, static_cast<char>(toupper(name[0])));
}

string formatShipCell(Board& board, const string& cell, bool hideShips) {
    string indexContent = cell.substr(1, cell.length() - 2);
    if (indexContent.empty() || !isdigit(indexContent[0])) {
        return stylize(cell, {FG_WHITE});
    }

    int shipIndex = stoi(indexContent);
    vector<Ship>& ships = board.getShipList();
    if (shipIndex < 0 || shipIndex >= static_cast<int>(ships.size())) {
        return stylize("[?]", {FG_GRAY});
    }

    Ship& ship = ships[shipIndex];
    if (hideShips) {
        return stylize("[~]", {FG_BLUE});
    }

    const char* color = ship.checkIsSunk() ? FG_RED : FG_YELLOW;
    return stylize("[" + shipInitial(ship) + "]", {BOLD, color});
}

string formatCell(Board& board, const string& rawCell, bool hideShips) {
    if (rawCell == "[ ]") {
        return stylize("[~]", {FG_BLUE});
    }
    if (rawCell == "[O]") {
        return stylize("[○]", {FG_CYAN});
    }
    if (rawCell == "[X]") {
        return stylize("[X]", {BOLD, FG_RED});
    }
    if (isShipIndex(rawCell)) {
        return formatShipCell(board, rawCell, hideShips);
    }
    return stylize(rawCell, {FG_WHITE});
}

} // namespace

void printBoard(Board& board) {
    cout << endl;
    int headerWidth = board.getColumns() * 4 + 8;
    printDivider('=', headerWidth);
    cout << accent(centerText(board.getPlayerName() + "'s Tactical Map", headerWidth)) << endl;
    printDivider('=', headerWidth);

    cout << "    ";
    for (int j = 0; j < board.getColumns(); j++) {
        string letter(1, static_cast<char>('A' + j));
        cout << stylize(" " + letter + " ", {BOLD, FG_CYAN});
    }
    cout << endl;

    for (int i = 0; i < board.getRows(); i++) {
        string rowLabel = (i < 9 ? " " : "") + to_string(i + 1);
        cout << stylize(rowLabel, {BOLD, FG_MAGENTA}) << "  ";

        for (int j = 0; j < board.getColumns(); j++) {
            cout << formatCell(board, board.getBoard()[i][j], false) << " ";
        }
        cout << endl;
    }
}

void printShipList(Board& board) {
    cout << endl << accent(board.getPlayerName() + "'s Fleet Status:") << endl;
    if (board.getShipList().empty()) {
        cout << muted("No vessels deployed yet.\n");
        return;
    }

    printDivider('-', 48, FG_BLUE);
    for (Ship& ship : board.getShipList()) {
        printShipInfo(ship);
        printDivider('-', 48, FG_BLUE);
    }
}

void printShipInfo(Ship& ship) {
    int integrity = ship.getLength() - ship.getHitCount();
    string status = ship.checkIsSunk() ? danger("SUNK") : success("OPERATIONAL");

    cout << success("Ship: ") << accent(ship.getName()) << endl;
    cout << "   Status: " << status << endl;
    cout << "   Integrity: " << healthBar(integrity, ship.getLength())
         << " " << muted(to_string(integrity) + "/" + to_string(ship.getLength())) << endl;
}

bool validateCoord(string coord, Board& board) {
    if (coord.length() < 2 ||
        coord.length() > 3 ||
        !isalpha(coord[0]) ||
        !isdigit(coord[1]) ||
        (coord.length() == 3 && !isdigit(coord[2]))) {
        cout << danger("Invalid format. Use LetterNumber (e.g., A5).\n") << endl;
        return false;
    }

    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;

    if (checkOutOfBounds(board, row, col) || !checkEmptyCell(board.getBoard()[row][col])) {
        cout << danger("Invalid coordinates. The location is occupied or out of bounds.\n") << endl;
        return false;
    }
    return true;
}

vector<int> coordToInt(string coord) {
    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;
    return {row, col};
}

void printBoardSideBySide(Board& board1, Board& board2, bool hideSecondBoardShips) {
    const int CELL_WIDTH = 4;
    const int ROW_NUM_WIDTH = 4;
    const int BOARD_SEPARATOR = 7;

    int board1Width = ROW_NUM_WIDTH + (board1.getColumns() * CELL_WIDTH) - 1;
    int board2Width = ROW_NUM_WIDTH + (board2.getColumns() * CELL_WIDTH) - 1;
    int totalWidth = board1Width + BOARD_SEPARATOR + board2Width;

    cout << endl;
    printDivider('=', totalWidth, FG_NAVY);

    string board1Name = board1.getPlayerName() + "'s Board";
    string board2Name = board2.getPlayerName() + "'s Board";
    cout << accent(centerText(board1Name, board1Width))
         << string(BOARD_SEPARATOR, ' ')
         << accent(centerText(board2Name, board2Width)) << endl;

    printDivider('-', totalWidth, FG_BLUE);

    cout << "    ";
    for (int j = 0; j < board1.getColumns(); j++) {
        string letter(1, static_cast<char>('A' + j));
        cout << stylize(" " + letter + " ", {BOLD, FG_CYAN});
    }
    cout << string(BOARD_SEPARATOR, ' ');
    for (int j = 0; j < board2.getColumns(); j++) {
        string letter(1, static_cast<char>('A' + j));
        cout << stylize(" " + letter + " ", {BOLD, FG_CYAN});
    }
    cout << endl;

    int maxRows = max(board1.getRows(), board2.getRows());
    for (int i = 0; i < maxRows; i++) {
        printBoardRow(board1, i, i < board1.getRows(), false);
        cout << string(BOARD_SEPARATOR, ' ');
        printBoardRow(board2, i, i < board2.getRows(), hideSecondBoardShips);
        cout << endl;
    }

    printDivider('=', totalWidth, FG_NAVY);
}

void printBoardRow(Board& board, int rowIndex, bool hasRow, bool hideShips) {
    if (hasRow) {
        string rowLabel = (rowIndex < 9 ? " " : "") + to_string(rowIndex + 1);
        cout << stylize(rowLabel, {BOLD, FG_MAGENTA}) << "  ";
        for (int j = 0; j < board.getColumns(); j++) {
            cout << formatCell(board, board.getBoard()[rowIndex][j], hideShips) << " ";
        }
    } else {
        cout << "    ";
        for (int j = 0; j < board.getColumns(); j++) {
            cout << "    ";
        }
    }
}
