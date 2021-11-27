#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../headers/terminal.h"
#include "../headers/jeu.h"
#include "../headers/menus.h"


extern int tab_parametres[50];

void Jouer()
{
    data element[50] = {0}; //Définition des données d'un élément (coordonnées et type) avec initialisation à zéro
    int vie;    //nb de vie du joueur
    int clavier;    //Saisie utilisateur
    int pause;  //détermine l'état de la pause
    int compteur = 0;   //Compte le nombre de


        //Définition de la fenêtre de jeu
    WINDOW *jeu = newwin(tab_parametres[0] - 3, tab_parametres[1], 2, 0);
    box(jeu, 0, 0);
    nodelay(jeu, TRUE);
    refresh();

        //Affichage du compteur de démarrage
    mvprintw(0, 0, "%d", 3);
    refresh();
    sleep(1);
    mvprintw(0, 0, "%d", 2);
    refresh();
    sleep(1);
    mvprintw(0, 0, "%d", 1);
    refresh();
    sleep(1);
    mvprintw(0, 0, "%d", 0);
    refresh();
    sleep(1);
    vie = 5;
    mvprintw(0, 0, " ");
    refresh();

    while (vie != 0)
    {
        compteur++;
        
        clavier = nb_wgetch(jeu);   //Récupère la saisie clavier dans la fenêtre de jeu
        //clavier = nb_getch

        GestionEff(jeu, element, compteur);  //efface les éléments déplacés de la boucle precédente

        if (clavier == 32) //la touche espace est pressée
            Pause();
        for (int i=2; (i<50) && ((compteur%20000) == 0); i++)
            element[i].type = Tirage();

        GestionMvElem(clavier, element, compteur);
        GestionAff(jeu, element, compteur);

        wrefresh(jeu);

        //GestionCollision(vie);

        sleep(0.01);
    }
}



void Pause()
{
    int compteur_pause=0;   //Permet de confirmer la sortie du jeu
    mvprintw(0, (tab_parametres[1] / 2) - (5/2), "PAUSE");
    while (1)
    {
        int saisie_pause  = b_getch();  //stoppe l'execution tout en recuperant les saisies clavier
        switch (saisie_pause)
        {
            case 32:   //on stoppe la pause
                mvprintw(0, (tab_parametres[1] / 2) - (5/2), "     ");
                break;
                //ajouter une ligne pour sortir de la boucle while
            case 27:    //on demande a quitter le jeu (avec la touche esc)
                compteur_pause++;
                if (compteur_pause == 2)    //la demande est confirmée on quitte le jeu
                {
                    clear();
                    ChoixMenuPrincipal();
                }    
                break;
        }
    }
}



void GestionMvElem(int clavier, data element[50], int compteur)
{
        // Modification de la position du vaisseau en fonction des entrees clavier
    switch (clavier)
    {
        case 'q':
            element[0].x--;
            if (element[0].x == 0)
                element[0].x = 1;
            break;
        case 'd':
            element[0].x++;
            if (element[0].x > tab_parametres[1] - 1 - 5)
                element[0].x = tab_parametres[1] - 1 - 5;
            break;
    }

        //Positionnement aleatoire de l'abscisse d'un element (pilules, ennemis, bonus, malus) + descente (non fonctionnel)
    for (int i=2; (((compteur%20000) == 0) && (i<50)); i= i+ 1)    //toutes les deux secondes
    {
        element[i].x = 1;
        element[i].y++;
        /*if (element[i].y < (5)) //limite la descente (non fonctionnel)
            element[i].y++;

        if ((element[i].type == 1) || (element[i].type == 2))
            element[i].x = rand()%((tab_parametres[1] - 2) - 1) + 1;
        else if ((element[i].type == 3) || (element[i].type == 4))
            element[i].x = rand()%((tab_parametres[1] - 2) - 5) + 1;
        */

    }

}



void GestionAff(WINDOW *jeu, data element[], int compteur)
{
    char vaisseau[] = "<[°]>", pilule[] = "OOOOO", ennemi[] = "XXXXX", malus[] = "m", bonus[] = "b";


    mvwprintw(jeu, element[0].y, element[0].x, vaisseau);  //affichage du vaisseau


    for (int i=2; ((i<50) && ((compteur%20000) == 0)); i=i+2)
    {
        switch (element[i].type)    //Affichage des autres element du jeu
        {
            case 0:
                //BOSS (a implenter)
                break;
            case 1:
                wattron(jeu, A_REVERSE);
                mvwprintw(jeu, element[i].y, element[i].x, malus);
                wattroff(jeu, A_REVERSE);
                break;
            case 2:
                wattron(jeu, A_REVERSE);
                mvwprintw(jeu, element[i].y, element[i].x, bonus);
                wattroff(jeu, A_REVERSE);
                break;
            case 3:
                mvwprintw(jeu, element[i].y, element[i].x, pilule);
                break;
            case 4:
                mvwprintw(jeu, element[i].y, element[i].x, ennemi);
                break;
        }
    }
}



void GestionEff(WINDOW *jeu, data element[50], int compteur)
{
        //Effacemement du vaisseau
    mvwprintw(jeu, element[0].y, element[0].x, " ");
    mvwprintw(jeu, element[0].y, element[0].x + 5, " ");  

        //Effacement des elements
    for (int j=2; j<50; j++) 
    {
        if ((element[j].type == 1) || (element[j].type == 2))
            mvwprintw(jeu, element[j].y, element[j].x, " ");
        else if ((element[j].type == 3) || (element[j].type == 4))
            mvwprintw(jeu, element[j].y, element[j].x, "     ");
    }
}



int Tirage()
{
    int element;    //Désigne l'élément à apparaitre tiré au sort
    int tirage; //Valeur aléatoire qu décide du prochain element
    int nb_bonus, nb_malus, nb_pilules;  //Compte le nombre d'élements respectifs apparus consécutivement pour restreindre l'aléatoire

    tirage = rand()%20;

    if (tirage == 0)
        {
            element = 1;    //Un malus apparait
            //nb_malus++;
            nb_bonus = 0;
            nb_pilules = 0;
        }
        else if (tirage == 1 && nb_bonus <= 3)
        {
            element = 2; //un bonus apparait
            nb_bonus++;
            nb_pilules = 0;
        }
        else if ((tirage >= 2 && tirage <= 4) && nb_pilules <= 4)
        {
            element = 3;    //une pilule apparait
            nb_pilules++;
            nb_bonus = 0;
        }
        else
        {
            element = 4;    //un ennemi apparait
            nb_pilules = 0;
            nb_malus = 0;
            nb_bonus = 0;        
        }
    return element;
}