#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/parametres.h"
#include "../headers/menus.h"
#include "../headers/terminal.h"



extern int tab_parametres[50];
extern char *design_elem[7];

void Fct_Parametres(int option)
{
    switch(option)
    {
        case 0:
            clear();
            ModifCouleurs();
            break;
        case 1: //Présentement utilisé pour modifier les caractères des éléments
            clear();
            ModifDesign();
            break;
        case 2:
            clear();
            dim_terminal();
            return;
            break;
        case 3:
            clear();
            printw("Scores effacé");
            int c = getch();
            return;
            break;
        case 4:
            clear();
            break;
    }
}   //"Changer les couleurs", "Activer/Désactiver les effets sonores", "Mettre à jour la taille du terminal","Réinitialiser les scores", "Retour


void ModifCouleurs()
{
    char *listmodif[16] = {"Changer la couleur de texte de l'interface", "Changer la couleur de fond de l'interface", "Changer la couleur de texte du joueur", "Changer la couleur de fond du joueur", "Changer la couleur de texte du boss", "Changer la couleur de fond du boss", "Changer la couleur de texte des ennemis", "Changer la couleur de fond des ennemis", "Changer la couleur de texte des pilules", "Changer la couleur de fond des pilules", "Changer la couleur de texte des malus", "Changer la couleur de fond des malus", "Changer la couleur de texte des bonus", "Changer la couleur de fond des bonus", "Couleurs par défaut", "Retour au menu principal"};
    WINDOW *fenModifCouleur = newwin(18, 48, (tab_parametres[0] / 2) - (18/2), (tab_parametres[1] / 2) - (48 / 2));
    wattron(fenModifCouleur,COLOR_PAIR(1)); 
    box(fenModifCouleur, 0, 0);
    refresh();
    int select=0; //Désigne l'élément duquel on doit modifier la couleur

    keypad(fenModifCouleur, TRUE);

    while(1)
    {
            //Affichage des éléments avec les couleurs choisies
        color();    //Appel de la fonction pour initialiser les nouvelles paires de couleurs
        for (int i=0; i<7; i++)
        {
            attron(COLOR_PAIR(i+1));
            mvprintw((tab_parametres[0] / 2) + i - (7/2), (tab_parametres[1]/2) + 25, design_elem[i]);
            attroff(COLOR_PAIR(i+1));
        }
        refresh();

        for (int i=0; i < 16; i++)
        {
            if (i == select)
            {
                wattron(fenModifCouleur, A_REVERSE);
                mvwprintw(fenModifCouleur, i+1, 1, listmodif[i]);
                wattroff(fenModifCouleur, A_REVERSE);
            }
            else
            {
                mvwprintw(fenModifCouleur, i+1, 1, listmodif[i]);
            }
        }

        int action = wgetch(fenModifCouleur);  //récupère l'action clavier

        switch(action)
        {
            case KEY_UP:    //Si flèche haut est pressée
                select--;
                if (select == -1)   //Empêche de sortir du nombres de valeurs définies
                    select = 0;
                break;
            case KEY_DOWN:  //Si flèche bas est pressée
                select++;
                if (select == 16)    //Empêche de sortir du nombres de valeurs définies
                    select = 15;
                break;
            case 10:    //Si Entrée est pressée
                if (select == 15)   //On souhaite retourner au menu principal
                {
                    clear();
                    delwin(fenModifCouleur);
                    refresh();
                    return;
                }
                else if (select == 14)  //On souhaite remettre les valeurs par défaut
                    DefautCouleurs();
                tab_parametres[select+2]++;  //Incrémente la valeur de la couleur pour l'éléments correspondant dans le tableau des paramètres
                if (tab_parametres[select+2] > 16)
                    tab_parametres[select+2] = 0;
                break;
        }

    }
}


void ModifDesign()
{
    char *listmodif[8] = {"Changer le design du joueur", "Changer le design du BOSS", "Changer le design des ennemis", "Changer le design des pilules", "Changer le design des bonus", "Changer le design des malus", "Design par défaut", "Retour au menu principal"};
    WINDOW *fenModifDesign = newwin(10, 32, (tab_parametres[0] / 3) - (10/2), (tab_parametres[1] / 2) - (32/2));
    wattron(fenModifDesign,COLOR_PAIR(1)); 
    box(fenModifDesign, 0, 0);
    refresh();
    int select=0; //Désigne l'élément duquel on doit modifier le design

    keypad(fenModifDesign, TRUE);

    while(1)
    {
            //Affichage des éléments avec le design choisi
        for (int i=1; i<7; i++)
        {
            attron(COLOR_PAIR(i+1));
            mvprintw((tab_parametres[0] / 3) + i - 4, (tab_parametres[1]/2) + 17, design_elem[i]);
            attroff(COLOR_PAIR(i+1));
        }
        refresh();

        for (int i=0; i < 8; i++)
        {
            if (i == select)
            {
                wattron(fenModifDesign, A_REVERSE);
                mvwprintw(fenModifDesign, i+1, 1, listmodif[i]);
                wattroff(fenModifDesign, A_REVERSE);
            }
            else
            {
                mvwprintw(fenModifDesign, i+1, 1, listmodif[i]);
            }
        }

        int action = wgetch(fenModifDesign);  //récupère l'action clavier

        switch(action)
        {
            case KEY_UP:    //Si flèche haut est pressée
                select--;
                if (select == -1)   //Empêche de sortir du nombres de valeurs définies
                    select = 0;
                break;
            case KEY_DOWN:  //Si flèche bas est pressée
                select++;
                if (select == 8)    //Empêche de sortir du nombres de valeurs définies
                    select = 7;
                break;
            case 10:    //Si Entrée est pressée
                if (select == 7)   //On souhaite retourner au menu principal
                {
                    clear();
                    delwin(fenModifDesign);
                    refresh();
                    return;
                }
                else if (select == 6)  //On souhaite remettre les valeurs par défaut
                    mvprintw(0, 0, "Défaut");
                else 
                {
                    curs_set(TRUE);
                    echo();
                    mvprintw((tab_parametres[0] / 2) + 2, (tab_parametres[1] / 2) - (53/2), "Saisir le nouveau design pour l'élément selectionné :");
                    if ((select == 5) || (select == 4)) //Si l'élément est un bonus ou mal on accepte un chaine de caractère de longeur 1 uniquement
                        mvscanw((tab_parametres[0] / 2) + 2 + 1, (tab_parametres[1] / 2) - (53/2), "%.1c", &design_elem[select+1]);
                    else
                        mvscanw((tab_parametres[0] / 2) + 2 + 1, (tab_parametres[1] / 2) - (53/2), "%.5c", &design_elem[select+1]);
                    mvprintw(0, 0, design_elem[select+1]);  //debug
                    curs_set(FALSE);
                    noecho();
                    move((tab_parametres[0] / 2) + 2, (tab_parametres[1] / 2) - 26);
                    clrtobot();
                }
                break;
        }

    }
}