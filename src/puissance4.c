/*!
\file puissance4.c
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 01/12/2022
\brief to play puissance4 game
*/

#include "puissance4.h"

void init(int ttint_board[N][N])
{
    int int_i; // iteration variable

    // fill the board game of -1
    for (int_i = 0; int_i < N; int_i++)
    {
        fillIntTableAuto(ttint_board[int_i], N, -1);
    }
}

void printBoardGame(int ttint_board[N][N], char *str_player1Name, char *str_player2Name, int int_currentPlayer)
{
    int int_i; // iteration variable
    int int_j; // iteration variable

    // to clear the console
    system("clear");

    // print palyers in game
    printf("Joueur 1 ");
    printf(RED);
    printf("●");
    printf(WHITE);
    printf(" : %s\n", str_player1Name);

    printf("Joueur 2 ");
    printf(YELLOW);
    printf("●");
    printf(WHITE);
    printf(" : %s\n\n\n", str_player2Name);

    // first line (column index)
    TABULATION;
    printf("  ");
    for (int_j = 0; int_j < N; int_j++)
    {
        printf("  %d ", int_j);
    }
    printf("\n");

    // middle lines
    for (int_i = 0; int_i < N; int_i++)
    {
        // top line
        TABULATION;
        printf("  ");
        for (int_j = 0; int_j < N; int_j++)
        {
            printf("+---");
        }
        printf("+\n");

        // number line
        TABULATION;
        printf("%d ", int_i);
        // print each cases
        for (int_j = 0; int_j < N; int_j++)
        {
            // no player
            if (ttint_board[int_i][int_j] == -1)
            {
                printf("|   ");
            }
            // player 1
            else if (ttint_board[int_i][int_j] == 0)
            {
                printf("| ");
                printf(RED);
                printf("● ");
                printf(WHITE);
            }
            // player 2
            else
            {
                printf("| ");
                printf(YELLOW);
                printf("● ");
                printf(WHITE);
            }
        }
        printf("|\n");
    }

    // last line
    TABULATION;
    printf("  ");
    for (int_j = 0; int_j < N; int_j++)
    {
        printf("+---");
    }
    printf("+\n\n");

    // active player
    TABULATION;
    if (int_currentPlayer == 0)
    {
        printf("         C'est au tour de %s ", str_player1Name);
        printf(RED);
        printf("●");
        printf(WHITE);
        printf(" !\n\n\n");
    }
    else
    {
        printf("         C'est au tour de %s ", str_player2Name);
        printf(YELLOW);
        printf("●");
        printf(WHITE);
        printf(" !\n\n\n");
    }
}

void gravity(int ttint_board[N][N], char *str_player1Name, char *str_player2Name, int int_currentPlayer)
{
    int int_i;                     // iteration variable
    int int_j;                     // iteration variable
    int int_k;                     // iteration variable
    int int_numberOfCoinsAbove[N]; // table of number of coins above for each columns
    int int_change;                // equals to 1 if a change is occur

    fillIntTableAuto(int_numberOfCoinsAbove, N, 0);

    printBoardGame(ttint_board, str_player1Name, str_player2Name, int_currentPlayer);

    // for each columns
    for (int_i = 0; int_i < N - 1; int_i++)
    {
        // no change at the beginning
        int_change = 0;

        for (int_j = 0; int_j < N; int_j++)
        {
            // if we have a coin, we add 1 to numberOfCoinsAbove to know how many coins we have to move
            if (ttint_board[int_i][int_j] != -1)
            {
                int_numberOfCoinsAbove[int_j]++;

                // if there is no coin in the bottom case, all the coins above the case fall (because of gravity)
                if (ttint_board[int_i + 1][int_j] == -1)
                {
                    for (int_k = 0; int_k < int_numberOfCoinsAbove[int_j]; int_k++)
                    {
                        int_change = 1;
                        // up the empty case
                        swapElementIntMatrixStatic(ttint_board, int_i + 1 - int_k, int_j, int_i - int_k, int_j);
                    }
                }
            }
        }
        if (int_change == 1)
        {
            printBoardGame(ttint_board, str_player1Name, str_player2Name, int_currentPlayer);
            usleep(100000);
        }
    }
}

