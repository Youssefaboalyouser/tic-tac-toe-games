#ifndef _four_four_Tic_Tac_Toe_H
#define _four_four_Tic_Tac_Toe_H

#include "BoardGame_Classes.h"

template <typename T>
class four_four_Tic_Tac_Toe_Board : public Board<T>
{
public:
    four_four_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    T getBoard(int x, int y); // Add this line
};

template <typename T>
class four_four_Tic_Tac_Toe_Player : public Player<T>
{
public:
    four_four_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y);
    void setName(const string &newName); // Method to set the player's name
    string getName();
};

template <typename T>
class four_four_Tic_Tac_Toe_Random_Player : public RandomPlayer<T>
{
public:
    four_four_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y);
    static bool randP;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype> // for toupper()

using namespace std;

template <typename T>
bool four_four_Tic_Tac_Toe_Random_Player<T>::randP = false;

template <typename T>
T four_four_Tic_Tac_Toe_Board<T>::getBoard(int x, int y)
{
    return this->board[x][y];
}

// Constructor for four_four_Tic_Tac_Toe_Board
template <typename T>
four_four_Tic_Tac_Toe_Board<T>::four_four_Tic_Tac_Toe_Board()
{
    this->rows = 4;
    this->columns = 4;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            if (i == 0)
            {
                if (j % 2 == 0)
                    this->board[i][j] = 'O';
                else
                    this->board[i][j] = 'X';
            }
            else if (i == 3)
            {
                if (j % 2 == 0)
                    this->board[i][j] = 'X';
                else
                    this->board[i][j] = 'O';
            }
            else
                this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool four_four_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark)
{
    static int old_x = -5, old_y = -5;
    if ((!(x < 0 || x >= this->rows || y < 0 || y >= this->columns)))
    {
        if (mark == 0 && !four_four_Tic_Tac_Toe_Random_Player<T>::randP)
        {
            this->board[x][y] = 0;
            old_x = x;
            old_y = y;
        }
        else if (four_four_Tic_Tac_Toe_Random_Player<T>::randP)
        {
            if (mark == 0)
            {
                this->board[x][y] = 0;
            }

            else if (this->board[x][y] == 0)
            {
                this->board[x][y] = mark;
                four_four_Tic_Tac_Toe_Random_Player<T>::randP = false;
            }
        }
        else
        {
            if (this->board[x][y] == 0 && ((abs(x - old_x) == 1 && y == old_y) || (abs(y - old_y) == 1 && x == old_x)))
            {
                this->board[x][y] = mark;
                this->n_moves++;
            }
            else
            {
                if (old_x == -5 || old_y == -5)
                    return false;
                this->board[old_x][old_y] = mark;
                return false;
            }
        }

        return true;
    }

    return false;
}

// Display the board and the pieces on it
template <typename T>
void four_four_Tic_Tac_Toe_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")" << setw(4) << "    ";
            cout << setw(2) << (this->board[i][j] == 0 ? " " : string(1, this->board[i][j])) << " |";
        }
        cout << "\n------------------------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool four_four_Tic_Tac_Toe_Board<T>::is_win()
{
    // Check rows and columns
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col <= 4 - 3; col++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row][col + 1] &&
                this->board[row][col] == this->board[row][col + 2])
            {
                return true;
            }
        }
    }

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row <= 4 - 3; row++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row + 1][col] &&
                this->board[row][col] == this->board[row + 2][col])
            {
                return true;
            }
        }
    }

    // Check diagonals
    for (int row = 0; row <= 4 - 3; row++)
    {
        for (int col = 0; col <= 4 - 3; col++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row + 1][col + 1] &&
                this->board[row][col] == this->board[row + 2][col + 2])
            {
                return true;
            }
        }
    }

    for (int row = 0; row <= 4 - 3; row++)
    {
        for (int col = 2; col < 4; col++)
        {
            if (this->board[row][col] != 0 &&
                this->board[row][col] == this->board[row + 1][col - 1] &&
                this->board[row][col] == this->board[row + 2][col - 2])
            {
                return true;
            }
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool four_four_Tic_Tac_Toe_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool four_four_Tic_Tac_Toe_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for four_four_Tic_Tac_Toe_Player
template <typename T>
four_four_Tic_Tac_Toe_Player<T>::four_four_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_four_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y)
{
    int targetX, targetY;

    cout << "\nPlease enter your token pos (x, y) separated by spaces: \n";
    cin >> x >> y;
    while (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5)
    {
        cout << "Invalid move! Please enter valid values: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> x >> y;
    }
    // Cast boardPtr to the derived class type
    auto *derivedBoard = static_cast<four_four_Tic_Tac_Toe_Board<T> *>(this->boardPtr);

    // Access the getBoard method of the derived class
    if (derivedBoard->getBoard(x, y) == this->symbol)
    {
        derivedBoard->update_board(x, y, 0);
    }
    else
    {
        cout << "Invalid selection! The selected position does not belong to your symbol.\n";
        return;
    }

    cout << "\nEnter the target pos (x, y) separated by spaces: \n";
    cin >> targetX >> targetY;
    x = targetX;
    y = targetY;
}

// Constructor for four_four_Tic_Tac_Toe_Random_Player
template <typename T>
four_four_Tic_Tac_Toe_Random_Player<T>::four_four_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 4;
    this->name = "Random Computer Player";

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void four_four_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y)
{
    four_four_Tic_Tac_Toe_Random_Player<T>::randP = true;
    vector<pair<int, int>> validMoves;
    while (validMoves.empty())
    {
        auto *derivedBoard = static_cast<four_four_Tic_Tac_Toe_Board<T> *>(this->boardPtr);

        while (derivedBoard->getBoard(x, y) != this->symbol)
        {
            x = rand() % this->dimension;
            y = rand() % this->dimension;
        }

        // Check adjacent cells for validity
        if (x - 1 >= 0 && derivedBoard->getBoard(x - 1, y) == 0)
        {
            validMoves.push_back({x - 1, y}); // Add top cell if valid
        }

        if (x + 1 < this->dimension && derivedBoard->getBoard(x + 1, y) == 0)
        {
            validMoves.push_back({x + 1, y}); // Add bottom cell if valid
        }

        if (y - 1 >= 0 && derivedBoard->getBoard(x, y - 1) == 0)
        {
            validMoves.push_back({x, y - 1}); // Add left cell if valid
        }

        if (y + 1 < this->dimension && derivedBoard->getBoard(x, y + 1) == 0)
        {
            validMoves.push_back({x, y + 1}); // Add right cell if valid
        }
    }
    this->boardPtr->update_board(x, y, 0);
    int ranInx = rand() % validMoves.size();
    x = validMoves[ranInx].first;
    y = validMoves[ranInx].second;
}

template <typename T>
void four_four_Tic_Tac_Toe_Player<T>::setName(const string &newName)
{
    this->name = newName;
}

template <typename T>
string four_four_Tic_Tac_Toe_Player<T>::getName()
{
    return this->name;
}

#endif // _four_four_Tic_Tac_Toe_H
