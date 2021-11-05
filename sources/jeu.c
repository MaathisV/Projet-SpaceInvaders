#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../headers/terminal.h"
#include "../headers/jeu.h"
#include "../headers/menus.h"



int Jouer(int tab_parametres[])
{
        //Variable vaisseau
    int x_vaisseau=tab_parametres[0] / 2; //abscisse vaisseau
    int clavier; //action clavier utilisateur
    char vaisseau[] = "<[°]>";
    int taille_vaisseau = strlen(vaisseau);

        //Variable ennemis, pilules
    int pos_elem[50];   //position y et x des ennemis, pilules, etc
    char pilule[] = "OOOO";
    int taille_pilule = strlen(pilule);
    char ennemi[] = "XXXX";
    int taille_ennemi = strlen(ennemi);
    int tirage; //Détermine quel élement apparaitra sur l'écran en fonction d'une valeur aléatoire
    int nb_pilules; //Stocke le nombre de pilules apparues a la suite
    int nb_bonus, nb_malus; //Stocke le nombre de bonus/malus apparus à la suite

        //Variable interface
    int start = 0; //définit l'état du jeu, en cours ou non
    int pause = 0;  //définit l'état de la pause, activée ou non
    int saisie_pause = 0;   //récupère la saisie clavier lorsque le jeu est en pause
    int compteur_pause = 0; //compte le nombre de fois qu'une saisie particulière est récupérée

    

        //Création de la fenetre de jeu
    WINDOW *jeu = newwin(tab_parametres[0] - 2, tab_parametres[1], 4, 0);
    box(jeu, 0, 0);

        //Affichage des éléments
    mvprintw(tab_parametres[0], 0, "je suis le jeu");
    mvwprintw(jeu, tab_parametres[0] - 10, x_vaisseau, vaisseau);

    refresh();
    wrefresh(jeu);

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
    start = 1;
    mvprintw(0, 0, " ");
    refresh();
       

    while(start == 1)
    {   
        nodelay(jeu, TRUE);
        clavier = nb_wgetch(jeu);

        mvwprintw(jeu, tab_parametres[0] - 10, x_vaisseau, vaisseau);  //affichage du vaisseau

        // Modification des données du jeu et entrees utilisateur
        switch (clavier)
        {
        case 'q':
            x_vaisseau--;
            if (x_vaisseau == 0)
                x_vaisseau = 1;
            break;
        case 'd':
            x_vaisseau++;
            if (x_vaisseau > tab_parametres[1] - 1 - taille_vaisseau)
                x_vaisseau = tab_parametres[1] - 1 - taille_vaisseau;
            break;
        case 32:    //la touche espace est pressée
            mvprintw(0, (tab_parametres[1] / 2) - (5/2), "PAUSE");
            pause = 1;
            while (pause == 1)
            {
                saisie_pause  = b_getch();  //stoppe l'execution tout en recuperant les saisies clavier
                switch (saisie_pause)
                {
                    case 32:   //on stoppe la pause
                        mvprintw(0, (tab_parametres[1] / 2) - (5/2), "     ");
                        compteur_pause = 0;
                        pause = 0;
                        break;
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

            break;
        }


        mvwprintw(jeu, tab_parametres[0] - 10, x_vaisseau-2, " ");
        mvwprintw(jeu, tab_parametres[0] - 10, x_vaisseau + taille_vaisseau + 1, " ");
        box(jeu, 0, 0);

        wrefresh(jeu);
        sleep(0.01);


        int i;  //pour naviguer dans le tableau des valeurs et descendre chaque élément (a implenter) (thread?)
            //Positionnement aléatoire de l'abscisse de départ du prochaine element
            pos_elem[i] = 1;
        pos_elem[i+1] = rand()%(tab_parametres[1] - 1 - taille_pilule) + 1;

            //Tirage aléatoire du prochain element a apparaitre
        tirage = rand()%20;
        if (tirage == 0)
        {
            //mvwprintw(jeu, pos_elem[0], pos_elem[1], malus)
            //nb_malus++;
            nb_bonus = 0;
            nb_pilules = 0;
        }
        else if (tirage == 1 && nb_bonus <= 3)
        {
            //mvwprintw(jeu, pos_elem[i], pos_elem[i+1], bonus)
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


        wrefresh(jeu);
        refresh();
    }
}