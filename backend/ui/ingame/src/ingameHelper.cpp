#include "../include/ingameHelper.h"
#include "../../../gameplay/board/include/board.h"
#include "../../../gameplay/ship/include/ship.h"
#include "../../../gameplay/mechanics/space/include/space.h"
#include "../../pregame/include/pregameHelper.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printBoard(Board& board) {
    cout << "\n╔═══ " << board.getPlayerName() << "'s Fleet Map ═══╗" << endl;
    if (board.getHideShips()) {
        cout << "║ 🌊 Enemy sonar interference active    ║" << endl;
        cout << "║ 💡 Use \"show\" to reveal their fleet  ║" << endl;
    }
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "   ";
    for (int j = 0; j < board.getColumns(); j++) {
        cout << "  " << static_cast<char>('A' + j) << " ";
    }
    cout << endl;

    for (int i = 0; i < board.getRows(); i++) {
        if (i < 9) {
            cout << i + 1 << "   ";
        } else {
            cout << i + 1 << "  ";
        }

        for (int j = 0; j < board.getColumns(); j++) {
            string cell = board.getBoard()[i][j];

            if (board.getHideShips()) {
                // Hide all cells except hits ([X]) and misses ([O])
                if (cell != "[X]" && cell != "[O]") {
                    cell = "[~]";
                }
            } else {
                // Convert ship index [0], [1], etc. to ship name letter for display
                if (cell.length() >= 3 && cell[0] == '[' && cell[cell.length()-1] == ']') {
                    string content = cell.substr(1, cell.length() - 2);
                    // Check if it's a number (ship index)
                    if (!content.empty() && isdigit(content[0])) {
                        int shipIndex = stoi(content);
                        vector<Ship>& ships = board.getShipList();
                        if (shipIndex >= 0 && shipIndex < ships.size()) {
                            // Display first letter of ship name
                            cell = "[" + ships[shipIndex].getName().substr(0, 1) + "]";
                        }
                    }
                }
            }

            cout << cell << " ";
        }
        cout << endl;
    }
}

void printShipList(Board& board) {
    cout << "\n┌────────────────────────────────────────┐" << endl;
    cout << "│  " << board.getPlayerName() << "'s Battle Readiness Report";
    // Calculate padding
    int nameLen = board.getPlayerName().length();
    int padding = 40 - 31 - nameLen - 2;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "     │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
    for (Ship& ship : board.getShipList()) {
        cout << "\n┌─ " << ship.getName();
        int shipNameLen = ship.getName().length();
        for (int i = 0; i < 35 - shipNameLen; i++) cout << "─";
        cout << "┐" << endl;
        printShipInfo(ship);
        cout << "└─────────────────────────────────────┘" << endl;
    }
}

void printShipInfo(Ship& ship) {
    cout << "│ ⚓ Vessel: " << ship.getName();
    int nameLen = ship.getName().length();
    int padding = 38 - 11 - nameLen - 2;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "│" << endl;
    
    cout << "│ ⚡ Hull Integrity: " << ship.getLength() - ship.getHitCount() << " / " << ship.getLength();
    // Calculate padding for hull integrity line
    string integrityStr = to_string(ship.getLength() - ship.getHitCount()) + " / " + to_string(ship.getLength());
    int integrityPadding = 37 - 18 - integrityStr.length() - 2;
    for (int i = 0; i < integrityPadding; i++) cout << " ";
    cout << "│" << endl;
    
    string status = ship.checkIsSunk() ? "💀 Sunk beneath the waves" : "✓ Operational";
    cout << "│ " << status;
    int statusLen = ship.checkIsSunk() ? 26 : 14;
    int statusPadding = 40 - 1 - statusLen - 2;
    for (int i = 0; i < statusPadding; i++) cout << " ";
    cout << "│" << endl;
}

