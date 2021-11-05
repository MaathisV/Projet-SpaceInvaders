#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "../headers/terminal.h"
#include "../headers/jeu.h"



int Jouer(int tab_parametres[])
{
    /*int x_vaisseau=0; //abscisse vaisseau
    int clavier; //action clavier utilisateur
    char vaisseau[] = "<[°]>";
    int taille_vaisseau = strlen(vaisseau);*/
    
    printw("je suis le jeu");
    WINDOW *jeu = newwin(4, 0, tab_parametres[0] - 1, tab_parametres[1]);
    box(jeu, 0, 1);
    refresh();
    wrefresh(jeu);
    refresh();
}
 
    /*while(1)
    {
        clavier = nb_wgetch(jeu);

        mvwprintw(jeu, 0, x_vaisseau, vaisseau);  //affichage du vaisseau


        // Modification des données du jeu et entrees utilisateur
        switch (clavier)
        {
        case 'q':
            x_vaisseau--;
            if (x_vaisseau == -1)
                x_vaisseau = 0;
            break;
        case 'd':
            x_vaisseau++;
            if (x_vaisseau > tab_parametres[1])
                x_vaisseau = tab_parametres[1];
            break;
        case 'p':
            wprintw(jeu, "fin du jeu");
            system("clear");
            break;
        }

        mvwprintw(jeu, 0, x_vaisseau-1, " ");
        mvwprintw(jeu, 0, x_vaisseau + taille_vaisseau, " ");

        wrefresh(jeu);
        refresh();
        wrefresh(jeu);
        sleep(0.01);
    }
}*/
