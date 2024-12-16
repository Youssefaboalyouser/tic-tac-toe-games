#ifndef _PYRAMID_H
#define _PYRAMID_H

#include "BoardGame_Classes.h"

template <typename T>
class Pyramid_Board : public Board<T> {
public:
    Pyramid_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    int pyramidStructure[3] = {1, 3, 5}; // Define the correct pyramid layers (base-first)
    bool check_horizontal(int layer);
    bool check_vertical();
    bool check_diagonal();
};
template <typename T>
class Pyramid_Player : public Player<T> {
public:
    Pyramid_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
};



#include <iomanip>
#include <iostream>
using namespace std;

template <typename T>
Pyramid_Board<T>::Pyramid_Board() {
    this->rows = 3; // 3 layers
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[pyramidStructure[i]]{};
    }
}

template <typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < pyramidStructure[x] && (this->board[x][y] == 0 || symbol == 0)) {
        if (symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}
template <typename T>
void Pyramid_Board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        // Calculate indentation to center-align the current row
        int indentation = (pyramidStructure[this->rows - 1] - pyramidStructure[i]) * 2;
        
        // Top border of boxes
        cout << string(indentation, ' '); 
        for (int j = 0; j < pyramidStructure[i]; ++j) {
            cout << "+---";
        }
        cout << "+\n";

        // Cell contents with side borders
        cout << string(indentation, ' '); 
        for (int j = 0; j < pyramidStructure[i]; ++j) {
            cout << "| " << (this->board[i][j] ? this->board[i][j] : ' ') << " ";
        }
        cout << "|\n";
    }

    // Bottom border for the last row
    int last_indentation = (pyramidStructure[this->rows - 1] - pyramidStructure[this->rows - 1]) * 2;
    cout << string(last_indentation, ' ');
    for (int j = 0; j < pyramidStructure[this->rows - 1]; ++j) {
        cout << "+---";
    }
    cout << "+\n";
}


template <typename T>
bool Pyramid_Board<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if (check_horizontal(i)) return true;
    }
    return check_vertical() || check_diagonal();
}

template <typename T>
bool Pyramid_Board<T>::is_draw() {
    int totalCells = 0;
    for (int i = 0; i < this->rows; ++i) {
        totalCells += pyramidStructure[i];
    }
    return (this->n_moves == totalCells && !is_win());
}

template <typename T>
bool Pyramid_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
bool Pyramid_Board<T>::check_horizontal(int layer) {
    for (int j = 0; j < pyramidStructure[layer] - 2; ++j) {
        if (this->board[layer][j] != 0 && this->board[layer][j] == this->board[layer][j + 1] && this->board[layer][j + 1] == this->board[layer][j + 2]) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool Pyramid_Board<T>::check_vertical() {
    for (int j = 0; j < 3; ++j) { // Middle column for diagonal checks
        if (this->board[2][j] != 0 && this->board[2][j] == this->board[1][j / 2] && this->board[1][j / 2] == this->board[0][0]) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool Pyramid_Board<T>::check_diagonal() {
    if (this->board[2][0] != 0 && this->board[2][0] == this->board[1][0] && this->board[1][0] == this->board[0][0]) {
        return true;
    }
    if (this->board[2][4] != 0 && this->board[2][4] == this->board[1][2] && this->board[1][2] == this->board[0][0]) {
        return true;
    }
    return false;
}
template <typename T>
Pyramid_Player<T>::Pyramid_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_Player<T>::getmove(int &x, int &y) {
    cout << "Enter your move: ";
    cin >> x >> y;
}


#endif //_PYRAMID_H
