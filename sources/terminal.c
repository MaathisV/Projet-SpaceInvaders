#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../headers/terminal.h"


void color(int cT,int cF)
{
    init_pair(1,cT,cF);
    attron(COLOR_PAIR(1));
}


char nb_getch()
{
    timeout(0);
    return getch();
}


char b_getch()
{
    timeout(-1);
    return getch();
}


void startscr()
{
    initscr();
    start_color();
    cbreak();
    curs_set(FALSE);
    noecho();
}


int dim_terminal(int tab_parametres[])
{
    getmaxyx(stdscr, tab_parametres[0], tab_parametres[1]);
    mvprintw(tab_parametres[0]/3 + 12, 0, "Les dimensions du terminal ont été mises à jour\nLe terminal fait maintenant %d de haut et %d de large\n\tAppuyer pour continuer", tab_parametres[0], tab_parametres[1]);   //Affichage des dimensions du terminal
    int pause = getch();    //Pause pour laisser afficher l'information
    clear();
}