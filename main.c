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



int tab_parametres[17]; //Tableau contenant les paramètres du jeu (0-1 : dimensions y et x du terminal, 2-15 : paires de couleurs des éléments du programme, 16 : effets sonores on/off (pas implémenté pour le moment))
score joueur[11];   //Tableau contenant le nom des joueurs et leurs meilleurs scores
char design_elem[7][10] = {"Interface", "<[°]>", "<XXXXX>", "XXXXX", "OOOOO", "m", "b"};  //Elements du jeu


int main()
{
    startscr();
    int option; //choix du menu paramètres
    int choix = -1;

    InitTabs(); //Initialise les différents tableaux de paramètres et de scores

    
    while (choix != 4)
    {
        wattron(stdscr,COLOR_PAIR(1));   
        choix = ChoixMenuPrincipal();
            //Affichage du menu et aiguillage
        switch(choix)
        {
            case 0: //Jouer à Space Invaders
                clear();
                Jouer();
                break;
            case 1: //Règles et Lore du jeu
                clear();
                Regles();
                break;
            case 2: //Menu des paramètres
                clear();
                option = ChoixMenuParametres();
                Fct_Parametres(option);
                break;
            case 3: //Tableau des scores
                printw("Scores");
                break;
            case 4: //Quitter le jeu
                break;
        }
    }
        endwin();

        return 0;
}