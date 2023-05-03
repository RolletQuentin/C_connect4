#ifndef __PUISSANCE4_H_
#define __PUISSANCE4_H_

#define N 10
#define TABULATION printf("          ")
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define WHITE "\033[0;37m"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "usefull_functions.h"

/*!
\fn void init (int ttint_board[N][N])
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 01/12/2022
\brief Initialization of the matrix representing the game board.
\param ttint_board the board of the game
*/
void init(int ttint_board[N][N]);

/*!
void printBoardGame(int ttint_board[N][N], char *str_player1Name, char *str_player2Name, int int_currentPlayer)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 01/12/2022
\brief Print the board game.
\param ttint_board the board of the game
\param *str_player1Name name of the player 1
\param *str_player2Name name of the player 2
\param int_currentPlayer 0 if it's the turn of the first player, 1 if it's the turn of the second
*/
void printBoardGame(int ttint_board[N][N], char *str_player1Name, char *str_player2Name, int int_currentPlayer);

/*!
\fn void gravity(int ttint_board[N][N], char *str_player1Name, char *str_player2Name, int int_currentPlayer)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 02/12/2022
\brief Implementation of the gravity. Like this, the coins fall down when a player play or when the board game is rotated.
\param ttint_board the board of the game
\param *str_player1Name name of the player 1
\param *str_player2Name name of the player 2
\param int_currentPlayer 0 if it's the turn of the first player, 1 if it's the turn of the second
*/
void gravity(int ttint_board[N][N], char *str_player1Name, char *str_player2Name, int int_currentPlayer);

/*!
\fn int play(int ttint_board[N][N], int int_playerNumber, int int_column, char *str_player1Name, char *str_player2Name)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 02/12/2022
\brief Allow to the player to play.
\param ttint_board the board of the game
\param int_playerNumber the number of the player (0 or 1)
\param int_column the choosen column by the player
\param *str_player1Name name of the player 1
\param *str_player2Name name of the player 2
\return -1 if an error is occur, else 1
*/
int play(int ttint_board[N][N], int int_playerNumber, int int_column, char *str_player1Name, char *str_player2Name);

/*!
\fn int isWinner(int ttint_board[N][N])
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 02/12/2022
\brief Test if there is a victory condition.
\param ttint_board the board of the game
\return -1 if there is no winner, 0 or 1 if there is a winner (the number of the player), 2 if there is an equality
*/
int isWinner(int ttint_board[N][N]);

/*!
\fn void playGame(int int_classic)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 02/12/2022
\brief Allow to play a game.
\param int_classic 1 correspond to a classical game, 0 if you want to have rotations
*/
void playGame(int int_classic);

/*!
\fn int printMenuPuissance4()
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 02/12/2022
\brief print the sub menu to play puissance4 game
\return 1 if the players want to continue, else 0
*/
int printMenuPuissance4();

/*!
\fn void rotate(int ttint_board[N][N])
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 02/12/2022
\brief To make a rotation of 90° on the board.
\param ttint_board the board of the game
*/
void rotate(int ttint_board[N][N]);

#endif