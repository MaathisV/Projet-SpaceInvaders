#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "../headers/jeu.h"
#include "../headers/terminal.h"


/*FONCTION Jouer() : Démarre le jeu
Entrées : néant
Sorties : néant*/
int Jouer()
{
    char nom;

    system("clear");
    mvprintw(0, (COLS / 2) - (19 / 2), "Saisissez votre nom");
    move(3,(COLS/2));
    scanw("%c",&nom);
    system("clear");
    
    DeplacementVaisseau();

}



int DeplacementVaisseau()
{
    int x_vaisseau=0; //abscisse vaisseau
    int clavier='!'; //action clavier utilisateur

    //noecho();   //n'affiche pas les entrées sur le terminal

    printw("<|>");  //Affichage du vaisseau
    refresh();

    clavier = nb_getch();
    
    while(clavier!='p')
    {
        // Modification des données du jeu et entrees utilisateur
        if (clavier==KEY_LEFT)
        {
            printw("gauche");
            clavier = nb_getch();
        }
        else if (clavier=='d')
        {
            printw("gauche");
            clavier = nb_getch();
        }

        else if (clavier=='p')
        {
            printw("fin du jeu");
            system("clear");
        }

        refresh();
        sleep(0.01);
    }

    clavier = nb_getch();
}
