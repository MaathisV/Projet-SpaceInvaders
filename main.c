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
#include "sources/menu.c"





int main()
{
    startscr();

        //Affichage du menu et aiguillage
    switch(ChoixMenu())
    {
        case 1: Jouer();
        break;
        case 2: printw("Règles");
        break;
        case 3: printw("Paramètres");
        break;
        case 4: printw("Scores");
        break;
        case 5: printw("Quitter");
    }

    endwin();

    return 0;
}