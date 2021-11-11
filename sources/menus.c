#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/menus.h"



extern int tab_parametres[50];

int ChoixMenuPrincipal()
{
    char titre[] = {"SPACE INVADERS"};
    char *menuPr_liste[5] = {"Jouer", "Règles", "Paramètres", "Scores", "Quitter"};
    int long_titre = strlen(titre);
    char info[] = "Flèches pour sélectionner || Entrée pour valider";
    int long_info = strlen(info);
    int select = 0; //Option du menuPr selectionnée (mais non validée)
    int action; //recupère la touche pressée

        //Création de la zone du menuPr, avec bordure
    WINDOW *menuPr = newwin(9, long_info, (tab_parametres[0] / 3), (tab_parametres[1] / 2) - (long_info / 2));
    box(menuPr, 0, 0);
    keypad(menuPr, true);
    mvprintw(0, (tab_parametres[1] / 2) - (long_titre / 2), titre);  //Affichage du titre du jeu
    mvprintw(tab_parametres[0] / 3 + 9, (tab_parametres[1] / 2) - long_info / 2, info);
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




int ChoixMenuParametres()
{
    char titre[] = {"PARAMèTRES"};
    char *menuPa_liste[6] = {"Changer les couleurs", "Activer/Désactiver les effets sonores", "Mettre à jour la taille du terminal", "Rentrer un mot de passe", "Réinitialiser les scores", "Retour"};
    int long_titre = strlen(titre);
    char info[] = "Flèches pour sélectionner || Entrée pour valider";
    int long_info = strlen(info);
    int select = 0; //Option du menuPr selectionnée (mais non validée)
    int action; //recupère la touche pressée

        //Création de la zone du menuPr, avec bordure
    WINDOW *menuPa = newwin(9, long_info, (tab_parametres[0] / 3), (tab_parametres[1] / 2) - (long_info / 2));
    box(menuPa, 0, 0);
    keypad(menuPa, true);
    mvprintw(0, (tab_parametres[1] / 2) - (long_titre / 2), titre);  //Affichage du titre du jeu
    mvprintw(tab_parametres[0] / 3 + 9, (tab_parametres[1] / 2) - long_info / 2, info);
    refresh();
    
    
    while(1)
    {
        for (int i=0; i < 6; i++)   //Affichage du menuPr avec la ligne
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
                return select;  //Retourne le choix validé par l'utilisateur
                break;
        }
    }
}