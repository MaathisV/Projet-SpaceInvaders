#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/menus.h"



extern int tab_parametres[50];

int ChoixMenuPrincipal()
{
    char titre[12][53] = {"   _____ ____  ___   ____________",
                    "  / ___// __ \\/   | / ____/ ____/",
                    "  \\__ \\/ /_/ / /| |/ /   / __/   ",
                    " ___/ / ____/ ___ / /___/ /___  ", 
                    "/____/_/   /_/  |_\\____/_____/   ",
                                 
"     _____   ___    _____    ____  __________  _____",
"    /  _/ | / / |  / /   |  / __ \\/ ____/ __ \\/ ___/",
"    / //  |/ /| | / / /| | / / / / __/ / /_/ /\\__ \\ ",
"  _/ // /|  / | |/ / ___ |/ /_/ / /___/ _, _/___/ / ",
" /___/_/ |_/  |___/_/  |_/_____/_____/_/ |_|/____/ "};

    char *menuPr_liste[5] = {"Jouer", "Règles", "Paramètres", "Scores", "Quitter"};
    char info[] = "Flèches pour sélectionner || Entrée pour valider";
    int long_info = strlen(info);
    int select = 0; //Option du menuPr selectionnée (mais non validée)
    int action; //recupère la touche pressée
    int posy=0, posx=(tab_parametres[1] / 2)  - (long_info / 2) - 10; //Position du titre

        //Création de la zone du menuPrincipal, avec bordure
    WINDOW *menuPr = newwin(9, long_info, 13, (tab_parametres[1] / 2)  - (long_info / 2));
    wattron(menuPr,COLOR_PAIR(1)); 
    box(menuPr, 0, 0);
    keypad(menuPr, true);

    //wattron(menuPr, COLOR_PAIR(1));

        //Affichage du titre
    for(int i=0;i<12;i++)
    { 
        for(int j=0;j<53;j++)
        {
            mvprintw(posy, posx, "%c",titre[i][j]);
            posx++;
        }
        posx=(tab_parametres[1] / 2)  - (long_info / 2) - 10;
        posy++;
    }
    mvprintw(14 + 9, (tab_parametres[1] / 2) - long_info / 2, info);
    refresh();
    
    
    while(1)
    {
        for (int i=0; i < 5; i++)   //Affichage du menuPr avec la ligne
        {
            if (i == select)
            {
                wattron(menuPr, A_REVERSE);
                mvwprintw(menuPr, i+1, 1, menuPr_liste[i]);
                wattroff(menuPr, A_REVERSE);
            }
            else
            {
                mvwprintw(menuPr, i+1, 1, menuPr_liste[i]);
            }
        }

        action = wgetch(menuPr);  //récupère l'action clavier

        switch(action)
        {
            case KEY_UP:    //Si flèche haut est pressée
                select--;
                if (select == -1)   //Empêche de sortir du nombres de valeurs définies
                    select = 0;
                break;
            case KEY_DOWN:  //Si flèche bas est pressée
                select++;
                if (select == 5)    //Empêche de sortir du nombres de valeurs définies
                    select = 4;
                break;
            case 10:    //Si Entrée est pressée
                //wattroff(menuPr, COLOR_PAIR(1));
                return select;  //Retourne le choix validé par l'utilisateur
                break;
        }
    }
}




int ChoixMenuParametres()
{
    char titre[] = {"PARAMèTRES"};
    char *menuPa_liste[5] = {"Changer les couleurs", "Activer/Désactiver les effets sonores", "Mettre à jour la taille du terminal", "Réinitialiser les scores", "Retour"};
    int long_titre = strlen(titre);
    char info[] = "Flèches pour sélectionner || Entrée pour valider";
    int long_info = strlen(info);
    int select = 0; //Option du menuPr selectionnée (mais non validée)
    int action; //recupère la touche pressée

        //Création de la zone du menuPr, avec bordure
    WINDOW *menuPa = newwin(8, long_info, (tab_parametres[0] / 3), (tab_parametres[1] / 2) - (long_info / 2));
    wattron(menuPa,COLOR_PAIR(1)); 
    box(menuPa, 0, 0);
    keypad(menuPa, true);

    wattron(menuPa, COLOR_PAIR(1));

    mvprintw(0, (tab_parametres[1] / 2) - (long_titre / 2), titre);  //Affichage du nom de la l'affichage
    mvprintw(tab_parametres[0] / 3 + 9, (tab_parametres[1] / 2) - long_info / 2, info);
    refresh();
    
    
    while(1)
    {
        for (int i=0; i < 5; i++)   //Affichage du menuPr avec la ligne
        {
            if (i == select)
            {
                wattron(menuPa, A_REVERSE);
                mvwprintw(menuPa, i+1, 1, menuPa_liste[i]);
                wattroff(menuPa, A_REVERSE);
            }
            else
            {
                mvwprintw(menuPa, i+1, 1, menuPa_liste[i]);
            }
        }

        action = wgetch(menuPa);  //récupère l'action clavier

        switch(action)
        {
            case KEY_UP:    //Si flèche haut est pressée
                select--;
                if (select == -1)   //Empêche de sortir du nombres de valeurs définies
                    select = 0;
                break;
            case KEY_DOWN:  //Si flèche bas est pressée
                select++;
                if (select == 6)    //Empêche de sortir du nombres de valeurs définies
                    select = 5;
                break;
            case 10:    //Si Entrée est pressée
                wattroff(menuPa, COLOR_PAIR(1));
                return select;  //Retourne le choix validé par l'utilisateur
                break;
        }
    }
}