#ifndef ASSIGNMENT_DEMO_MISERE_X_O_H
#define ASSIGNMENT_DEMO_MISERE_X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class Misere_Board:public Board<T> {
public:
    Misere_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    static  bool flag;

};

template <typename T>
bool Misere_Board<T>::flag =false;


template <typename T>
class Misere_player : public Player<T> {
public:
    Misere_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Misere_Random_Player : public RandomPlayer<T>{
public:
    Misere_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
    template <typename U>
    friend class Misere_Board;//error

};


//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>


using namespace std;

// Constructor for Misere_Board
template <typename T>
Misere_Board<T>::Misere_Board() {
    this->rows = this->columns = 3;
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
bool Misere_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if(Misere_Board<T>::flag)
        return true;

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Misere_Board<T>::display_board() {
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


// Returns true if there is any winner
template <typename T>
bool Misere_Board<T>::is_win() {
    if(flag)
        return true;

    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {

            flag =true;
            return false;

        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        flag =true;
        return false;

    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Misere_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Misere_player
template <typename T>
Misere_player<T>::Misere_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_player<T>::getmove(int& x, int& y) {
    if(Misere_Board<T>::flag){
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    while (cin.fail() || x < 0 || x >= 9 || y < 0 || y >= 9) {
        cout << "Invalid move! Please enter values between 0 and 2: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> x >> y;
    }
}

// Constructor for Misere_Random_Player
template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


#endif //ASSIGNMENT_DEMO_MISERE_Misere_H
