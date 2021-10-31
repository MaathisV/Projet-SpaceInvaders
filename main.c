/*      PROJET SPACE INVADERS
    BERGEREAU Paul et VADEZ Mathis
Développement d'un jeu type Space Invaders en language C et directement dans le terminal
Pour executer le programme dans la console repl.it
gcc -o projet main.c -lncurses
./projet*/


#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//FONCTION DE MISE EN FORME DU TERMINAL
/*Choix des couleurs de la police et de la fenêtre CONSOLE
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
void color(int cT,int cF)
{
    init_pair(1,cT,cF);
    attron(COLOR_PAIR(1));
}



/*Fonction qui récupère la touche pressée sans mettre en pause l'exécution
Entrées : néant
Sorties : néant*/
char nb_getch()
{
    timeout(0);
    return getch();
}



/*Fonction qui récupère la touche pressée en mettant en pause l'exécution
Entrées : néant
Sorties : néant*/
char b_getch()
{
    timeout(-1);
    return getch();
}



/*Fonction d'initialisation de l'écran
Entrées : néant
Sorties : néant*/
void startscr()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
}



/*FONCTION ChoixMenu() : Affiche un menu et récupère le choix utilisateur 
Entrées : néant
Sorties : choix (choix de l'utilisateur ; (1:Jouer, 2: Règles, 3:Paramètres, 4:Scores, 5:Quitter))*/
int ChoixMenu()
{
    int choix;  //Valeur du choix utilisateur
    // Affichage de l'écran d'accueil et du menu
    printw("Bienvenue dans le jeu\n que voulez vous faire\n1 - Jouer\n2 - Règles\n3 - Paramètres\n4 - Scores\n5 - Quitter\n Votre choix :");
    scanw("%d", &choix);
    refresh();
    return choix;
}



/*FONCTION DeplacementVaisseau() : Recupère l'entrée clavier et fait bouger le vaisseau sur la console
Entrées : néant
Sorties : néant*/
int DeplacementVaisseau()
{
        // Déclaration des variables
    int x_vaisseau; //abscisse vaisseau
    int xn_vaisseau;  //abscisse n-1 du vaisseau
    unsigned char clavier=0; //action clavier utilisateur


    // Dans la boucle while les instruction pour le jeu
    while(clavier=='p')
    {
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
}



int main()
{
    startscr();

        //Affichage du menu et aiguillage
    ChoixMenu();
    switch(ChoixMenu())
    {
        case 1: printw("Jouer");
        break;
        case 2: printw("Règles");
        break;
        case 3: printw("Paramètres");
        break;
        case 4: printw("Scores");
        break;
        case 5: printw("Quitter");
    }

    endwin();

    return 0;
}