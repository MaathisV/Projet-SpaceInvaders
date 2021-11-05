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
    int x_vaisseau=1; //abscisse vaisseau
    int clavier; //action clavier utilisateur
    char vaisseau[] = "<[°]>";
    int taille_vaisseau = strlen(vaisseau);
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

        mvprintw(0,0,"%d", x_vaisseau);
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
            if (x_vaisseau > tab_parametres[1] - 1) //en réalité la boite  s'arrete a 75
                x_vaisseau = tab_parametres[1] - 1;
            break;
        case 'p':
            mvprintw(0, 0, "PAUSE");
            pause = 1;
            while (pause == 1)
            {
                saisie_pause  = b_getch();  //stoppe l'execution tout en recuperant les saisies clavier
                switch (saisie_pause)
                {
                    case 'p':   //on stoppe la pause
                        mvprintw(0, 0, "     ");
                        pause = 0;
                        break;
                    case 10:    //on demande a quitter le jeu
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
        refresh();
        sleep(0.01);
    }
}