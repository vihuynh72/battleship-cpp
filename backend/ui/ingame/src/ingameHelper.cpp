#include "../include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"
#include "../../pregame/include/pregameHelper.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace {

string getDisplayCell(Board& board, int row, int col) {
    string cell = board.getBoard()[row][col];

    if (cell.length() >= 3 && cell.front() == '[' && cell.back() == ']') {
        string content = cell.substr(1, cell.length() - 2);
        bool isNumeric = !content.empty() &&
                         all_of(content.begin(), content.end(), [](unsigned char ch) {
                             return isdigit(ch);
                         });

        if (isNumeric) {
            int shipIndex = stoi(content);
            vector<Ship>& ships = board.getShipList();
            if (shipIndex >= 0 && shipIndex < static_cast<int>(ships.size())) {
                string letter = ships[shipIndex].getName().substr(0, 1);
                if (!letter.empty()) {
                    letter[0] = toupper(static_cast<unsigned char>(letter[0]));
                }
                cell = "[" + letter + "]";
            }
        }
    }

    return cell;
}

string buildHorizontalBorder(int cols) {
    string border = "   +";
    for (int j = 0; j < cols; j++) {
        border += "-----+";
    }
    return border;
}

string buildBoardRowString(Board& board, int rowIndex) {
    stringstream rowStream;
    rowStream << " " << setw(2) << right << rowIndex + 1 << " |";

    for (int j = 0; j < board.getColumns(); j++) {
        rowStream << " " << setw(3) << left << getDisplayCell(board, rowIndex, j) << " |";
    }

    return rowStream.str();
}

vector<string> renderBoard(Board& board) {
    vector<string> lines;
    string title = board.getPlayerName() + "'s Battle Grid";
    string underline(title.length(), '=');

    lines.push_back(title);
    lines.push_back(underline);
    lines.push_back("Legend: [ ] Empty  [O] Miss  [X] Hit  [Initial] Ship segment");
    lines.push_back("");

    stringstream header;
    header << "     ";
    for (int j = 0; j < board.getColumns(); j++) {
        header << "  " << static_cast<char>('A' + j) << "   ";
    }

    lines.push_back(header.str());

    string border = buildHorizontalBorder(board.getColumns());
    lines.push_back(border);

    for (int i = 0; i < board.getRows(); i++) {
        lines.push_back(buildBoardRowString(board, i));
        lines.push_back(border);
    }

    return lines;
}

} // namespace

void printBoard(Board& board) {
    cout << endl;

    vector<string> boardLines = renderBoard(board);
    for (const string& line : boardLines) {
        cout << line << endl;
    }
}

void printShipList(Board& board) {
    cout << board.getPlayerName() << "'s Fleet Overview" << endl;
    cout << string(board.getPlayerName().length() + 19, '=') << endl;
    for (Ship& ship : board.getShipList()) {
        cout << "• ";
        printShipInfo(ship);
    }
}

void printShipInfo(Ship& ship) {
    int remainingHealth = ship.getLength() - ship.getHitCount();
    cout << ship.getName() << " | Length: " << ship.getLength()
         << " | Integrity: " << remainingHealth << " segment"
         << (remainingHealth == 1 ? "" : "s")
         << " | Status: " << (ship.checkIsSunk() ? "SUNK" : "AFLOAT") << endl;
}

bool validateCoord(string coord, Board& board) {

    if (coord.length() < 2 || 
        coord.length() > 3 ||
        !isalpha(coord[0]) || 
        !isdigit(coord[1]) || 
        (coord.length() == 3 && !isdigit(coord[2]))) {
        cout << "Invalid format. Please use the format LetterNumber (e.g., A5).\n" << endl;
        return false;
    }
    
    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;
    
    if (checkOutOfBounds(board, row, col) || !checkEmptyCell(board.getBoard()[row][col])) {
        cout << "Invalid coordinates. Please try again.\n" << endl;
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
    vector<string> board1Lines = renderBoard(board1);
    vector<string> board2Lines = renderBoard(board2);

    size_t board1Width = 0;
    for (const string& line : board1Lines) {
        board1Width = max(board1Width, line.length());
    }

    size_t maxLines = max(board1Lines.size(), board2Lines.size());
    const size_t gapWidth = 8;

    string board1Title = board1.getPlayerName() + "'s Command";
    string board2Title = board2.getPlayerName() + "'s Command";

    cout << endl;
    cout << left << setw(board1Width) << board1Title;
    cout << string(gapWidth, ' ');
    cout << board2Title << endl;
    cout << left << setw(board1Width) << string(board1Title.length(), '-');
    cout << string(gapWidth, ' ');
    cout << string(board2Title.length(), '-') << endl;
    cout << right;

    for (size_t i = 0; i < maxLines; i++) {
        string leftLine = i < board1Lines.size() ? board1Lines[i] : "";
        string rightLine = i < board2Lines.size() ? board2Lines[i] : "";

        size_t padding = board1Width > leftLine.length() ? board1Width - leftLine.length() : 0;

        cout << leftLine << string(padding + gapWidth, ' ') << rightLine << endl;
    }
}

void printBoardRow(Board& board, int rowIndex, bool hasRow) {
    if (hasRow) {
        cout << buildBoardRowString(board, rowIndex);
    } else {
        cout << string(board.getColumns() * 6 + 4, ' ');
    }
}