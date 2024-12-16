#ifndef ASSIGNMENT_DEMO_5X5X_O_H
#define ASSIGNMENT_DEMO_5X5X_O_H
#include "BoardGame_Classes.h"

template <typename T>
class X_O5x5Board:public Board<T> {
public:
    X_O5x5Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    int count_three_in_a_row(T player);
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





#include <bits/stdc++.h>

using namespace std;

// Constructor for X_O5x5Board
template <typename T>
X_O5x5Board<T>::X_O5x5Board() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O5x5Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            if(this -> n_moves<25) this->board[x][y] = toupper(mark);
            else this -> board[x][y] = 0;
        }

        return true;
    }
    return false;
}

template <typename T>
void X_O5x5Board<T>::display_board() {
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
int X_O5x5Board<T>::count_three_in_a_row(T player) {
    int count = 0;
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) { // Loop stops at columns - 3
            if (this->board[i][j] == player && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2]) {
                count++;
            }
        }
    }

    // Check columns
    for (int i = 0; i <= this->rows - 3; i++) { // Loop stops at rows - 3
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == player &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j]) {
                count++;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == player &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                count++;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) { // Start from column 2 to columns - 1
            if (this->board[i][j] == player &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2]) {
                count++;
            }
        }
    }

    return count;
}

template <typename T>
bool X_O5x5Board<T>::is_win() {
    // Count the number of empty cells


    // If all squares except one are filled, compare three-in-a-row counts
    if (this->n_moves == 25) {
        int x_count = count_three_in_a_row('X');
        int o_count = count_three_in_a_row('O');

        cout << "Player X has " << x_count << " three-in-a-row patterns.\n";
        cout << "Player O has " << o_count << " three-in-a-row patterns.\n";

        if (x_count > o_count) {
            cout<<"player X wins!!"<<endl;
            return true;
        } else if (o_count > x_count) {
            cout<<"player O wins!!"<<endl;
            return true;
        }
    }
    // Otherwise, no winner yet
    return false;
}


template <typename T>
bool X_O5x5Board<T>::is_draw() {
    // Check if the board is full
    if(this->n_moves<24) return false;
    // Count the number of 'X' and 'O' moves on the board
    int x_count = count_three_in_a_row('X');
    int o_count = count_three_in_a_row('O');
    cout << "Player X has " << x_count << " three-in-a-row patterns.\n";
    cout << "Player O has " << o_count << " three-in-a-row patterns.\n";

    // Ensure the counts of 'X' and 'O' are equal (or off by one, if 'X' starts first)
    if (abs(x_count - o_count) > 1) {
        return false; // Invalid board state; not a draw
    }

    // If the board is full and there is no winner, it's a draw
    return !is_win();
}

template <typename T>
bool X_O5x5Board<T>::game_is_over() {
    // Game is over if there's a winner or the board is full (draw)
    return is_win() || is_draw();
}

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Function for human player to input their move
template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
    // Ensure input is within valid range
    while (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5) {
        cout << "Invalid move! Please enter valid values : ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> x >> y;
    }
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;  // Set dimension to 5 for a 5x5 board
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Function for random player to generate a move
template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 4
    y = rand() % this->dimension;
}




#endif //ASSIGNMENT_DEMO_5X5X_O_H
