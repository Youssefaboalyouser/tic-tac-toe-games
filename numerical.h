#ifndef _num_Tic_tac_H
#define _num_Tic_tac_H
#include "BoardGame_Classes.h"
#include <array>
#include <algorithm>
#include <set>
template <typename T>
class num_Tic_Tac_Board : public Board<T>
{
public:
    num_Tic_Tac_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class num_Tic_Tac_Player : public Player<T>
{
public:
    static set<int> exc_list;
    vector<int> numSet;
    num_Tic_Tac_Player(string name, int key);

    void getmove(int &x, int &y);
    void setBoard(Board<T> *b);
};
template <typename T>
set<int> num_Tic_Tac_Player<T>::exc_list;
template <typename T>
class num_Tic_Tac_Random_Player : public RandomPlayer<T>
{
public:
    vector<int> numSet;
    num_Tic_Tac_Random_Player(int key);
    void getmove(int &x, int &y);
};

//---------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
num_Tic_Tac_Board<T>::num_Tic_Tac_Board()
{
    this->rows = this->columns = 3;
    this->board = new int *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = -1;
        }
    }
    this->n_moves = 0;
};

template <typename T>
bool num_Tic_Tac_Board<T>::update_board(int x, int y, T mark)
{

    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == -1 || mark == -1))
    {
        if (mark == -1)
        {
            auto it = find(num_Tic_Tac_Player<T>::exc_list.begin(), num_Tic_Tac_Player<T>::exc_list.end(), this->board[x][y]);
            if (it != num_Tic_Tac_Player<T>::exc_list.end())
            {
                num_Tic_Tac_Player<T>::exc_list.erase(it);
            }
            this->board[x][y] = -1;
            this->n_moves--;
        }

        else
        {
            this->n_moves++;
            this->board[x][y] = mark;
            num_Tic_Tac_Player<T>::exc_list.insert(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
bool num_Tic_Tac_Board<T>::is_win()
{
    // Check rows and columns
    for (int i = 0; i < this->rows; i++)
    {
        // Check row i
        if (this->board[i][0] != -1 && this->board[i][1] != -1 && this->board[i][2] != -1 &&
            (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15))
        {
            return true;
        }

        // Check column i
        if (this->board[0][i] != -1 && this->board[1][i] != -1 && this->board[2][i] != -1 &&
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15))
        {
            return true;
        }
    }

    // Check diagonals
    if (this->board[0][0] != -1 && this->board[1][1] != -1 && this->board[2][2] != -1 &&
        (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15))
    {
        return true;
    }

    if (this->board[0][2] != -1 && this->board[1][1] != -1 && this->board[2][0] != -1 &&
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15))
    {
        return true;
    }

    return false;
}

template <typename T>
bool num_Tic_Tac_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool num_Tic_Tac_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}
template <typename T>
num_Tic_Tac_Player<T>::num_Tic_Tac_Player(string name, int key) : Player<T>(name, key)
{
    if (key == 1)
        this->numSet = {1, 3, 5, 7, 9};
    else
        this->numSet = {2, 4, 6, 8};
}

template <typename T>
void num_Tic_Tac_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces : ";
    cin >> x >> y;

    cout << "enter a valid available " << ((this->symbol) % 2 != 0 ? "odd values from[1,3,5,7,9]: " : "even values from[2,4,6,8]: ");
    while (1)
    {
        cin >> this->symbol;
        bool valid = find(this->numSet.begin(), this->numSet.end(), this->symbol) != this->numSet.end();
        bool found = find(num_Tic_Tac_Player<T>::exc_list.begin(), num_Tic_Tac_Player<T>::exc_list.end(), this->symbol) != num_Tic_Tac_Player<T>::exc_list.end();

        if (!valid || found)
        {
            cout << "enter a number other than " << this->symbol << endl;
            continue;
        }
        else
            break;
    }
}

// Constructor for num_Tic_Tac_Random_Player
template <typename T>
num_Tic_Tac_Random_Player<T>::num_Tic_Tac_Random_Player(int key) : RandomPlayer<T>(key)
{
    if (key == 1)
        this->numSet = {1, 3, 5, 7, 9};
    else
        this->numSet = {2, 4, 6, 8};
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void num_Tic_Tac_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension; // Random number between 0 and 2
    y = rand() % this->dimension;

    // Vector to store valid moves
    vector<int> validMoves;
    for (int n : this->numSet)
    {
        // If the number is not in the exc_list, add it to validMoves
        if (find(num_Tic_Tac_Player<T>::exc_list.begin(), num_Tic_Tac_Player<T>::exc_list.end(), n) == num_Tic_Tac_Player<T>::exc_list.end())
        {
            validMoves.push_back(n);
        }
    }

    // If there are valid moves, pick a random one
    if (!validMoves.empty())
    {
        this->symbol = validMoves[rand() % validMoves.size()];
    }
}

template <typename T>
void num_Tic_Tac_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << (to_string(this->board[i][j]) == "-1" ? " " : to_string(this->board[i][j])) << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
void num_Tic_Tac_Player<T>::setBoard(Board<T> *b)
{
    this->boardPtr = b;
}

#endif