bool validateCoord(string coord, Board& board) {

    if (coord.length() < 2 || 
        coord.length() > 3 ||
        !isalpha(coord[0]) || 
        !isdigit(coord[1]) || 
        (coord.length() == 3 && !isdigit(coord[2]))) {
        cout << "That transmission was garbled. Use the LetterNumber format (e.g., A5).\n" << endl;
        return false;
    }
    
    int col = toupper(coord[0]) - 'A';
    int row = stoi(coord.substr(1)) - 1;
    
    if (checkOutOfBounds(board, row, col) || !checkEmptyCell(board.getBoard()[row][col])) {
        cout << "No target acquired there. Adjust your aim and try again.\n" << endl;
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
    const int CELL_WIDTH = 4;  // Each cell takes 4 characters (char + 3 spaces)
    const int ROW_NUM_WIDTH = 4;  // Row number column width
    const int BOARD_SEPARATOR = 7;  // Space between boards
    
    // Calculate board widths
    int board1Width = ROW_NUM_WIDTH + (board1.getColumns() * CELL_WIDTH) - 1;
    int board2Width = ROW_NUM_WIDTH + (board2.getColumns() * CELL_WIDTH) - 1;
    
    // Create board names
    string board1Name = board1.getPlayerName() + "'s Board:";
    string board2Name = board2.getPlayerName() + "'s Board:";
    
    // Calculate total width needed for the headline
    int totalWidth = board1Width + BOARD_SEPARATOR + board2Width;
    
    // Create and format the headline
    string nameHeadline = string(totalWidth, ' ');
    nameHeadline.replace(0, board1Name.length(), board1Name);
    
    // Position the second board name
    int board2NameStart = board1Width + BOARD_SEPARATOR + 2;
    if (board2NameStart + board2Name.length() <= nameHeadline.length()) {
        nameHeadline.replace(board2NameStart, board2Name.length(), board2Name);
    }

    cout << endl;
    cout << nameHeadline << endl;
    
    // Print column headers for both boards
    cout << "     ";
    for (int j = 0; j < board1.getColumns(); j++) {
        cout << static_cast<char>('A' + j) << "   ";
    }
    cout << "           ";  // 7 spaces + 4 extra = 11 spaces total
    for (int j = 0; j < board2.getColumns(); j++) {
        cout << static_cast<char>('A' + j) << "   ";
    }
    cout << endl;

    // Print rows for both boards
    int maxRows = max(board1.getRows(), board2.getRows());
    for (int i = 0; i < maxRows; i++) {
        // Print board1 row
        printBoardRow(board1, i, i < board1.getRows());
        
        // Print separator between the two boards
        cout << "       ";
        
        // Print board2 row
        printBoardRow(board2, i, i < board2.getRows());
        
        cout << endl;
    }
}

void printBoardRow(Board& board, int rowIndex, bool hasRow) {
    if (hasRow) {
        // Print row number with proper formatting
        if (rowIndex < 9) {
            cout << " " << rowIndex + 1 << "  ";
        } else {
            cout << rowIndex + 1 << "  ";
        }
        // Print board cells
        for (int j = 0; j < board.getColumns(); j++) {
            string cell = board.getBoard()[rowIndex][j];

            if (board.getHideShips()) {
                // Hide all cells except hits ([X]) and misses ([O])
                if (cell != "[X]" && cell != "[O]") {
                    cell = "[~]";
                }
            } else {
                // Convert ship index [0], [1], etc. to ship name letter for display
                if (cell.length() >= 3 && cell[0] == '[' && cell[cell.length()-1] == ']') {
                    string content = cell.substr(1, cell.length() - 2);
                    // Check if it's a number (ship index)
                    if (!content.empty() && isdigit(content[0])) {
                        int shipIndex = stoi(content);
                        vector<Ship>& ships = board.getShipList();
                        if (shipIndex >= 0 && shipIndex < ships.size()) {
                            // Display first letter of ship name
                            cell = "[" + ships[shipIndex].getName().substr(0, 1) + "]";
                        }
                    }
                }
            }

            cout << cell << " ";
        }
    } else {
        // Print empty spaces when board has fewer rows
        cout << "    ";
        for (int j = 0; j < board.getColumns(); j++) {
            cout << "    ";
        }
    }
}
