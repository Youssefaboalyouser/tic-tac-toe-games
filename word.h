#ifndef _word_H
#define _word_H
#include "BoardGame_Classes.h"
#include <fstream>
#include <unordered_set>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
// Load dictionary of valid words
std::unordered_set<std::string> loadDictionary(const std::string &filename)
{
    std::unordered_set<std::string> dictionary;
    std::ifstream file(filename);
    std::string word;
    while (file >> word)
    {
        dictionary.insert(word);
    }
    return dictionary;
}

const std::unordered_set<std::string> VALID_WORDS = loadDictionary("dic.txt");
template <typename T>
class word_Board : public Board<T>
{
private:
    bool isValidWord(const std::string &word);

public:
    word_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class word_Player : public Player<T>
{
public:
    word_Player(string name, T symbol);
    void getmove(int &x, int &y);
    char get_new_char();
};

template <typename T>
class word_Random_Player : public RandomPlayer<T>
{
public:
    word_Random_Player(T symbol);
    void getmove(int &x, int &y);
    char get_newRandom_char();
};
//--------------------------------------- IMPLEMENTATION

using namespace std;

// Constructor for X_O_Board
template <typename T>
word_Board<T>::word_Board()
{
    this->rows = this->columns = 3;
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
bool word_Board<T>::update_board(int x, int y, T symbol)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 1))
    {
        if (symbol == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = toupper(symbol); // Directly assign the symbol here
        }
        return true;
    }
    return false;
}

template <typename T>
void word_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
bool word_Board<T>::is_win()
{
    std::string word;

    // Check rows
    for (int i = 0; i < this->rows; i++)
    {
        word = "";
        for (int j = 0; j < this->columns; j++)
        {
            word += this->board[i][j];
        }
        if (isValidWord(word))
            return true;
    }

    // Check columns
    for (int j = 0; j < this->columns; j++)
    {
        word = "";
        for (int i = 0; i < this->rows; i++)
        {
            word += this->board[i][j];
        }
        if (isValidWord(word))
            return true;
    }

    // Check diagonals
    word = "";
    for (int i = 0; i < this->rows; i++)
    {
        word += this->board[i][i];
    }
    if (isValidWord(word))
        return true;

    word = "";
    for (int i = 0; i < this->rows; i++)
    {
        word += this->board[i][this->columns - i - 1];
    }
    if (isValidWord(word))
        return true;

    return false;
}
template <typename T>
bool word_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool word_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

// Helper method to validate if a word exists in the dictionary
template <typename T>
bool word_Board<T>::isValidWord(const std::string &word)
{
    return VALID_WORDS.find(word) != VALID_WORDS.end();
}
//--------------------------------------------------------------
template <typename T>
word_Player<T>::word_Player(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
char word_Player<T>::get_new_char()
{
    char ch;
    cout << "Write your character: ";
    cin >> ch;
    return ch;
}
template <typename T>
void word_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    while (cin.fail() || x < 0 || x >= 4 || y < 0 || y >= 4)
    {
        cout << "Invalid move! Please enter valid position: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> x >> y;
    }
    this->symbol = get_new_char();
    // this->boardPtr->update_board(x, y, this->symbol);
}

//----------------------------
template <typename T>
word_Random_Player<T>::word_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
char word_Random_Player<T>::get_newRandom_char()
{
    char ch = 'A' + (rand() % 26);
    return ch;
}
template <typename T>
void word_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = get_newRandom_char();
}

#endif
