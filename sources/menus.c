#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/menus.h"



int ChoixMenuPrincipal(int y_maxter, int x_maxter)
{
    char titre[] = {"SPACE INVADERS"};
    char *menu_liste[5] = {"Jouer", "Règles", "Paramètres", "Scores", "Quitter"};
    int long_titre = strlen(titre);
    char info[] = "Flèches pour sélectionner || Entrée pour valider";
    int long_info = strlen(info);
    int select = 0; //Option du menu selectionnée (mais non validée)
    int action; //recupère la touche pressée

        //Récuperation des dimensions du terminal
    getmaxyx(stdscr,  y_maxter, x_maxter);
        //Création de la zone du menu, avec bordure
    WINDOW *menu = newwin(9, long_info, (y_maxter / 3), (x_maxter / 2) - (long_info / 2));
    box(menu, 0, 0);
    keypad(menu, true);
    mvprintw(0, (x_maxter / 2) - (long_titre / 2), titre);  //Affichage du titre du jeu
    mvprintw(y_maxter / 3 + 9, (x_maxter / 2) - long_info / 2, info);
    refresh();
    
    
    while(1)
    {
        for (int i=0; i < 5; i++)   //Affichage du menu avec la ligne
        {
            if (i == select)
            {
                wattron(menu, A_REVERSE);
                mvwprintw(menu, i+1, 1, menu_liste[i]);
                wattroff(menu, A_REVERSE);
            }
            else
            {
                mvwprintw(menu, i+1, 1, menu_liste[i]);
            }
        }

        action = wgetch(menu);  //récupère l'action clavier

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