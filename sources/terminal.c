#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include "../headers/terminal.h"
#include "../headers/scores.h"


extern int tab_parametres[17];

    //FONCTIONS DE DEMARRAGE ET D'INITIALISATION
void startscr()
{
    initscr();
    start_color();
    cbreak();
    curs_set(FALSE);
    noecho();
}


void InitTabs()
{
    dim_terminal();
    DefautCouleurs();
    color();
    InitScore();
}


void dim_terminal()
{
    getmaxyx(stdscr, tab_parametres[0], tab_parametres[1]);
    mvprintw(tab_parametres[0]/3 + 6, 0, "Les dimensions du terminal ont été mises à jour\nLe terminal fait maintenant %d de haut et %d de large\n\tAppuyer pour continuer", tab_parametres[0], tab_parametres[1]);   //Affichage des dimensions du terminal

        //Message de prévention en cas de tailles de terminal non conventionnelles
    if ((tab_parametres[0] < 24) || (tab_parametres[1] < 80))
        mvprintw(0, 0, "La taille de votre terminal est inférieure aux dimensions recommandées\nLa jouabilité du programme peut être compromise\nEssayez d'agrandir votre terminal svp (puis mettez à jour dans les paramètres)");
    else if (tab_parametres[0] > 70 || tab_parametres[1] > 200)
        mvprintw(0, 0, "Votre terminal est très grand\nGardez en tête que cela peut influencer les performances du jeu et sa difficulté");
    int pause = getch();    //Pause pour laisser afficher l'information
    clear();
}



    //FONCTIONS DE GESTION DES COULEURS
void color()
{
        //Initialisation des paires de couleurs (texte puis fond)
    init_pair(1,tab_parametres[2],tab_parametres[3]);   //Couleurs de l'interface
    init_pair(2,tab_parametres[4],tab_parametres[5]);   //Couleurs du joueur
    init_pair(3,tab_parametres[6],tab_parametres[7]);   //Couleurs du BOSS
    init_pair(4,tab_parametres[8],tab_parametres[9]);   //Couleurs des ennemis
    init_pair(5,tab_parametres[10],tab_parametres[11]);   //Couleurs des pilules
    init_pair(6,tab_parametres[12],tab_parametres[13]);   //Couleurs des malus
    init_pair(7,tab_parametres[14],tab_parametres[15]);   //Couleurs des bonus
    init_pair(8, COLOR_WHITE, COLOR_BLACK); //Couleurs des tirs (non modifiable)
}


void DefautCouleurs()
{
        //Dans l'ordre et deux par deux (fond puis texte) : interface, joueur, boss, ennemis, pilules, malus, bonus
    tab_parametres[3] = COLOR_BLACK;
    tab_parametres[2] = COLOR_WHITE;
    tab_parametres[5] = COLOR_BLACK;
    tab_parametres[4] = COLOR_WHITE;
    tab_parametres[7] = COLOR_WHITE;
    tab_parametres[6] = COLOR_BLACK;
    tab_parametres[9] = COLOR_BLACK;
    tab_parametres[8] = COLOR_WHITE;
    tab_parametres[11] = COLOR_BLACK;
    tab_parametres[10] = COLOR_WHITE;
    tab_parametres[13] = COLOR_WHITE;
    tab_parametres[12] = COLOR_BLACK;
    tab_parametres[15] = COLOR_WHITE;
    tab_parametres[14] = COLOR_BLACK;
}



    //FONCTIONS DE SAISIE
char nb_getch()
{
    timeout(0);
    return getch();
}
char nb_wgetch(WINDOW* fenetre)
{
    timeout(0);
    return wgetch(fenetre);
}


char b_getch()
{
    timeout(-1);
    return getch();
}
char b_wgetch(WINDOW* fenetre)
{
    timeout(-1);
    return wgetch(fenetre);
}


void SaisieChaine(WINDOW *fenetre, int y, int x, char chaine[], int longueur, bool validation)
{
    int l=0; //Curseur compris entre longueur et 0
    curs_set(TRUE);
    keypad(fenetre, TRUE);  //Empeche la récupération des touches directionnelles (et autres) en tant que char
    wrefresh(fenetre);
    while (l<longueur)
    {
        mvwprintw(fenetre, y, x, chaine);
        wrefresh(fenetre);
        move(y, x+l);
        int caractere = getch();
        move(tab_parametres[0] - 3, 0);
        clrtoeol();
        if (isgraph(caractere))
        {
            chaine[l] = caractere;
            l++;
        }
        else if ((validation == TRUE) && (iscntrl(caractere)) && (caractere == '\n') && (l>0))   //Si l'option de validation est activée et que caractere est à la fois un caractère de controle et le retour à la ligne + chaine trop courte
        {
            chaine[l] = '\0';   //Place le caractère de fin de chaine
            keypad(fenetre, FALSE);
            curs_set(FALSE);
            return;
        }
        else if (caractere == KEY_BACKSPACE)    //Permet d'effacer le caractère précédent avec retour arrière
        {
            if (l>0)
                l--;
            chaine[l] = '_';
        }
        else
            mvwprintw(fenetre, tab_parametres[0] - 3, (tab_parametres[1]/2) - (17/2),"Saisie incorrecte");
    }
    mvwprintw(fenetre, y, x, chaine);
    chaine[longueur] = '\0';  //Place le caractère de fin de chaine
    keypad(fenetre, FALSE);
    curs_set(FALSE);
    return;
}