int play(int ttint_board[N][N], int int_playerNumber, int int_column, char *str_player1Name, char *str_player2Name)
{
    int int_error;

    int_error = 1;

    // out of bounds
    if ((int_column < 0) || (int_column > N - 1))
    {
        fprintf(stderr, "Merci de saisir un entier entre 0 et %d.\n", N - 1);
        int_error = -1;
    }
    // the case is not empty
    else if (ttint_board[0][int_column] != -1)
    {
        fprintf(stderr, "La colonne est pleine ! Merci de choisir une colonne ou il reste de la place.\n");
        int_error = -1;
    }
    else
    {
        // we put a coin on the top of the board, the the gravity play his role
        ttint_board[0][int_column] = int_playerNumber;
        gravity(ttint_board, str_player1Name, str_player2Name, int_playerNumber);
    }

    return (int_error);
}

void rotate(int ttint_board[N][N])
{
    int int_i;   // iteration variable
    int int_j;   // iteration variable
    int int_tmp; //

    for (int_i = 0; int_i < N / 2; int_i++)
    {
        for (int_j = 0; int_j < N / 2; int_j++)
        {
            int_tmp = ttint_board[N - int_j - 1][int_i];
            ttint_board[N - int_j - 1][int_i] = ttint_board[N - int_i - 1][N - int_j - 1];
            ttint_board[N - int_i - 1][N - int_j - 1] = ttint_board[int_j][N - int_i - 1];
            ttint_board[int_j][N - int_i - 1] = ttint_board[int_i][int_j];
            ttint_board[int_i][int_j] = int_tmp;
        }
    }
}

int isWinner(int ttint_board[N][N])
{
    int int_coin;   // the color of the coins
    int int_winner; // -1 if no player win
    int int_i;      // iteration variable
    int int_j;      // iteration variable
    int int_k;      // iteration variable
    int int_numberOfCoins;
    int int_emptyCase; // 0 if there is no empty case

    int_winner = -1;
    int_i = 0;
    int_emptyCase = 0;

    while ((int_i < N) && (int_winner == -1))
    {
        int_j = 0;
        while ((int_j < N) && (int_winner == -1))
        {
            // if the case is not empty
            if (ttint_board[int_i][int_j] != -1)
            {
                int_coin = ttint_board[int_i][int_j];

                // right
                if (int_j + 3 < N)
                {
                    // we have 1 coin
                    int_numberOfCoins = 1;

                    // if there is 3 others coins next, it's won
                    for (int_k = 1; int_k < 4; int_k++)
                    {
                        if (ttint_board[int_i][int_j + int_k] == int_coin)
                        {
                            int_numberOfCoins++;
                        }
                    }
                    // puissance 4 !
                    if (int_numberOfCoins == 4)
                    {
                        int_winner = int_coin;
                    }
                }

                // bottom
                if (int_i + 3 < N)
                {
                    // we have 1 coin
                    int_numberOfCoins = 1;

                    // if there is 3 others coins next, it's won
                    for (int_k = 1; int_k < 4; int_k++)
                    {
                        if (ttint_board[int_i + int_k][int_j] == int_coin)
                        {
                            int_numberOfCoins++;
                        }
                    }
                    // puissance 4 !
                    if (int_numberOfCoins == 4)
                    {
                        int_winner = int_coin;
                    }
                }

                // bottom left
                if ((int_j - 3 >= 0) && (int_i + 3 < N))
                {
                    // we have 1 coin
                    int_numberOfCoins = 1;

                    // if there is 3 others coins next, it's won
                    for (int_k = 1; int_k < 4; int_k++)
                    {
                        if (ttint_board[int_i + int_k][int_j - int_k] == int_coin)
                        {
                            int_numberOfCoins++;
                        }
                    }
                    // puissance 4 !
                    if (int_numberOfCoins == 4)
                    {
                        int_winner = int_coin;
                    }
                }

                // bottom right
                if ((int_j + 3 < N) && (int_i + 3 < N))
                {
                    // we have 1 coin
                    int_numberOfCoins = 1;

                    // if there is 3 others coins next, it's won
                    for (int_k = 1; int_k < 4; int_k++)
                    {
                        if (ttint_board[int_i + int_k][int_j + int_k] == int_coin)
                        {
                            int_numberOfCoins++;
                        }
                    }
                    // puissance 4 !
                    if (int_numberOfCoins == 4)
                    {
                        int_winner = int_coin;
                    }
                }
            }
            // there is an empty case
            else
            {
                int_emptyCase = 1;
            }

            int_j++;
        }
        int_i++;
    }

    // there is no empty case
    if (int_emptyCase == 0)
    {
        int_winner = 2;
    }

    return (int_winner);
}

