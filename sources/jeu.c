#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "../headers/terminal.h"
#include "../headers/jeu.h"



int Jouer()
{
    int x_vaisseau=0; //abscisse vaisseau
    int clavier; //action clavier utilisateur
    int x_maxter, y_maxter; //dimensions du terminal
    char vaisseau[] = "<[°]>";
    int taille_vaisseau = strlen(vaisseau);
    
    getmaxyx(stdscr, y_maxter, x_maxter);
 
    
    while(1)
    {
        clavier = nb_getch();

        mvprintw(0, x_vaisseau, vaisseau);  //affichage du vaisseau


        // Modification des données du jeu et entrees utilisateur
        switch (clavier)
        {
        case 'q':
            //mvprintw(0, x_vaisseau-1, ".....");
            x_vaisseau--;
            if (x_vaisseau == -1)
                x_vaisseau = 0;
            break;
        case 'd':
            //mvprintw(0, x_vaisseau+3, ".....");
            x_vaisseau++;
            if (x_vaisseau > x_maxter)
                x_vaisseau = x_maxter;
            break;
        case 'p':
            printw("fin du jeu");
            system("clear");
            break;
        }

        mvprintw(0, x_vaisseau-1, " ");
        mvprintw(0, x_vaisseau + taille_vaisseau, " ");

        refresh();
        sleep(0.01);
    }
}
