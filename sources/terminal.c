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
}