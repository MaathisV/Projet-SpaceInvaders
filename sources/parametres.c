#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/parametres.h"
#include "../headers/menus.h"
#include "../headers/terminal.h"



extern int tab_parametres[50];

void Fct_Parametres(int option)
{
    switch(option)
    {
        case 0:
            clear();
            ModifCouleurs();
            break;
        case 1:
            clear();
            printw("son");
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
    char *design_elem[7] = {"Interface", "<[°]>", "BOSS", "XXXXX", "OOOOO", "m", "b"};
    char *listmodif[16] = {"Changer la couleur de fond de l'interface", "Changer la couleur de texte de l'interface", "Changer la couleur de fond du joueur", "Changer la couleur de texte du joueur", "Changer la couleur de fond du boss", "Changer la couleur de texte du boss", "Changer la couleur de fond des ennemis", "Changer la couleur de texte des ennemis", "Changer la couleur de fond des pilules", "Changer la couleur de texte des pilules", "Changer la couleur de fond des malus", "Changer la couleur de texte des malus", "Changer la couleur de fond des bonus", "Changer la couleur de texte des bonus", "Couleurs par défaut", "Retour"};
    WINDOW *fenModifCouleur = newwin(22, 48, (tab_parametres[0] / 2) - (22/2), (tab_parametres[1] / 2) - (48 / 2));
    wattron(fenModifCouleur,COLOR_PAIR(1)); 
    box(fenModifCouleur, 0, 0);
    refresh();
    int select=0; //Désigne l'élément duquel on doit modifier la couleur

    keypad(fenModifCouleur, TRUE);

    while(1)
    {
            //Affichage des éléments avec les couleurs choisies
        color();    //
        for (int i=0; i<7; i++)
        {
            attron(COLOR_PAIR(i+1));
            mvprintw(i, 0, design_elem[i]);
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
                if (select == 15)   //On souhaite retourner au menu précédent
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