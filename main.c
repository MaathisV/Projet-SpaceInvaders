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
#include "sources/parametres.c"





int main()
{
    startscr();
    int tab_parametres[50]; //Tableau contenant les paramètres du jeu
    int option; //choix du menu paramètres
    int choix = -1;


            //Récupération des dimensions du terminal
    dim_terminal(tab_parametres);
    
    //while (choix == -1)
    //{   
        choix = ChoixMenuPrincipal(tab_parametres);
            //Affichage du menu et aiguillage
        switch(choix)
        {
            case 0:
                clear();
                Jouer(tab_parametres);
                break;
            case 1: printw("Règles");
                break;
            case 2:
                clear();
                option = ChoixMenuParametres(tab_parametres);
                Fct_Parametres(option, tab_parametres);
                break;
            case 3: printw("Scores");
                break;
            case 4: printw("Quitter");
                break;
            default:
                break;
        }
    //}
        endwin();

        return 0;
}