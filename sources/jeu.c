#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../headers/terminal.h"
#include "../headers/jeu.h"
#include "../headers/menus.h"



void Jouer(int tab_parametres[])
{
    int pos_elem[50] = {15};   //Contient la position de tout les elements apparaissant sur la fenêtre de jeu (initialisé à un pour la première valeur et 0 pour toutes les autres)
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

        GestionEff(jeu, pos_elem, tab_parametres);  //efface les éléments déplacés de la boucle precédente

        if (clavier == 32) //la touche espace est pressée
            Pause();
        GestionMvElem(clavier, pos_elem, compteur, tab_parametres);

        GestionAff(jeu, pos_elem, compteur, tab_parametres);

        wrefresh(jeu);

        sleep(0.01);
    }
}



void GestionMvElem(int clavier, int pos_elem[], int compteur, int tab_parametres[])
{
    int taille_vaisseau=5;

        // Modification de la position du vaisseau en fonction des entrees clavier
    switch (clavier)
    {
        case 'q':
            pos_elem[1]--;
            if (pos_elem[1] == 0)
                pos_elem[1] = 1;
            break;
        case 'd':
            pos_elem[1]++;
            if (pos_elem[1] > tab_parametres[1] - 1 - taille_vaisseau)
                pos_elem[1] = tab_parametres[1] - 1 - taille_vaisseau;
            break;
    }

        //Positionnement aleatoire de l'abscisse d'un element (pilules, ennemis, bonus, malus) + descente
    for (int i=2; i<12; i=i+2)
    {
        if (compteur%200==0)    //2s sont passées -> action validée
        {
            pos_elem[i+1] = rand()%(tab_parametres[1] - 1 - 1) + 1;
            pos_elem[i]++;
        }
    }
}



void Pause(int tab_parametres[])
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
                    ChoixMenuPrincipal(tab_parametres);
                }    
                break;
        }
    }
}



void GestionAff(WINDOW *jeu, int pos_elem[], int compteur, int tab_parametres[])
{
    char vaisseau[] = "<[°]>", pilule[] = "OOOOO", ennemi[] = "XXXXX", malus[] = "m", bonus[] = "b";
    int nb_bonus, nb_malus, nb_pilules;  //Compte le nombre d'élements respectifs apparus consécutivement pour restreindre l'aléatoire
    int tirage; //nombre aléatoire qui détermine le future élément à apparaître


    mvwprintw(jeu, tab_parametres[0] - 10, pos_elem[1], vaisseau);  //affichage du vaisseau

    
    //Tirage aléatoire du prochain element a apparaitre
    for (int i=2; i<13; i=i+2)
    {
        if (compteur%200==0)    //2s sont passé on valide l'apparition
        {
            tirage = rand()%20;
            if (tirage == 0)
            {
                mvwprintw(jeu, pos_elem[i], pos_elem[i+1], malus);
                //nb_malus++;
                nb_bonus = 0;
                nb_pilules = 0;
            }
            else if (tirage == 1 && nb_bonus <= 3)
            {
                mvwprintw(jeu, pos_elem[i], pos_elem[i+1], bonus);
                nb_bonus++;
                nb_pilules = 0;
            }
            else if ((tirage >= 2 && tirage <= 4) && nb_pilules <= 4)
            {
                mvwprintw(jeu, pos_elem[i], pos_elem[i+1], pilule);
                nb_pilules++;
                nb_bonus = 0;
            }
            else
            {
                mvwprintw(jeu, pos_elem[i], pos_elem[i+1], ennemi);
                nb_pilules = 0;
                nb_malus = 0;
                nb_bonus = 0;        
            }
        }
    }
}



void GestionEff(WINDOW *jeu, int pos_elem[], int tab_parametres[])
{
    mvwprintw(jeu, tab_parametres[0] - 10, pos_elem[1], " ");
    mvwprintw(jeu, tab_parametres[0] - 10, pos_elem[1]+5, " ");  
}