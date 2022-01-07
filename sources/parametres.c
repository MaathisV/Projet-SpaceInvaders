#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/parametres.h"
#include "../headers/menus.h"
#include "../headers/terminal.h"
#include "../headers/scores.h"



extern int tab_parametres[17];
extern char design_elem[7][10];

void Fct_Parametres(int option)
{
    switch(option)
    {
        case 0: //Changer les couleurs
            clear();
            ModifCouleurs();
            break;
        case 1: //Modifier le design des éléments
            clear();
            ModifDesign();
            break;
        case 2: //Mettre à jour la taille du terminal
            clear();
            dim_terminal();
            break;
        case 3: //Réinitialisation du tableau des scores
            clear();
            FILE* fscores = fopen("classement", "w+");
            for (int i=0; i<11; i++)
                fprintf(fscores, "%s : %d\n", "____________", 0);
            fclose(fscores);
            InitScore();    //Réinitialise le tableau joueur à partir du fichier
            return;
            break;
        case 4: //Retour au menu précédent
            clear();
            break;
    }
}


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

        for (int i=0; i < 16; i++)  //Affichage du menu avec l'option selectionnée par le curseur en surbrillance
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
                if (select == -1)   //Empêche de sortir du nombre de valeurs définies
                    select = 0;
                break;
            case KEY_DOWN:  //Si flèche bas est pressée
                select++;
                if (select == 16)    //Empêche de sortir du nombre de valeurs définies
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
    char *listmodif[8] = {"Changer le design du joueur", "Changer le design du BOSS", "Changer le design des ennemis", "Changer le design des pilules", "Changer le design des malus", "Changer le design des bonus", "Design par défaut", "Retour au menu principal"};
    WINDOW *fenModifDesign = newwin(10, 32, (tab_parametres[0] / 3) - (10/2), (tab_parametres[1] / 2) - (32/2));
    wattron(fenModifDesign,COLOR_PAIR(1)); 
    box(fenModifDesign, 0, 0);
    refresh();
    int select=0; //Désigne l'élément duquel on doit modifier le design
    char design_defaut[6][10] = {"<[°]>", "<X|-|X>", "XXXXX", "OOOOO", "m", "b"};  //Désign par défaut des éléments

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

        for (int i=0; i < 8; i++)   //Affichage du menu avec l'option selectionnée par le curseur en surbrillance
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
                {
                    for (int d=0; d<6; d++)
                        strcpy(design_elem[d+1], design_defaut[d]);
                }
                else 
                {
                    mvprintw((tab_parametres[0] / 2) + 2, (tab_parametres[1] / 2) - (53/2), "Saisir le nouveau design pour l'élément selectionné :");
                    refresh();
                    if ((select == 5) || (select == 4)) //Modification bonus ou malus donc longueur 1 max
                        SaisieChaine(stdscr, (tab_parametres[0] / 2) + 3, (tab_parametres[1] / 2) - (53/2), design_elem[select+1], 1, FALSE);
                    else if (select == 1)   //Modification de boss donc longueur 7 max
                        SaisieChaine(stdscr, (tab_parametres[0] / 2) + 3, (tab_parametres[1] / 2) - (53/2), design_elem[select+1], 7, FALSE);
                    else    //Modification de ennemi ou pilule donc longueur 5 max
                        SaisieChaine(stdscr, (tab_parametres[0] / 2) + 3, (tab_parametres[1] / 2) - (53/2), design_elem[select+1], 5, FALSE);
                    move((tab_parametres[0] / 2) + 2, (tab_parametres[1] / 2) - 26);
                    clrtobot();
                }
                break;
        }

    }
}