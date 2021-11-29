#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
//#include <math.h>
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
    int compteur = 0;   //Compte le nombre d'itérations de la boucle de jeu
    int i=2;    //
    int score=0;
    //double long_sc = 8 + log(score) + 1;
    int etat;


        //Définition de la fenêtre de jeu
    WINDOW *jeu = newwin(tab_parametres[0] - 3, tab_parametres[1], 2, 0);
    box(jeu, 0, 0);
    nodelay(jeu, TRUE);

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

        //Initialisation de l'emplacement du vaisseau
    element[0].x = 1;
    element[0].y = tab_parametres[0] - 5;
    element[0].init = 1;
 
    element[1].init = 1;    //Boss (non implémenter)


    while (vie != 0)
    {
        compteur++;
        
        clavier = nb_wgetch(jeu);   //Récupère la saisie clavier dans la fenêtre de jeu
        //clavier = nb_getch

        GestionEff(jeu, element, compteur, i);  //efface les éléments déplacés de la boucle precédente

        if (clavier == 32) //la touche espace est pressée
            Pause();

        GestionMvElem(clavier, element, compteur, i);
        GestionAff(jeu, element, compteur, i);

        wrefresh(jeu);

        GestionCollision(vie);
        MajAffInterface(vie, score, etat);//Initialisation de l'interface

        if (((compteur%100) == 0) && (i<3))
            i++;
        else /*if (i <! 50)*/
            i = 2;

        usleep(10000);
    }
}



void MajAffInterface(int vie, int score, int etat)
{
    mvprintw(0,0, "Vie(s) : %d", vie);
    mvprintw(0,tab_parametres[1] - 12, "Score : %d", score);
    mvprintw(tab_parametres[0], 0, "Bonus");
    mvprintw(tab_parametres[0] - 1, (tab_parametres[1] / 2) - 4, "DISARMED");
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



void initElem(data element[50], int i)
{
    if (element[i].init == 0)
    {
        element[i].y = 0;
        element[i].type = Tirage();
    if ((element[i].type == 3) || (element[i].type == 4))
        element[i].x = rand()%(tab_parametres[1] - 5 - 2) + 1;
    if ((element[i].type == 2) || (element[i].type == 1))
        element[i].x = rand()%(tab_parametres[1] - 1 - 2) + 1;
    element[i].init = 1;
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



void GestionMvElem(int clavier, data element[50], int compteur, int i)
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
            if (element[0].x > tab_parametres[1] - 1 - 6)
                element[0].x = tab_parametres[1] - 1 - 6;
            break;
    }

    if ((compteur%100) == 0)
    {
        initElem(element, i);
        if (element[i].y > (tab_parametres[0] - 6))
            element[i].init = 0;
        else
            element[i].y++;   
        
    }
}



void GestionAff(WINDOW *jeu, data element[], int compteur, int i)
{
    char vaisseau[] = "<[°]>", pilule[] = "OOOOO", ennemi[] = "XXXXX", malus[] = "m", bonus[] = "b";


    mvwprintw(jeu, element[0].y, element[0].x, vaisseau);  //affichage du vaisseau


    if ((compteur%100) == 0)
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
                mvwprintw(jeu, element[3].y, element[i].x, bonus);
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



void GestionEff(WINDOW *jeu, data element[50], int compteur, int i)
{
        //Effacemement du vaisseau
    mvwprintw(jeu, element[0].y, element[0].x, " ");
    mvwprintw(jeu, element[0].y, element[0].x + 5, " ");  

    if ((compteur%100) == 0)
    {    
        if ((element[i].type == 1) || (element[i].type == 2))
            mvwprintw(jeu, element[i].y, element[i].x, " ");
        else if ((element[i].type == 3) || (element[i].type == 4))
            mvwprintw(jeu, element[i].y, element[i].x, "     ");
    }
}



int GestionCollision(int vie)
{
    
}