#ifndef _NUM_TIC_TAC_AI_H
#define _NUM_TIC_TAC_AI_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <array>
#include <set>
#include <tuple>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

// --------------------- AI Player Class ---------------------
template <typename T>
class num_Tic_Tac_AI_Player : public Player<T>
{
public:
    array<int, 5> numSet;

    static set<int> exc_list; // Numbers already used in the game

    num_Tic_Tac_AI_Player(int key);
    void getmove(int &x, int &y) override;

private:
    int calculateMinMax(bool isMaximizing, int currentSum, int alpha, int beta);
    tuple<int, int, T> getBestMove();
};

template <typename T>
set<int> num_Tic_Tac_AI_Player<T>::exc_list;

template <typename T>
num_Tic_Tac_AI_Player<T>::num_Tic_Tac_AI_Player(int key) : Player<T>("AI Player", key)
{
    if (key == 1)
    {
        numSet = {1, 3, 5, 7, 9}; // Odd numbers for AI
    }
    else
    {

        numSet = {2, 4, 6, 8}; // Even numbers for AI
    }
}

// Get the best move for the AI
template <typename T>
void num_Tic_Tac_AI_Player<T>::getmove(int &x, int &y)
{
    auto [bestX, bestY, bestNum] = getBestMove();
    x = bestX;
    y = bestY;
    this->symbol = bestNum;
    exc_list.insert(bestNum); // Assign the chosen number to the player's symbol
}

template <typename T>
int num_Tic_Tac_AI_Player<T>::calculateMinMax(bool isMaximizing, int currentSum, int alpha, int beta)
{
    // Terminal states: win, draw

    if (this->boardPtr->is_win())
        return isMaximizing ? -1 : 1;
    if (this->boardPtr->is_draw())
        return 0;

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (auto num : numSet)
            {
                // Ensure the number has not been used and the cell is valid
                if (exc_list.count(num) == 0 && this->boardPtr->update_board(i, j, num))
                {
                    exc_list.insert(num);
                    int score = calculateMinMax(!isMaximizing, currentSum + num, alpha, beta);
                    this->boardPtr->update_board(i, j, -1); // Undo move
                    exc_list.erase(num);                    // Undo number usage

                    if (isMaximizing)
                    {
                        bestValue = max(bestValue, score);
                        alpha = max(alpha, bestValue);
                    }
                    else
                    {
                        bestValue = min(bestValue, score);
                        beta = min(beta, bestValue);
                    }

                    if (beta <= alpha)
                        return bestValue; // Prune
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
tuple<int, int, T> num_Tic_Tac_AI_Player<T>::getBestMove()
{
    int bestValue = numeric_limits<int>::min();
    tuple<int, int, T> bestMove = {-1, -1, -1};

    if (this->boardPtr->is_win() || this->boardPtr->is_draw())
    {
        return bestMove;
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (auto num : numSet)
            {
                if (exc_list.count(num) == 0 && this->boardPtr->update_board(i, j, num))
                {
                    exc_list.insert(num);
                    int moveValue = calculateMinMax(false, num, numeric_limits<int>::min(), numeric_limits<int>::max());

                    if (moveValue > bestValue)
                    {
                        bestValue = moveValue;
                        bestMove = {i, j, num};
                    }

                    exc_list.erase(num);
                    this->boardPtr->update_board(i, j, -1);
                }
            }
        }
    }

    return bestMove;
}

#endif //_NUM_TIC_TAC_AI_H
