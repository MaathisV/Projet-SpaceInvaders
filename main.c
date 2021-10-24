/*

 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*-------------------------------------------------------------*/
/* DECLARATIONS DES FCTS DE GESTION DU TERMINAL */
/*-------------------------------------------------------------*/
void color(int cT, int cF);
char nb_getch();
char b_getch();
void startscr();

/*-------------------------------------------------------------*/
/* DECLARATION DES FCTS DE GESTION DU JEU */
/*-------------------------------------------------------------*/





/*-------------------------------------------------------------*/
/* FONCTION PRINCIPALE */
/*-------------------------------------------------------------*/
int main()
{
    // Déclaration des variables
    int a=1;
    int x_vaisseau; //abscisse vaisseau
    int xn_vaisseau;  //abscisse n-1 du vaisseau
    int clavier; //action clavier utilisateur

    // Les instructions avant le début du jeu
    startscr();

    // Affichage de l'écran d'accueil et du menu
    printw("Bienvenue dans le jeu\n que voulez vous faire\n1 - Jouer\n2 - Quitter\n Votre choix :");
    scanw("%d", &a);
    refresh();


    // Dans la boucle while les instruction pour le jeu
    while(a==1){

      clavier = nb_getch();

      //affichage vaisseau
  

        // Modification des données du jeu et entrees utilisateur
        if (clavier=='q')
        {
          xn_vaisseau = x_vaisseau-3;
          move(0,xn_vaisseau);
          printw("   ");
          x_vaisseau = x_vaisseau - 1;
          move(0,x_vaisseau);
          printw("<|>");
        }
        else if (clavier=='d')
        {
          xn_vaisseau = x_vaisseau-3;
          move(0,xn_vaisseau);
          printw("   ");
          x_vaisseau = x_vaisseau + 1;
          move(0,x_vaisseau);
          printw("<|>");
        }

        else if (clavier=='p')
        {
          system("clear");
        }

        refresh();
        sleep(0.01);
    }


    // Les instructions avant la cloture du programme
    endwin();

    return 0;
}




/*-------------------------------------------------------------*/
/* DEFINITIONS DES FCTS DE GESTION DU TERMINAL */
/*-------------------------------------------------------------*/

/************************************************************/
/*  Choix des couleurs de la police et de la fen�tre CONSOLE
    cT correspond a la couleur du texte
    cF correspond a la couleur de fond
    Codes couleus :
        0: noir
        1: bleu fonce
        2: vert
        3: bleu-gris
        4: marron
        5: pourpre
        6: kaki
        7: gris clair
        8: gris
        9: bleu
        10: vert fluo
        11: turquoise
        12: rouge
        13: rose fluo
        14: jaune fluo
        15: blanc               */
/************************************************************/
void color(int cT,int cF)
{
    init_pair(1,cT,cF);
    attron(COLOR_PAIR(1));
}

/*-----------------------------------------------------------*/
/* Retourne la touche pressee sans bloquer le deroulement    */
/*-----------------------------------------------------------*/
char nb_getch()
{
    timeout(0);
    return getch();
}

/*-----------------------------------------------------------*/
/* Retourne la touche pressee en bloquant le deroulement     */
/*-----------------------------------------------------------*/
char b_getch()
{
    timeout(-1);
    return getch();
}

/*-----------------------------------------------------------*/
/* Initialise l'ecran */
/*-----------------------------------------------------------*/
void startscr()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    //curs_set(0);
    keypad(stdscr, true);
}


/*-------------------------------------------------------------*/
/* DEFINITION DES FCTS DE GESTION DU JEU */
/*-------------------------------------------------------------*/


