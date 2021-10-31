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
#include <string.h>


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
    curs_set(0);
    keypad(stdscr, true);
}



/*FONCTION ChoixMenu() : Affiche un menu et récupère le choix utilisateur 
Entrées : néant
Sorties : choix (choix de l'utilisateur ; (1:Jouer, 2: Règles, 3:Paramètres, 4:Scores, 5:Quitter))*/
int ChoixMenu()
{
    int choix=-1;  //Valeur du choix utilisateur

    // Affichage de l'écran d'accueil et du menu
    while (choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5)
    {
        printw("Bienvenue dans le jeu\n que voulez vous faire\n1 - Jouer\n2 - Règles\n3 - Paramètres\n4 - Scores\n5 - Quitter\n Votre choix :");
        scanw("%d", &choix);
        refresh();
    }
    return choix;
}



/*FONCTION DeplacementVaisseau() : Recupère l'entrée clavier et fait bouger le vaisseau sur la console
Entrées : néant
Sorties : néant*/
int DeplacementVaisseau()
{
    int x_vaisseau=0; //abscisse vaisseau
    int clavier='!'; //action clavier utilisateur

    //noecho();   //n'affiche pas les entrées sur le terminal

    printw("<|>");  //Affichage du vaisseau
    
    while(clavier!='p')
    {
        // Modification des données du jeu et entrees utilisateur
        if (clavier=='q')
        {
            mvprintw(LINES,(x_vaisseau - 3),"    ");    //effacement du vaisseau précédent
            x_vaisseau--;   //décrémentation
            mvprintw(LINES,(x_vaisseau),"<|>"); //affichage du vaisseau au nouvel emplacement
            clavier = nb_getch();
        }
        else if (clavier=='d')
        {
            mvprintw(LINES,(x_vaisseau - 3),"    ");    //effacement du vaisseau précédent
            x_vaisseau++;   //incrémentation
            mvprintw(LINES,(x_vaisseau),"<|>"); //affichage du vaisseau au nouvel emplacement
            clavier = nb_getch();
        }

        else if (clavier=='p')
        {
            printw("fin du jeu");
            system("clear");
        }

        refresh();
        sleep(0.01);
    }

    clavier = nb_getch();
}



/*FONCTION Jouer() : Démarre le jeu
Entrées : néant
Sorties : néant*/
int Jouer()
{
    char nom;

    system("clear");
    mvprintw(0, (COLS / 2) - (19 / 2), "Saisissez votre nom");
    move(3,(COLS/2));
    scanw("%c",&nom);
    system("clear");
    
    DeplacementVaisseau();

}



int main()
{
    startscr();
        //Affichage du menu et aiguillage
    switch(ChoixMenu())
    {
        case 1: Jouer();
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