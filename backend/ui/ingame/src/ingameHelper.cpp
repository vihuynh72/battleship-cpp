#include "../include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"
#include "../../pregame/include/pregameHelper.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace {
string formatCellDisplay(Board& board, int row, int col) {
    string cell = board.getBoard()[row][col];

    if (cell.length() >= 3 && cell.front() == '[' && cell.back() == ']') {
        string content = cell.substr(1, cell.length() - 2);
        if (!content.empty() && isdigit(content[0])) {
            int shipIndex = stoi(content);
            vector<Ship>& ships = board.getShipList();
            if (shipIndex >= 0 && shipIndex < static_cast<int>(ships.size())) {
                string shipName = ships[shipIndex].getName();
                char shipInitial = shipName.empty() ? '?' : toupper(shipName.front());
                cell = string("[") + shipInitial + "]";
            }
        }
    }

    if (cell.length() == 3) {
        return cell;
    }
    if (cell.length() == 2) {
        return " " + cell;
    }
    if (cell.length() == 1) {
        return string(" ") + cell + " ";
    }
    if (cell.empty()) {
        return "   ";
    }
    return cell.substr(0, 3);
}

vector<string> buildBoardGrid(Board& board) {
    vector<string> lines;

    ostringstream columnStream;
    columnStream << "    ";
    for (int j = 0; j < board.getColumns(); j++) {
        columnStream << " " << static_cast<char>('A' + j) << "  ";
    }
    lines.push_back(columnStream.str());

    ostringstream dividerStream;
    dividerStream << "   +";
    for (int j = 0; j < board.getColumns(); j++) {
        dividerStream << "---+";
    }
    const string horizontalDivider = dividerStream.str();
    lines.push_back(horizontalDivider);

    for (int i = 0; i < board.getRows(); i++) {
        ostringstream rowStream;
        rowStream << " " << setw(2) << setfill(' ') << (i + 1) << " |";
        for (int j = 0; j < board.getColumns(); j++) {
            rowStream << formatCellDisplay(board, i, j) << "|";
        }
        lines.push_back(rowStream.str());
        lines.push_back(horizontalDivider);
    }

    return lines;
}

string padRight(const string& text, size_t width) {
    if (text.size() >= width) {
        return text;
    }
    return text + string(width - text.size(), ' ');
}
} // namespace

void printBoard(Board& board) {
    cout << "\n========================================" << endl;
    cout << "TACTICAL DISPLAY: " << board.getPlayerName() << endl;
    cout << "Legend: [ ] Fog of war  [X] Direct hit  [O] Missed shot  Ship initials = vessel" << endl;
    cout << "----------------------------------------" << endl;

    vector<string> gridLines = buildBoardGrid(board);
    for (const string& line : gridLines) {
        cout << line << endl;
    }
}

void printShipList(Board& board) {
    cout << "\n========================================" << endl;
    cout << board.getPlayerName() << "'s Fleet Manifest" << endl;
    cout << "----------------------------------------" << endl;
    for (Ship& ship : board.getShipList()) {
        printShipInfo(ship);
        cout << "----------------------------------------" << endl;
    }
}

void printShipInfo(Ship& ship) {
    cout << "Vessel: " << ship.getName() << endl;
    cout << "Hull Integrity: " << ship.getLength() - ship.getHitCount() << " / " << ship.getLength() << endl;
    cout << "Status: " << (ship.checkIsSunk() ? "SUNK - Wreckage sighted" : "ACTIVE - Ready for duty") << endl;
}

bool validateCoord(string coord, Board& board) {

    if (coord.length() < 2 || 
        coord.length() > 3 ||
        !isalpha(coord[0]) || 
        !isdigit(coord[1]) || 
        (coord.length() == 3 && !isdigit(coord[2]))) {
        cout << "Coordinate rejected. Use the format LetterNumber (e.g., A5).\n" << endl;
        return false;
    }

    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;

    if (checkOutOfBounds(board, row, col) || !checkEmptyCell(board.getBoard()[row][col])) {
        cout << "That sector is unavailable. Choose a different target.\n" << endl;
        return false;
    }
    return true;
}

vector<int> coordToInt(string coord) {
    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;  // Convert to 0-indexed (subtract 1, not add 1)
    return {row, col};
}


void printBoardSideBySide(Board& board1, Board& board2) {
    vector<string> board1Lines = buildBoardGrid(board1);
    vector<string> board2Lines = buildBoardGrid(board2);

    size_t board1Width = 0;
    size_t board2Width = 0;
    for (const string& line : board1Lines) {
        board1Width = max(board1Width, line.size());
    }
    for (const string& line : board2Lines) {
        board2Width = max(board2Width, line.size());
    }

    const string separator = "     ";

    cout << "\n========================================" << endl;
    cout << "FLEET STATUS OVERVIEW" << endl;
    cout << "Legend: [ ] Fog of war  [X] Direct hit  [O] Missed shot  Ship initials = vessel" << endl;
    cout << "----------------------------------------" << endl;

    string board1Title = "TACTICAL DISPLAY: " + board1.getPlayerName();
    string board2Title = "TACTICAL DISPLAY: " + board2.getPlayerName();
    cout << padRight(board1Title, board1Width) << separator << padRight(board2Title, board2Width) << endl;

    size_t totalLines = max(board1Lines.size(), board2Lines.size());
    for (size_t i = 0; i < totalLines; ++i) {
        string leftLine = i < board1Lines.size() ? board1Lines[i] : "";
        string rightLine = i < board2Lines.size() ? board2Lines[i] : "";

        cout << padRight(leftLine, board1Width) << separator << padRight(rightLine, board2Width) << endl;
    }
}

void printBoardRow(Board& board, int rowIndex, bool hasRow) {
    if (!hasRow) {
        return;
    }

    vector<string> gridLines = buildBoardGrid(board);
    size_t headerOffset = 2; // Skip column header and first divider
    size_t targetIndex = headerOffset + static_cast<size_t>(rowIndex * 2);
    if (targetIndex < gridLines.size()) {
        cout << gridLines[targetIndex] << endl;
        cout << gridLines[targetIndex + 1] << endl;
    }
}