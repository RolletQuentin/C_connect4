/*!
\file main.c
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief Vectors and matrix manipulations
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "usefull_functions.h"
#include "puissance4.h"

/*!
\fn int main(int argc, char **argv)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 15/11/2022
\brief main function - print a menu to use functions
\param argc number of arguments
\param **argv values of arguments
\return 0 if all is good
*/
int main(int argc, char **argv)
{
    // print the main menu
    printMainMenu();

    // because all is good
    return (0);
}