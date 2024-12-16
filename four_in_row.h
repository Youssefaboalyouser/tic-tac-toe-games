#ifndef _3X3four_in_row_H
#define _3X3four_in_row_H

#include "BoardGame_Classes.h"

template <typename T>
class four_in_row_Board : public Board<T>
{
public:
    four_in_row_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    auto get_board(int x, int y);
};

template <typename T>
class four_in_row_Player : public Player<T>
{
public:
    four_in_row_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class four_in_row_Random_Player : public RandomPlayer<T>
{
public:
    four_in_row_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype> // for toupper()
#include <stdio.h>
using namespace std;

// Constructor for four_in_row_Board

template <typename T>
auto four_in_row_Board<T>::get_board(int x, int y)
{
    return this->board[x][y];
}
template <typename T>
four_in_row_Board<T>::four_in_row_Board()
{
    this->rows = 6;
    this->columns = 7;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool four_in_row_Board<T>::update_board(int x, int y, T mark)
{

    // Only update if move is valid
    if (!(y < 0 || y >= 7 || x < 0 || x >= 6))
    {
        bool valid_col = true;

        if (this->board[x][y] != 0 && mark != 0)
            return false;
        else if (this->board[x][y] != 0 && mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
            return true;
        }
        else
        {
            this->board[x][y] = mark;
            return true;
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void four_in_row_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << j << "    ";
            cout << setw(2) << (this->board[i][j] == 0 ? " " : string(1, this->board[i][j])) << " |";
        }
        cout << "\n----------------------------------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool four_in_row_Board<T>::is_win()
{
    // Check rows for horizontal wins
    // Check vertical win
    for (int col = 0; col < 7; col++)
    {
        for (int row = 0; row <= 6 - 4; row++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row + 1][col] &&
                this->board[row][col] == this->board[row + 2][col] &&
                this->board[row][col] == this->board[row + 3][col])
            {
                return true;
            }
        }
    }

    // Check horizontal win
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col <= 7 - 4; col++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row][col + 1] &&
                this->board[row][col] == this->board[row][col + 2] &&
                this->board[row][col] == this->board[row][col + 3])
            {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right) win
    for (int row = 0; row <= 6 - 4; row++)
    {
        for (int col = 0; col <= 7 - 4; col++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row + 1][col + 1] &&
                this->board[row][col] == this->board[row + 2][col + 2] &&
                this->board[row][col] == this->board[row + 3][col + 3])
            {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right) win
    for (int row = 3; row < 6; row++)
    {
        for (int col = 0; col <= 7 - 4; col++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row - 1][col + 1] &&
                this->board[row][col] == this->board[row - 2][col + 2] &&
                this->board[row][col] == this->board[row - 3][col + 3])
            {
                return true;
            }
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool four_in_row_Board<T>::is_draw()
{
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool four_in_row_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for four_in_row_Player
template <typename T>
four_in_row_Player<T>::four_in_row_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_in_row_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move column number (0 to 6) separated by spaces: ";
    cin >> y;

    x = 5;
    while (cin.fail() ||  y < 0 || y >= 7)
    {
        cout << "Invalid move! Please enter valid column: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> y;
    }
    auto *boardDerived = dynamic_cast<four_in_row_Board<T> *>(this->boardPtr); // Cast to derived type
    if (boardDerived)
    {
        while (x >= 0 && boardDerived->get_board(x, y) != 0)
        {
            x--;
        }
        if (x < 0)
        {
            cout << "Ivalid column. Choose a different column.\n";
        }
    }
    else
    {
        cerr << "Error: Board pointer is not of type four_in_row_Board.\n";
    }
}

// Constructor for four_in_row_Random_Player
template <typename T>
four_in_row_Random_Player<T>::four_in_row_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void four_in_row_Random_Player<T>::getmove(int &x, int &y)
{
    y = rand() % this->dimension;
    x = 5;
    auto *boardDerived = dynamic_cast<four_in_row_Board<T> *>(this->boardPtr); // Cast to derived type

    while (x >= 0 && boardDerived->get_board(x, y) != 0)
    {
        x--;
    }
}

#endif //_3X3four_in_row_H
