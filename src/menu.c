/*!
\file menu.c
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief Print the main menu and sub menu
*/

#include "menu.h"

void printMainMenu()
{
    int int_continue;

    // print the menu
    printf("Welcome to the connect4 game !\n");
    printf("\n");

    int_continue = 1;
    while (int_continue == 1)
    {
        int_continue = printMenuPuissance4();
    }
    printf("Merci d'avoit joué !\n");
}