void playGame(int int_classic)
{
    int int_currentPlayer;
    char str_player1Name[TABLE_LENGTH];
    char str_player2Name[TABLE_LENGTH];
    int int_choosenColumn;
    int ttint_board[N][N];
    int int_winner;
    int int_numberOfRotatonRemainingPlayer1;
    int int_numberOfRotatonRemainingPlayer2;

    int int_error;

    // first player
    int_currentPlayer = rand() % 2;

    // Ask the name of the two players
    printf("Nom du joueur 1 :\n");
    inputStringStatic(str_player1Name);
    printf("Nom du joueur 2 :\n");
    inputStringStatic(str_player2Name);

    // if rotate game
    if (int_classic == 0)
    {
        int_numberOfRotatonRemainingPlayer1 = int_numberOfRotatonRemainingPlayer2 = inputInteger("Avec combien de rotations voulez-vous jouer ?");
    }

    // init the board
    init(ttint_board);

    do
    {
        printBoardGame(ttint_board, str_player1Name, str_player2Name, int_currentPlayer);
        // ask a column to play and play it if no error is occur
        do
        {
            int_choosenColumn = inputInteger("Dans quel colonne voulez-vous jouez ?\n");
            int_error = play(ttint_board, int_currentPlayer, int_choosenColumn, str_player1Name, str_player2Name);
        } while (int_error == -1);

        // determine if we have a winner
        int_winner = isWinner(ttint_board);

        // if there is no winner
        if (int_winner == -1)
        {
            // if rotate game
            if (int_classic == 0)
            {
                if ((int_numberOfRotatonRemainingPlayer1 != 0) && (int_currentPlayer == 0))
                {
                    printf("Il vous reste %d rotation(s).\n", int_numberOfRotatonRemainingPlayer1);
                    if (inputInteger("Voulez-vous effectuer une rotation ?\n(Oui = 1)\n") == 1)
                    {
                        int_numberOfRotatonRemainingPlayer1--;
                        rotate(ttint_board);
                        gravity(ttint_board, str_player1Name, str_player2Name, int_currentPlayer);
                        int_winner = isWinner(ttint_board);
                    }
                }
                else if ((int_numberOfRotatonRemainingPlayer2 != 0) && (int_currentPlayer == 1))
                {
                    printf("Il vous reste %d rotation(s).\n", int_numberOfRotatonRemainingPlayer2);
                    if (inputInteger("Voulez-vous effectuer une rotation ?\n(Oui = 1)\n") == 1)
                    {
                        int_numberOfRotatonRemainingPlayer2--;
                        rotate(ttint_board);
                        gravity(ttint_board, str_player1Name, str_player2Name, int_currentPlayer);
                        int_winner = isWinner(ttint_board);
                    }
                }
                else
                {
                    printf("Vous n'avez plus de rotation.\n");
                }
            }

            // change player
            if (int_currentPlayer == 0)
            {
                int_currentPlayer = 1;
            }
            else
            {
                int_currentPlayer = 0;
            }
        }

    } while (int_winner == -1);

    // print the winner
    if (int_winner == 0)
    {
        printf("Puissance 4 : %s a gagné la partie !\n\n", str_player1Name);
    }
    else if (int_winner == 1)
    {
        printf("Puissance 4 : %s a gagné la partie !\n\n", str_player2Name);
    }
    else
    {
        printf("Égalité ! La partie est terminée.\n\n");
    }
}

int printMenuPuissance4()
{
    int int_selector;
    int int_error;

    // print the menu
    printf("Bienvenue dans le puissance 4 !\n\n");
    printf("Choisir une option :\n");
    printf("1 -- Puissance 4 - Mode classique\n");
    printf("2 -- Puissance 4 - Mode rotatif\n");
    printf("3 -- Quittez\n");
    printf("\n");

    // ask a number and verify if this one isn't out of range
    do
    {
        int_error = 0;
        int_selector = inputInteger("Merci de renseigner votre choix :");
        if ((int_selector < 1) || (int_selector > 3))
        {
            fprintf(stderr, "Merci de renseigner un entier compris dans les choix du menu\n");
            int_error = -1;
        }
    } while (int_error == -1);

    printf("\n");

    // use the function with the choice of the user
    switch (int_selector)
    {
    // reverse the table and print it
    case 1:
        playGame(1);
        return (1);
        break;

    // sum the elements of the table
    case 2:
        playGame(0);
        return (1);
        break;

    case 3:
        return (0);

    default:
        fprintf(stderr, "Une erreur inconnue s'est produite. Fin du programme.");
        exit(-1);
        break;
    }
}