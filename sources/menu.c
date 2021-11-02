#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/menu.h"


int ChoixMenu()
{
    char titre[] = "SPACE INVADERS";
    int long_titre = strlen(titre);
    char aff_menu[] = {"Jouer", "Règles", "Paramètres", "Scores", "Quitter", "\0"};
    char info[] = "↑ ↓ pour sélectionner   Entrée pour valider";
    int long_info = strlen(info);
    int select = 0;
    int action; //


    WINDOW *menu = newwin(6, long_info, COLS / 2, LINES / 2);
    keypad(menu, true);
    
        //Affichage du titre
    while(1) {  //Boucle pour empêcher l'arrêt du programme si le terminnal est redimensionné
        mvprintw(0, (COLS / 2) - (long_titre / 2), titre);
        box(menu, 0, 0);
        mvwprintw(menu, 1, 1, info);
        wprintw(menu, aff_menu);
        refresh();
        wrefresh(menu);

        for (int i=0; i < 5; i++)
        {
            if (i == select)
            {
                wattron(menu, A_REVERSE);
                mvwprintw(menu, i+1, 1, "%s", aff_menu[i]);
                wattroff(menu, A_REVERSE);
            }
        }
        action = wgetch(menu);

            //Aiguillage du menu
        switch(action)
        {
            case KEY_UP:
                select--;
                break;
            case KEY_DOWN:
                select++;
                break;
            default:
                break;
        }
        if (action == 10)   //Si la touche Entrée est pressée : la saisie est validée
            //return select;
            break;

        if(getch() != 410)  //410 correspond à la valeur retournée lorsque le terminal est redimensionné
            break;
    }

    return select;    
}
