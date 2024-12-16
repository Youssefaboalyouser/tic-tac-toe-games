#include <iostream>
#include "BoardGame_Classes.h"
#include "MinMaxPlayer.h"
#include "5x5X_O.h"
#include "Misere_X_O.h"
#include "Ultimate_X_O.h"
#include "pyramid.h"
#include "word.h"
#include "four_in_row.h"
#include "numerical.h"
#include "numerical_AI.h"
#include "four_four_tic_tac_toe.h"
using namespace std;
int main()
{
    bool loop = true;
    while (loop)
    {
        cout << "------------------ WOELCOM TO OUR GAMES --------------------------\n";
        cout << "we have * 8 * games\na) Pyramid Tic-Tac-Toe\t\tb) Four-in-a-row Tic-Tac-Toe\nc) 5x5 Tic-Tac-Toe\t\td) Word Tic-Tac-Toe\ne) Numerical Tic-Tac-Toe\tf) Misere Tic-Tac-Toe\ng) 4x4 Tic-Tac-Toe\t\th) Ultimate Tic-Tac-Toe\n";
        // cout << "------------------------------------------------------------------\n";
        cout << endl;
        cout << "Do you Want to Play(y/n)? 🤔: ";
        string play_or_not, which_game, player1Name, player2Name;
        int choice1, choice2;
        cin >> play_or_not;
        if (play_or_not == "y")
        {
            cout << "let's have some fun 😉 chose your game: ";
            cin >> which_game;
            cout << "Enter Player X name: ";
            cin >> player1Name;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer(AI)\n";
            cin >> choice1;
            while (cin.fail() || choice1 > 3 || choice1 < 1)
            {
                cin.clear();                                         // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Try again 🤬" << endl;
                cin >> choice1; // Re-prompt input
            }
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer(AI)\n";
            cin >> choice2;
            while (cin.fail() || choice2 > 3 || choice2 < 1)
            {
                cin.clear();                                         // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Try again 🤬" << endl;
                cin >> choice2; // Re-prompt input
            }
            if (which_game == "a")
            {
                Player<char> *players[2];
                Pyramid_Board<char> *B = new Pyramid_Board<char>();
                switch (choice1)
                {
                case 1:
                    players[0] = new Pyramid_Player<char>(player1Name, 'X');
                    break;
                case 2:
                    players[0] = new X_O_Random_Player<char>('X');
                    break;
                case 3:
                    players[0] = new X_O_MinMax_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    loop = false;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new Pyramid_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new X_O_Random_Player<char>('O');
                    break;
                case 3:
                    players[1] = new X_O_MinMax_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    loop = false;
                    continue;
                }
                GameManager<char> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            //---------------------------------------------------------
            else if (which_game == "b")
            {
                Player<char> *players[2];
                four_in_row_Board<char> *B = new four_in_row_Board<char>();
                switch (choice1)
                {
                case 1:
                    players[0] = new four_in_row_Player<char>(player1Name, 'X');
                    players[0]->setBoard(B);
                    break;
                case 2:
                    players[0] = new four_in_row_Random_Player<char>('X');
                    players[0]->setBoard(B);
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new four_in_row_Player<char>(player2Name, 'O');
                    players[1]->setBoard(B);
                    break;
                case 2:
                    players[1] = new four_in_row_Random_Player<char>('O');
                    players[1]->setBoard(B);
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                GameManager<char> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            // ---------------------------------------------------------
            else if (which_game == "c")
            {
                Player<char> *players[2];
                X_O5x5Board<char> *B = new X_O5x5Board<char>();
                switch (choice1)
                {
                case 1:
                    players[0] = new X_O_Player<char>(player1Name, 'X');
                    break;
                case 2:
                    players[0] = new X_O_Random_Player<char>('X');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new X_O_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new X_O_Random_Player<char>('O');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                GameManager<char> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            // ---------------------------------------------------------
            else if (which_game == "d")
            {
                Player<char> *players[2];
                word_Board<char> *B = new word_Board<char>();
                switch (choice1)
                {
                case 1:
                    players[0] = new word_Player<char>(player1Name, ' ');
                    break;
                case 2:
                    players[0] = new word_Random_Player<char>(' ');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new word_Player<char>(player2Name, ' ');
                    break;
                case 2:
                    players[1] = new word_Random_Player<char>(' ');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                GameManager<char> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            // ---------------------------------------------------------
            else if (which_game == "e")
            {
                Player<int> *players[2];
                num_Tic_Tac_Board<int> *B = new num_Tic_Tac_Board<int>();
                switch (choice1)
                {
                case 1:
                    players[0] = new num_Tic_Tac_Player<int>(player1Name, 1);
                    players[0]->setBoard(B);
                    break;
                case 2:
                    players[0] = new num_Tic_Tac_Random_Player<int>(1);
                    players[0]->setBoard(B);
                    break;
                case 3:
                    players[0] = new num_Tic_Tac_AI_Player<int>(1);
                    players[0]->setBoard(B);
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    loop = false;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new num_Tic_Tac_Player<int>(player2Name, 2);
                    players[1]->setBoard(B);
                    break;
                case 2:
                    players[1] = new num_Tic_Tac_Random_Player<int>(2);
                    players[1]->setBoard(B);
                    break;
                case 3:
                    players[1] = new num_Tic_Tac_AI_Player<int>(2);
                    players[1]->setBoard(B);
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    loop = false;
                }
                GameManager<int> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            // ---------------------------------------------------------
            else if (which_game == "f")
            {
                Player<char> *players[2];
                Misere_Board<char> *B = new Misere_Board<char>();
                switch (choice1)
                {
                case 1:
                    players[0] = new Misere_player<char>(player1Name, 'X');
                    break;
                case 2:
                    players[0] = new Misere_Random_Player<char>('X');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new Misere_player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new Misere_Random_Player<char>('O');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                GameManager<char> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            // ---------------------------------------------------------
            else if (which_game == "g")
            {
                Player<char> *players[2];
                four_four_Tic_Tac_Toe_Board<char> *B = new four_four_Tic_Tac_Toe_Board<char>();
                switch (choice1)
                {
                case 1:
                    players[0] = new four_four_Tic_Tac_Toe_Player<char>(player1Name, 'X');
                    players[0]->setBoard(B);
                    break;
                case 2:
                    players[0] = new four_four_Tic_Tac_Toe_Random_Player<char>('X');
                    players[0]->setBoard(B);
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new four_four_Tic_Tac_Toe_Player<char>(player2Name, 'O');
                    players[1]->setBoard(B);
                    break;
                case 2:
                    players[1] = new four_four_Tic_Tac_Toe_Random_Player<char>('O');
                    players[1]->setBoard(B);
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                GameManager<char> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            else if (which_game == "h")
            {
                Player<char> *players[2];
                Ultimate_Board<char> *B = new Ultimate_Board<char>();
                switch (choice1)
                {
                case 1:
                    players[0] = new Ultimate_Player<char>(player1Name, 'X');
                    break;
                case 2:
                    players[0] = new Ultimate_Random_Player<char>('X');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    players[1] = new Ultimate_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new Ultimate_Random_Player<char>('O');
                    break;
                default:
                    cout << "AI player didn't support in this game 😬 .\n";
                    loop = false;
                    continue;
                }
                GameManager<char> pyramid_game(B, players);
                pyramid_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i)
                {
                    delete players[i];
                }
            }
            else
            {
                cout << "INVALID choice <🥺> try again" << endl;
            }
        }
        else if (play_or_not == "n")
        {
            cout << "GOOD BYE 🥰";
            loop = false;
        }
        else
        {
            cout << "INVALID choice <🥺> try again" << endl;
        }
    }
}
