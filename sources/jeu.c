#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "../headers/terminal.h"
#include "../headers/jeu.h"
#include "../headers/menus.h"



int Jouer(int tab_parametres[])
{
        //Variable vaisseau
    int x_vaisseau=1; //abscisse vaisseau
    int clavier; //action clavier utilisateur
    char vaisseau[] = "<[°]>";
    int taille_vaisseau = strlen(vaisseau);

        //Variable ennemis, pilules
    int pos_elem[50];   //position y et x des ennemis, pilules, etc
    char pilule[] = "OOOO";
    int taille_pilule = strlen(pilule);
    char ennemi[] = "XXXX";
    int taille_ennemi = strlen(ennemi);

        //Variable interface
    int pause = 0;  //définit l'état de la pause, activée ou non
    int saisie_pause = 0;   //récupère la saisie clavier lorsque le jeu est en pause
    int compteur_pause = 0; //compte le nombre de fois qu'une saisie particulière est récupérer

    
    mvprintw(tab_parametres[0], 0, "je suis le jeu");
    WINDOW *jeu = newwin(tab_parametres[0] - 2, tab_parametres[1], 4, 0);
    box(jeu, 0, 0);
    mvwprintw(jeu, tab_parametres[0] - 10, x_vaisseau, vaisseau);
    refresh();
    wrefresh(jeu);

    while(1)
    {
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

        pos_elem[0] = 1;

        mvwprintw(jeu, tab_parametres[0] - 10, x_vaisseau-2, " ");
        mvwprintw(jeu, tab_parametres[0] - 10, x_vaisseau + taille_vaisseau + 1, " ");
        box(jeu, 0, 0);

        wrefresh(jeu);
        sleep(0.01);

        pos_elem[1] = rand()%(tab_parametres[1] - 1 - taille_pilule) + 1;
        mvwprintw(jeu, pos_elem[0], pos_elem[1], pilule);
        wrefresh(jeu);
        refresh();
    }
}