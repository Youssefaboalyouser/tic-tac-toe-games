
#ifndef ASSIGNMENT_DEMO_ULTIMATE_X_O_H
#define ASSIGNMENT_DEMO_ULTIMATE_X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class Ultimate_Board:public Board<T> {
public:
    Ultimate_Board ();
    ~Ultimate_Board();
    T** w_board;
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void check_small_board_wins();      // Function to check win conditions in smaller boards
    void display_win_board();
};




template <typename T>
class Ultimate_Player : public Player<T> {
public:
    Ultimate_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T>{
public:
    Ultimate_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;

// Constructor for Ultimate_Board
template <typename T>
Ultimate_Board<T>::Ultimate_Board() {
    // for the 9*9 board
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }

    //for the 3*3 win_board
    this->w_board = new char*[3];
    for (int i = 0; i < 3; i++) {
        this->w_board[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            this->w_board[i][j] = 0;
        }
    }

    this->n_moves = 0;
}
template <typename T>
Ultimate_Board<T>::~Ultimate_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;

    for (int i = 0; i < 3; i++) {
        delete[] this->w_board[i];
    }
    delete[] this->w_board;
}

template <typename T>
void Ultimate_Board<T>::display_win_board() {
    cout << "\nUpdated w_board:\n\n";

    // Top row with column numbers
    cout << "    ";
    for (int j = 0; j < 3; j++) {
        cout << "  " << j << "   ";
    }
    cout << "\n";

    // Top border
    cout << "   +";
    for (int j = 0; j < 3; j++) {
        cout << "-----+";
    }
    cout << "\n";

    // Rows
    for (int i = 0; i < 3; i++) {
        // Row content
        cout << " " << i << " |";
        for (int j = 0; j < 3; j++) {
            if (this->w_board[i][j] == 0) {
                cout << "     |";
            } else {
                cout << "  " << this->w_board[i][j] << "  |";
            }
        }
        cout << "\n";

        // Row border
        cout << "   +";
        for (int j = 0; j < 3; j++) {
            cout << "-----+";
        }
        cout << "\n";
    }
}



// Display the board and the pieces on it
template <typename T>
void Ultimate_Board<T>::display_board() {
    cout<<"\n";
    // Top row with column numbers
    cout << "    ";
    for (int j = 0; j < this->columns; j++) {
        cout << "  " << j << "   ";
    }
    cout << endl;

    // Top border
    cout << "   +";
    for (int j = 0; j < this->columns; j++) {
        cout << "-----+";
    }
    cout << endl;

    // Rows
    for (int i = 0; i < this->rows; i++) {
        // Row content
        cout << setw(2) << i << " |";
        for (int j = 0; j < this->columns; j++) {
            cout << "  " << setw(2) << this->board[i][j] << " |";
        }
        cout << endl;

        // Row border
        cout << "   +";
        for (int j = 0; j < this->columns; j++) {
            cout << "-----+";
        }
        cout << endl;
    }
}



template <typename T>
void Ultimate_Board<T>::check_small_board_wins() {
    for (int blockRow = 0; blockRow < 3; ++blockRow) {
        for (int blockCol = 0; blockCol < 3; ++blockCol) {
            int startRow = blockRow * 3;
            int startCol = blockCol * 3;
            T winner = 0;

            // Check rows in the block
            for (int i = 0; i < 3; ++i) {
                if (this->board[startRow + i][startCol] == this->board[startRow + i][startCol + 1] &&
                    this->board[startRow + i][startCol + 1] == this->board[startRow + i][startCol + 2] &&
                    this->board[startRow + i][startCol] != 0) {
                    winner = this->board[startRow + i][startCol];
                    break;
                }
            }

            // Check columns in the block
            if (winner == 0) {
                for (int i = 0; i < 3; ++i) {
                    if (this->board[startRow][startCol + i] == this->board[startRow + 1][startCol + i] &&
                        this->board[startRow + 1][startCol + i] == this->board[startRow + 2][startCol + i] &&
                        this->board[startRow][startCol + i] != 0) {
                        winner = this->board[startRow][startCol + i];
                        break;
                    }
                }
            }

            // Check main diagonal in the block
            if (winner == 0 &&
                this->board[startRow][startCol] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol + 2] &&
                this->board[startRow][startCol] != 0) {
                winner = this->board[startRow][startCol];
            }

            // Check secondary diagonal in the block
            if (winner == 0 &&
                this->board[startRow][startCol + 2] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol] &&
                this->board[startRow][startCol + 2] != 0) {
                winner = this->board[startRow][startCol + 2];

            }

            if (winner != 0 && this->w_board[blockRow][blockCol] == 0) {
                this->w_board[blockRow][blockCol] = winner;
                // Display the winner of the small board and the updated `w_board`
                cout << "\nSmall board won by: " << winner << "\n";
                this->display_win_board(); // Call display function here
            }
        }
    }
}


template <typename T>
bool Ultimate_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) &&
        (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {  // Undo move
            this->n_moves--;
            this->board[x][y] = 0;
        } else {  // Make a move
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        // Call `check_small_board_wins()` to update the `w_board`
        this->check_small_board_wins();
        return true;
    }
    return false;
}



template <typename T>
bool Ultimate_Board<T>::is_win() {
    for (int i = 0; i < 3; ++i) {
        // Check rows and columns in `w_board`
        if ((this->w_board[i][0] == this->w_board[i][1] &&
             this->w_board[i][1] == this->w_board[i][2] &&
             this->w_board[i][0] != 0) ||
            (this->w_board[0][i] == this->w_board[1][i] &&
             this->w_board[1][i] == this->w_board[2][i] &&
             this->w_board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals in `w_board`
    if ((this->w_board[0][0] == this->w_board[1][1] &&
         this->w_board[1][1] == this->w_board[2][2] &&
         this->w_board[0][0] != 0) ||
        (this->w_board[0][2] == this->w_board[1][1] &&
         this->w_board[1][1] == this->w_board[2][0] &&
         this->w_board[0][2] != 0)) {
        return true;
    }

    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool Ultimate_Board<T>::is_draw() {
    return (this->n_moves == 80 && !is_win());
}

template <typename T>
bool Ultimate_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Ultimate_Player
template <typename T>
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
    while (cin.fail() || x < 0 || x >= 9 || y < 0 || y >= 9) {
        cout << "Invalid move! Please enter values between 0 and 8: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> x >> y;
    }
}

// Constructor for Ultimate_Random_Player
template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}




#endif //ASSIGNMENT_DEMO_ULTIMATE_X_O_H
