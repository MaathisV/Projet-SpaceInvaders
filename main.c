/*      PROJET SPACE INVADERS
    BERGEREAU Paul et VADEZ Mathis
Développement d'un jeu type Space Invaders en language C et directement dans le terminal
Pour executer le programme dans la console repl.it
gcc -o projet main.c -lncurses
./projet*/


#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "sources/terminal.c"   //Fonctions du terminal (couleurs, saisies, taille)
#include "sources/jeu.c"    //Fonction du jeu (gameover, parametres de la partie, boucle de jeu, compteur de démarrage)
#include "sources/menus.c"  //Fonctions qui affiche et gère la selection des différents menus (principal et paramètres)
#include "sources/parametres.c" //Fonctions  de paramètrage du programme (changement de couleurs, changement de design, maj taille terminal, réinitialisation des scores)
#include "sources/scores.c" //Fonctions d'enregistrement, récupération, affichage et tri des scores
//Les .h du dossier headers contiennent les prototypes des fonctions ci-dessus



int tab_parametres[17]; //Tableau contenant les paramètres du jeu (0-1 : dimensions y et x du terminal, 2-15 : paires de couleurs des éléments du programme, 16 : effets sonores on/off (pas implémenté pour le moment))
score joueur[11];   //Tableau contenant le nom des joueurs et leurs meilleurs scores
char design_elem[7][10] = {"Interface", "<[°]>", "<X|-|X>", "XXXXX", "OOOOO", "m", "b"};  //Elements du jeu : joueur, boss, ennemi, pilule, malus et bonus. Interface sert à montrer la couleur de l'interface dans les paramètres (n'est pas utilisé en jeu)


int main()
{
    startscr();
    int option; //choix du menu paramètres
    int choix = -1;

    InitTabs(); //Initialise les différents tableaux de paramètres et de scores

    
    while (choix != 4)
    {
        wattron(stdscr,COLOR_PAIR(1));   
        choix = ChoixMenuPrincipal();
            //Affichage du menu et aiguillage
        switch(choix)
        {
            case 0: //Jouer à Space Invaders
                clear();
                Jouer();
                break;
            case 1: //Règles et Lore du jeu
                clear();
                Regles();
                break;
            case 2: //Menu des paramètres
                clear();
                option = ChoixMenuParametres();
                Fct_Parametres(option);
                break;
            case 3: //Tableau des scores
                clear();
                AffScore();
                break;
            case 4: //Quitter le jeu
                break;
        }
    }
        endwin();

        return 0;
}