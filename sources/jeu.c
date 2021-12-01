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
    data element[75] = {0}; //Définition des données d'un élément (coordonnées et type) avec initialisation à zéro
    int vie;    //nb de vie du joueur
    int *pointe_vie = &vie;    //Pointe la variable vie
    int effetJoueur=0; //Désigne le malus ou bonus qui affecte le joueur
    int *pointe_effetJoueur = &effetJoueur;  //pointe la variable etat_Affect 
    int clavier;    //Saisie utilisateur
    int pause;  //détermine l'état de la pause
    int compteur = 0;   //Compte le nombre d'itérations de la boucle de jeu
    int i=2;    //
    int score=0;
    //double long_sc = 8 + log(score) + 1;


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

        GestionEff(jeu, element, compteur);  //efface les éléments déplacés de la boucle precédente

        if (clavier == 32) //la touche espace est pressée
            Pause();

        GestionMvElem(clavier, element, compteur, i);
        GestionAff(jeu, element, compteur, i);

        wrefresh(jeu);

        GestionCollision(pointe_vie, pointe_effetJoueur, element, compteur);
        //GestionEffetMalusBonus(effetJoueur)
        MajAffInterface(vie, score, effetJoueur);


        if ((compteur%100) == 0)
            i++;
        else if (i <! 75)
            i = 2;
        

        usleep(10000);
    }
}



void MajAffInterface(int vie, int score, int effetJoueur)
{
    mvprintw(0,0, "Vie(s) : %d", vie);
    mvprintw(0,tab_parametres[1] - 12, "Score : %d", score);
    mvprintw(tab_parametres[0], 0, "Bonus");
    attron(A_DIM);
    mvprintw(tab_parametres[0] - 1, (tab_parametres[1] / 2) - 15, "CANON DESACTIVE");
    attroff(A_DIM);
    switch (effetJoueur)
    {
        case 10:
            attron(A_STANDOUT);
            mvprintw(tab_parametres[0] - 1, 0, "MALUS");
            attroff(A_STANDOUT);
            break;
        case 20:
            attron(A_STANDOUT);
            mvprintw(tab_parametres[0] - 1, 0, "MALUS");
            attroff(A_STANDOUT);
            break;
        default:
            mvprintw(tab_parametres[0] - 1, 0, "        ");
    }

    refresh();
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
                return;
                break;
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



void initElem(data element[75], int i)
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



void GestionMvElem(int clavier, data element[75], int compteur, int i)
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
        for (int j=2; j<75; j++)
        {
            if (element[j].init == 1)
            {
                mvprintw(12, 2, "debug j init mv = %d", j);
                refresh();
                if (element[j].y > (tab_parametres[0] - 6))
                    element[j].init = 0;
                else
                    element[j].y++;   
            }
        }
    }
}



void GestionAff(WINDOW *jeu, data element[], int compteur, int i)
{
    char vaisseau[] = "<[°]>", pilule[] = "OOOOO", ennemi[] = "XXXXX", malus[] = "m", bonus[] = "b";


    mvwprintw(jeu, element[0].y, element[0].x, vaisseau);  //affichage du vaisseau


    if ((compteur%100) == 0)
    {
        for (int j=2; j<75; j++)
        {
            if (element[j].init == 1)
            {
                switch (element[j].type)    //Affichage des autres element du jeu
                {
                    case 0:
                        //BOSS (a implenter)
                        break;
                    case 1:
                        wattron(jeu, A_REVERSE);
                        mvwprintw(jeu, element[j].y, element[j].x, malus);
                        wattroff(jeu, A_REVERSE);
                        break;
                    case 2:
                        wattron(jeu, A_REVERSE);
                        mvwprintw(jeu, element[3].y, element[j].x, bonus);
                        wattroff(jeu, A_REVERSE);
                        break;
                    case 3:
                        mvwprintw(jeu, element[j].y, element[j].x, pilule);
                        break;
                    case 4:
                        mvwprintw(jeu, element[j].y, element[j].x, ennemi);
                        break;
                }
            }
        }
    }
}



void GestionEff(WINDOW *jeu, data element[75], int compteur)
{
        //Effacemement du vaisseau
    mvwprintw(jeu, element[0].y, element[0].x, " ");
    mvwprintw(jeu, element[0].y, element[0].x + 5, " ");  

    if ((compteur%100) == 0)
    {
        for (int j=2; j<75; j++)
        {
            if (element[j].init == 1)
            {
                if ((element[j].type == 1) || (element[j].type == 2))
                    mvwprintw(jeu, element[j].y, element[j].x, " ");
                else if ((element[j].type == 3) || (element[j].type == 4))
                    mvwprintw(jeu, element[j].y, element[j].x, "     ");
            }
        }
    }
}



void GestionCollision(int *pointe_vie, int *pointe_effetJoueur, data element[], int compteur)
{
    if ((compteur%100) == 0)
    {
        for (int j=2; j<75; j++)
        {
            if (element[j].init == 1)
            {
                if ((element[j].type == 4) && (element[j].y == element[0].y) && ((element[j].x < element[0].x + 5) && (element[j].x > element[0].x - 5))) //Gestion des collision pour les ennemis
                {
                    *pointe_vie = *pointe_vie - 1;
                    element[j].init = 0;    //Désinitialisation de l'élément
                }

                else if ((element[j].type == 3) && (element[j].y == element[0].y) && ((element[j].x < element[0].x + 5) && (element[j].x > element[0].x - 5))) //Gestion des collision pour les pilules
                {
                    *pointe_vie = *pointe_vie + 1;
                    element[j].init = 0;    //Désinitialisation de l'élément
                }

                else if ((*pointe_effetJoueur == 0) && (element[j].type == 1) && (element[j].y == element[0].y) && (element[j].x + 5 < element[0].x)) //Gestion des collisions pour les malus
                {
                    *pointe_effetJoueur = 10;
                    element[j].init = 0;    //Désinitialisation de l'élément
                }
                else if ((*pointe_effetJoueur == 0) && (element[j].type == 2) && (element[j].y == element[0].y) && (element[j].x + 5 < element[0].x)) //Gestion des collisions pour bonus malus
                {
                    *pointe_effetJoueur = 20;
                    element[j].init = 0;    //Désinitialisation de l'élément
                }
            }
        }
    }
}