#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/menus.h"



int ChoixMenuPrincipal(int y_maxter, int x_maxter)
{
    char titre[] = {"SPACE INVADERS"};
    char *menuPr_liste[5] = {"Jouer", "Règles", "Paramètres", "Scores", "Quitter"};
    int long_titre = strlen(titre);
    char info[] = "Flèches pour sélectionner || Entrée pour valider";
    int long_info = strlen(info);
    int select = 0; //Option du menuPr selectionnée (mais non validée)
    int action; //recupère la touche pressée

        //Création de la zone du menuPr, avec bordure
    WINDOW *menuPr = newwin(9, long_info, (y_maxter / 3), (x_maxter / 2) - (long_info / 2));
    box(menuPr, 0, 0);
    keypad(menuPr, true);
    mvprintw(0, (x_maxter / 2) - (long_titre / 2), titre);  //Affichage du titre du jeu
    mvprintw(y_maxter / 3 + 9, (x_maxter / 2) - long_info / 2, info);
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
                return select;  //Retourne le choix validé par l'utilisateur
                break;
        }
    }
}




int ChoixMenuParametres(int y_maxter, int x_maxter)
{
    char titre[] = {"PARAMèTRES"};
    char *menuPa_liste[5] = {"Changer les couleurs", "Activer/Désactiver les effets sonores", "Mettre à jour la taille du terminal", "Rentrer un mot de passe", "Retour"};
    int long_titre = strlen(titre);
    char info[] = "Flèches pour sélectionner || Entrée pour valider";
    int long_info = strlen(info);
    int select = 0; //Option du menuPr selectionnée (mais non validée)
    int action; //recupère la touche pressée

        //Création de la zone du menuPr, avec bordure
    WINDOW *menuPa = newwin(9, long_info, (y_maxter / 3), (x_maxter / 2) - (long_info / 2));
    box(menuPa, 0, 0);
    keypad(menuPa, true);
    mvprintw(0, (x_maxter / 2) - (long_titre / 2), titre);  //Affichage du titre du jeu
    mvprintw(y_maxter / 3 + 9, (x_maxter / 2) - long_info / 2, info);
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
                if (select == 5)    //Empêche de sortir du nombres de valeurs définies
                    select = 4;
                break;
            case 10:    //Si Entrée est pressée
                return select;  //Retourne le choix validé par l'utilisateur
                break;
        }
    }
}