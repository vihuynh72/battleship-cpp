#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {
    public:
        Board(); // Constructor to initialize the board
        displayBoard(); // Method to display the board

    private:
        // Board dimensions
        int Rows;
        int Columns;

        // 2D array to represent the board
        string board[Rows][Columns];
};

#endif // BOARD_H