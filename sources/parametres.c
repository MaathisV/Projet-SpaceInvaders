#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/menus.h"
#include "../headers/terminal.h"



extern int tab_parametres[50];

void Fct_Parametres(int option)
{
    switch(option)
    {
        case 0:
            printw("couleurs");
            clear();
            break;
        case 1:
            clear();
            printw("son");
            break;
        case 2:
            clear();
            dim_terminal();
            return;
            break;
        case 3:
            clear();
            printw("Scores effacé");
            int c = getch();
            return;
            break;
        case 4:
            clear();
            break;
    }
}


//"Changer les couleurs", "Activer/Désactiver les effets sonores", "Mettre à jour la taille du terminal","Réinitialiser les scores", "Retour