/*      PROJET SPACE INVADERS
    BERGEREAU Paul et VADEZ Mathis
Développement d'un jeu type Space Invaders en language C et directement dans le terminal
Pour executer le programme dans la console repl.it
gcc -o projet main.c -lncurses
./projet*/


#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "sources/terminal.c"
#include "sources/jeu.c"
#include "sources/menus.c"





int main()
{
    startscr();
    int parametres[50]; //Tableau contenant les paramètres du jeu


        //Récupération des dimensions du terminal
    getmaxyx(stdscr, parametres[0], parametres[1]);
    printw("%d\n%d", parametres[0], parametres[1]);

        //Affichage du menu et aiguillage
    switch(ChoixMenuPrincipal(parametres[0], parametres[1]))
    {
        case 0:
            clear();
            Jouer();
            break;
        case 1: printw("Règles");
            break;
        case 2: printw("Paramètres");
            break;
        case 3: printw("Scores");
            break;
        case 4: printw("Quitter");
            break;
        default:
            break;
    }

    endwin();

    return 0;
}