#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/scores.h"

extern int tab_parametres[17];
extern score joueur[11];

void InitScore()
{
    for (int i=0; i<11; i++)
        joueur[i].score = 0;

    //initialise le tableau avec le contenu du fichier
    FILE* fscore = fopen("classement","r");
    if (fscore != NULL)
    {
        for (int i=0;i<11;i++)
        {
            fscanf(fscore,"%s : %d\n", joueur[i].pseudo, &joueur[i].score);
        }
        fclose(fscore);
    }
}


void SauvScore()
{
    //ecrit le tableau dans le fichier
    int i;
    FILE* fscore = fopen("classement","w+");
    refresh();
    if (fscore != NULL)
    {
        for (i=0;i<11;i++)
        {
            fprintf(fscore,"%s : %d\n",joueur[i].pseudo ,joueur[i].score);
            refresh();
        }
        fclose(fscore);
    }
}    

void AffScore()
{
    char titre[5][38] = {"   _____ __________  ____  ___________",
                         "  / ___// ____/ __ \\/ __ \\/ ____/ ___/",
                         "  \\__ \\/ /   / / / / /_/ / __/  \\__ \\ ",
                         " ___/ / /___/ /_/ / _, _/ /___ ___/ / ",
                         "/____/\\____/\\____/_/ |_/_____//____/  "};
    int posy = 1;
    int posx = (tab_parametres[1] / 2) - (38 / 2);

    attron(COLOR_PAIR(1));
        //Afficher le titre de la fenetre 
    for(int k=0;k<5;k++)
    {
        for(int j=0;j<38;j++)
        {
            mvprintw(posy, posx, "%c",titre[k][j]);
            posx++;
        }
        posx = (tab_parametres[1] / 2) - (38 / 2);
        posy++;
    }


    
    for (int i=0;i<10;i++)
        mvprintw((tab_parametres[0]/2)-(10/2)+i, (tab_parametres[1]/2) - (22/2), "%s : %d pts", joueur[i].pseudo, joueur[i].score);

    attron(A_ITALIC);
    mvprintw((tab_parametres[0]/2)-(10/2)+11, (tab_parametres[1]/2)-(40/2), "Appuyer sur une touche pour continuer...");
    attroff(A_ITALIC);
    refresh();

    int wait = getchar();
    attroff(COLOR_PAIR(1));
    clear();
    refresh();
    return;
}


void TriScore()
{
    //Tri les scores dans le tableau par ordre croissant
    score stock;
    for(int i=0; i<11-1;i++)
    {
        for(int j=i+1;j<11;j++)
        {
            if (joueur[j].score > joueur[i].score)
            {
                stock = joueur[i];
                joueur[i] = joueur[j];
                joueur[j]= stock;
            }
        }
    }
    joueur[10].score = 0;
    //VIDER PSEUDO

}