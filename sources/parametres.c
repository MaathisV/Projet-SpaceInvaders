#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/parametres.h"
#include "../headers/menus.h"
#include "../headers/terminal.h"


void Fct_Parametres(int option, int tab_parametres[])
{
    switch(option)
    {
        case 0:
            ;
            break;
        case 1: printw("Règles");
            break;
        case 2:

            break;
        case 3: printw("Scores");
            break;
        case 4: 
            break;
        case 5:
            ChoixMenuPrincipal(tab_parametres[0], tab_parametres[1]);
            break;
        default:
            break;
    }
}


//"Changer les couleurs", "Activer/Désactiver les effets sonores", "Mettre à jour la taille du terminal","Réinitialiser les scores", "Rentrer un mot de passe", "Retour