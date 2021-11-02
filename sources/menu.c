#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/menu.h"
#include "../headers/terminal.h"


int ChoixMenu()
{
    keypad(stdscr, true);
    int choix=-1;  //Valeur du choix utilisateur

    // Affichage de l'écran d'accueil et du menu
    while (choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5)
    {
        printw("Bienvenue dans le jeu\n que voulez vous faire\n1 - Jouer\n2 - Règles\n3 - Paramètres\n4 - Scores\n5 - Quitter\n Votre choix :");
        scanw("%d", &choix);
        refresh();
    }
    return choix;
}
