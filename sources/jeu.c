#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
//#include <math.h>
#include "../headers/terminal.h"
#include "../headers/jeu.h"
#include "../headers/menus.h"


extern int tab_parametres[50];
extern score joueur[11];
extern char *design_elem[7];

void Jouer()
{
    data element[100] = {0}; //Définition des données d'un élément (coordonnées et type) avec initialisation à zéro
    int vie;    //nb de vie du joueur
    int *pointe_vie = &vie;    //Pointe la variable vie
    int effetJoueur=0; //Désigne le malus ou bonus qui affecte le joueur (0: rien, 11: acceleration des éléments, 12: inversion des commandes du vaisseau, 21: invicibilité, 22: canon activé)
    int *pointe_effetJoueur = &effetJoueur;  //pointe la variable effetJoueur 
    int clavier;    //Saisie utilisateur
    int pause;  //détermine l'état de la pause
    int compteur = 0;   //Compte le nombre d'itérations de la boucle de jeu
    int i=2;    //Permet de controler l'itération (fais en sorte que le délai soit respecté)
    int score=0;
    int *pointe_score=&score;    //Pointeur sur la variable score
    //double long_sc = 8 + log(score) + 1;
    int delai=100;  //Controle la vitesse des éléments (100 correspond à une seconde)
    int *pointe_delai=&delai;    //Pointeur sur la variable delai
    int duree=0;    //Compte le temps d'application d'un effet
    int *pointe_duree=&duree;
    int derniertir=0;   //Stocke la valeur de compteur lors du dernier tir
    int *pointe_derniertir=&derniertir; //Pointeur sur la variable derniertir


    refresh();
    vie = DebutPartie(joueur);
    if (vie == -1)  //Quitte direction le menu
        return;
    AffichageCompteur();

        //Définition de la fenêtre de jeu
    WINDOW *jeu = newwin(tab_parametres[0] - 3, tab_parametres[1], 2, 0);
    wattron(jeu,COLOR_PAIR(1)); 
    box(jeu, 0, 0);
    nodelay(jeu, TRUE);
    

        //Initialisation de l'emplacement du vaisseau
    element[0].x = 1;
    element[0].y = tab_parametres[0] - 5;
    element[0].init = 1;
 
    element[1].init = 0;    //Boss (non implémenter)


    while (vie != 0)
    {
        compteur++;
        
        clavier = nb_wgetch(jeu);   //Récupère la saisie clavier dans la fenêtre de jeu
        //clavier = nb_getch

        GestionEff(jeu, element, compteur, delai);  //efface les éléments déplacés de la boucle precédente

        if (clavier == 27) //la touche es est pressée
        {
            int val_pause = Pause();
            if (val_pause == -1)
            {
                clear();
                delwin(jeu);
                refresh();
                return;
            }
        }

        GestionMvElem(clavier, element, pointe_effetJoueur, pointe_derniertir, compteur, delai, i);
        GestionAff(jeu, element, compteur, i);

        wrefresh(jeu);

        GestionCollision(pointe_vie, pointe_effetJoueur, pointe_score, element, compteur, delai);
        GestionEffetMalusBonus(pointe_effetJoueur, pointe_delai, pointe_duree, compteur);
        MajAffInterface(vie, score, effetJoueur);


        if ((compteur%100) == 0)
        {
            i++;
            if ((element[1].init != 1) /*&& (effetJoueur != -1)*/)  //Augmentation du score si le boss n'apparait pas (ou si le joueur n'est pas touché par un ennemi => not implmented yet)
                score++;
            if (i >= 30)
                i = 2;
        }
        
        

        usleep(10000);
    }
}

int DebutPartie(score joueur[11])
{
    int clavier;   //Récupère la saisie clavier
    char pseudo;    //Récupère le pseudo
    int selection_vie = 5;  //Nombre de vies selectionnées (entre 1 et 5, 5 par défaut)
    int modif = 1;  //Désigne le réglage a modifier (1: pseudo, 2 : nombre de vie)


    WINDOW *DebutPartie = newwin(tab_parametres[0], tab_parametres[1], 0, 0);   //Fenetre dans laquelle sera affiché le choix du pseudo et du nombre de vie
    wattron(DebutPartie,COLOR_PAIR(1)); 

    curs_set(TRUE);
    while (1)
    {
        switch (modif)
        {
            case 1:
                echo();
                move((tab_parametres[0] / 4) + 1, (tab_parametres[1] / 2) - (25 / 2));  //Déplace et efface l'éventuel nom précédent en cas d'erreur
                clrtoeol();
                mvwprintw(DebutPartie, tab_parametres[0] / 4, (tab_parametres[1] / 2) - (25 / 2), "Saisissez votre pseudo :");
                mvwscanw(DebutPartie, (tab_parametres[0] / 4) + 1, (tab_parametres[1] / 2) - (24 / 2), "%c", &pseudo);
                modif = 2;
                noecho();
                break;
            case 2:
                keypad(DebutPartie, TRUE);
                mvwprintw(DebutPartie, (tab_parametres[0] / 4) + 4, (tab_parametres[1] / 2) - (31 / 2), "Nombre de vie selectionnées : %d", selection_vie);
                clavier = wgetch(DebutPartie);

                switch (clavier)
                {
                case KEY_DOWN:
                    selection_vie--;
                    if (selection_vie < 1)
                        selection_vie = 1;
                    break;

                case KEY_UP:
                    selection_vie++;
                    if (selection_vie > 5)
                        selection_vie = 5;
                    break;

                case 27:    //touche esc pressé on retourne au menu
                    curs_set(FALSE);
                    clear();
                    delwin(DebutPartie);
                    refresh();
                    return -1;
                    break;

                case 10:    //Entrée pressée, réglages de partie validés
                    curs_set(FALSE);
                    for (int j=0;j<11;j++)  //on stocke le pseudo dans le tableau des scores
                    {
                        if (joueur[j].pseudo == 0)
                            joueur[j].pseudo = pseudo;    //On enregistre dans la première case libre (variable pseudo de la structure egal à zéro -> case vide)
                    }
                    clear();
                    delwin(DebutPartie);
                    return selection_vie;
                    break;
                }
                break;

        wrefresh(DebutPartie);       
        }
    }
}


void AffichageCompteur()
{
    int posx, posy; //Définit la position du compteur

        //Définition des chiffres du compteur
    char trois[5][7] = {" _____ ",
                        "|___ / ",
                        "  |_ \\ ",
                        " ___) |",
                        "|____/ "}; 
                         
    char deux[5][7] = {"  ____ ",
                       " |___ \\",
                       "  __) |",
                       " / __/ ",
                       "|_____|"};
    char un[5][3] ={" _ ",
                    "/ |",
                    "| |",
                    "| |",
                    "|_|"} ; 

    char zero[5][6]={"  ___ ", 
                     " / _ \\ ",
                     "| | | |",
                     "| |_| |",
                     " \\___/ "};   
    

        //Affichage du compteur de démarrage
    //Définition de la position du chiffre
    posy = (tab_parametres[0] / 2) - (5 / 2);
    posx = (tab_parametres[1] / 2) - (7 / 2);
    for(int k=0;k<5;k++)
    {
        for(int j=0;j<7;j++)
        {
            mvprintw(posy, posx, "%c",trois[k][j]);
            posx++;
        }
        posx = (tab_parametres[1] / 2) - (7 / 2);
        posy++;
    }
    refresh();
    clear();
    sleep(1);

    //Définition de la position du chiffre
    posy = (tab_parametres[0] / 2) - (5 / 2);
    posx = (tab_parametres[1] / 2) - (7 / 2);
    for(int k=0;k<5;k++)
    {
        for(int j=0;j<7;j++)
        { 
            mvprintw(posy, posx, "%c",deux[k][j]);
            posx++;
        }
        posx = (tab_parametres[1] / 2) - (7 / 2);
        posy++;
    }
    refresh();
    clear();
    sleep(1);

    //Définition de la position du chiffre
    posy = (tab_parametres[0] / 2) - (5 / 2);
    posx = (tab_parametres[1] / 2) - (3 / 2);
    for(int k=0;k<5;k++)
    {
        for(int j=0;j<3;j++)
        {
            mvprintw(posy, posx, "%c",un[k][j]);
            posx++;
        }
        posx = (tab_parametres[1] / 2) - (3 / 2);
        posy++;
    }
    refresh();
    clear();
    sleep(1);
    
    //Définition de la position du chiffre
    posy = (tab_parametres[0] / 2) - (5 / 2);
    posx = (tab_parametres[1] / 2) - (6 / 2);
    for(int k=0;k<5;k++)
    {
        for(int j=0;j<6;j++)
        {
            mvprintw(posy, posx, "%c",zero[k][j]);
            posx++;
        }
        posx = (tab_parametres[1] / 2) - (6 / 2);
        posy++;
    }
    refresh();
    clear();
    refresh();
    sleep(1);
}


void MajAffInterface(int vie, int score, int effetJoueur)
{
    mvprintw(0,0, "Vie(s) : %d", vie);
    mvprintw(0,tab_parametres[1] - 12, "Score : %d", score);
    attron(A_DIM);
    mvprintw(tab_parametres[0] - 1, (tab_parametres[1] / 2) - (15/2), "CANON DESACTIVE");
    attroff(A_DIM);
    //mvprintw(1,tab_parametres[1] - 12, "effet : %d", effetJoueur);
    switch (effetJoueur)
    {
        case 11:
            attron(COLOR_PAIR(6));
            mvprintw(tab_parametres[0] - 1, 0, "ACCELERATION");
            attroff(COLOR_PAIR(6));
            break;
        case 12:
            attron(COLOR_PAIR(6));
            mvprintw(tab_parametres[0] - 1, 0, "INVERSION");
            attroff(COLOR_PAIR(6));
            break;
        case 21:
            attron(COLOR_PAIR(7));
            mvprintw(tab_parametres[0] - 1, 0, "INVICIBLE");
            attroff(COLOR_PAIR(7));
            break;
        case 22:
            mvprintw(tab_parametres[0] - 1, (tab_parametres[1] / 2) - (15/2), "               ");
            attron(COLOR_PAIR(7));
            mvprintw(tab_parametres[0] - 1, (tab_parametres[1] / 2) - 6, "CANON ACTIVE");
            attroff(COLOR_PAIR(7));
        case 0:
            mvprintw(tab_parametres[0] - 1, 0, "            ");
            break;
    }

    refresh();
}



int Pause()
{
    int compteur_pause=0;   //Permet de confirmer la sortie du jeu
    mvprintw(0, (tab_parametres[1] / 2) - (5/2), "PAUSE");
    while (1)
    {
        int saisie_pause  = b_getch();  //stoppe l'execution tout en recuperant les saisies clavier
        switch (saisie_pause)
        {
            case 27:   //on stoppe la pause
                mvprintw(0, (tab_parametres[1] / 2) - (5/2), "     ");
                return 0;
                break;
            case 32:    //on demande a quitter le jeu (avec la touche espace)
                compteur_pause++;
                if (compteur_pause == 2)    //la demande est confirmée on quitte le jeu
                    return -1;
                break;
        }
    }
}



void initElem(data element[100], int i)
{
    if (element[i].init == 0)
    {
        element[i].y = 0;
        element[i].type = Tirage();
        if ((element[i].type == 3) || (element[i].type == 4))
            element[i].x = rand()%(tab_parametres[1] - 5 - 2) + 1;
        if ((element[i].type == 2) || (element[i].type == 1))
            element[i].x = rand()%(tab_parametres[1] - 1 - 2) + 1;
        element[i].init = 1;
    }    
}



int Tirage()
{
    int element;    //Désigne l'élément à apparaitre tiré au sort
    int tirage; //Valeur aléatoire qu décide du prochain element
    int nb_bonus, nb_malus, nb_pilules;  //Compte le nombre d'élements respectifs apparus consécutivement pour restreindre l'aléatoire

    tirage = rand()%20;

    if ((tirage == 0) || (tirage == 1))
        {
            element = 1;    //Un malus apparait
            //nb_malus++;
            nb_bonus = 0;
            nb_pilules = 0;
        }
        else if (((tirage == 2) || (tirage == 3)) && (nb_bonus <= 3))
        {
            element = 2; //un bonus apparait
            nb_bonus++;
            nb_pilules = 0;
        }
        else if ((tirage >= 4 && tirage <= 8) && nb_pilules <= 5)
        {
            element = 3;    //une pilule apparait
            nb_pilules++;
            nb_bonus = 0;
        }
        else
        {
            element = 4;    //un ennemi apparait
            nb_pilules = 0;
            nb_malus = 0;
            nb_bonus = 0;        
        }
    return element;
}



void GestionMvElem(int clavier, data element[100], int *pointe_effetJoueur, int *pointe_derniertir, int compteur, int delai, int i)
{

        // Modification de la position du vaisseau en fonction des entrees clavier
    switch (clavier)
    {
        case 'q':   //Bouge le vaisseau à gauche
            if (*pointe_effetJoueur == 12)   //Sauf si le malus d'inversion est activé
            {
                element[0].x++;
                if (element[0].x > tab_parametres[1] - 1 - 6)
                    element[0].x = tab_parametres[1] - 1 - 6;    
            }
            else
            {
                element[0].x--;
                if (element[0].x == 0)
                    element[0].x = 1;
            }
            break;

        case 'd':   //Bouge le vaisseau à droite
            if (*pointe_effetJoueur == 12)  //Sauf si le malus d'inversion est activé
            {
                element[0].x--;
                if (element[0].x == 0)
                    element[0].x = 1;
            }
            else
            {
                element[0].x++;
            if (element[0].x > tab_parametres[1] - 1 - 6)
                element[0].x = tab_parametres[1] - 1 - 6;
            }
            break;

        case 32:    //Appuie sur la touche espace, déclenchement du tir de canon
            if ((*pointe_effetJoueur == 22) && ((compteur - *pointe_derniertir) >= 50))  //Seulement si le bonus à été accordé et si le cooldown de 0.5s est passé
            {
                *pointe_derniertir = compteur;
                element[30].init = 1;
                element[30].type = 5;
                element[30].x = element[0].x + 2;
                element[30].y = element[0].y + 1;
            }
            break;
    }

    if ((compteur%100) == 0)
    {
        initElem(element, i);
        for (int j=2; j<80; j++)    //On passe que sur les éléments qui ont un délai à respecter (pilules, ennemis, bonus, malus)
        {
            if (element[j].init == 1)
            {
                if (element[j].y > (tab_parametres[0] - 6)) //Si il atteint le bord inférieur de la fenetre de jeu
                    element[j].init = 0;    //Désinitialisé/Disparait
                else
                    element[j].y++; //Il descends
            }
        }
    }
    for (int j=80; j<100; j++) 
    {
        if ((element[j].init == 1) && (element[j].type == 6))   //Si l'élément est initialisé et est un tir ennemi
        {
            if (element[j].y > (tab_parametres[0] - 6)) //Si il atteint le bord inférieur de la fenetre de jeu
                element[j].init = 0;    //Désinitialisé/Disparait
            else
                element[j].y++; //Il descends
        }
        else if ((element[j].init == 1) && (element[j].type == 5))   //Si l'élément est initialisé et est un tir ami 
        {
            if (element[j].y < (3)) //Si il atteint le bord inférieur de la fenetre de jeu
                element[j].init = 0;    //Désinitialisé/Disparait
            else
                element[j].y--; //Il monte
        }
    }
}



void GestionAff(WINDOW *jeu, data element[], int compteur, int delai)
{
    wattron(jeu, COLOR_PAIR(2));
    mvwprintw(jeu, element[0].y, element[0].x, design_elem[1]);  //affichage du vaisseau
    wattroff(jeu, COLOR_PAIR(2));


    if ((compteur%100) == 0)
    {
        for (int j=2; j<80; j++)
        {
            if (element[j].init == 1)
            {
                switch (element[j].type)    //Affichage des autres element du jeu
                {
                    case 0:
                        //BOSS (a implanter)
                        //wattron(jeu, COLOR_PAIR(3));
                        //wattron(jeu, A_UNDERLINE)
                        //mvwprintw(jeu, element[1].y, element[1].x, design_elem[2]);
                        //wattroff(jeu, A_UNDERLINE)
                        //wattroff(jeu, COLOR_PAIR(3));
                        break;
                    case 1:
                        wattron(jeu, COLOR_PAIR(7));
                        mvwprintw(jeu, element[j].y, element[j].x, design_elem[5]); //Affichage malus
                        wattroff(jeu, COLOR_PAIR(7));
                        break;
                    case 2:
                        wattron(jeu, COLOR_PAIR(6));
                        mvwprintw(jeu, element[j].y, element[j].x, design_elem[6]); //Affichage bonus
                        wattroff(jeu, COLOR_PAIR(6));
                        break;
                    case 3:
                        wattron(jeu, COLOR_PAIR(5));
                        mvwprintw(jeu, element[j].y, element[j].x, design_elem[4]); //Affichage pilule
                        wattroff(jeu, COLOR_PAIR(5));
                        break;
                    case 4:
                        wattron(jeu, COLOR_PAIR(4));
                        mvwprintw(jeu, element[j].y, element[j].x, design_elem[3]); //Affichage ennemi
                        wattroff(jeu, COLOR_PAIR(4));
                        break;
                }
            }
        }
    }
    for (int j=80; j<100; j++)
    {
        if (element[j].init == 1)   
        {
            //Présentement affiché avec les couleurs d'interface, penser à changer
            mvwaddch(jeu, element[j].y, element[j].x, ACS_BULLET);  //Affichage des tirs initialisés
        }
    }
}



void GestionEff(WINDOW *jeu, data element[100], int compteur, int delai)
{
        //Effacemement du vaisseau
    mvwprintw(jeu, element[0].y, element[0].x, " ");
    mvwprintw(jeu, element[0].y, element[0].x + 5, " ");  

    if ((compteur%100) == 0)
    {
        for (int j=2; j<80; j++)
        {
            if (element[j].init == 1);
            {
                if ((element[j].type == 1) || (element[j].type == 2))
                    mvwprintw(jeu, element[j].y, element[j].x, " ");
                else if ((element[j].type == 3) || (element[j].type == 4))
                    mvwprintw(jeu, element[j].y, element[j].x, "     ");
            }
        }
    }
    for (int j=80; j<100; j++)
    {
        if (element[j].init == 1);  //Pas besoin de vérifier le type, les éléments de 30 à 50 sont forcément des tirs, on ne les efface que s'ils sont initialisés/affichés
            mvwprintw(jeu, element[j].y, element[j].x, " ");
    }
}



void GestionCollision(int *pointe_vie, int *pointe_effetJoueur, int *pointe_score, data element[100], int compteur, int delai)
{
    for (int j=2; j<80; j++)    //Balayage éléments
    {
        if (element[j].init == 1)
        {
            for (int k=80; k<100; k++)   //Balayage des tirs (uniquements pour les éléments initialisés)
            {
                if ((element[k].type == 5) && (element[j].type == 4) && (element[k].y == element[j].y) && (element[k].x >= element[j].x) && (element[k].x <= element[j].x + 5))   //Si un tir ami rentre en collision avec un ennemi
                {
                    *pointe_score += 10;
                    element[k].init = 0;
                    element[j].init = 0; 
                }

                else if ((element[k].type == 5) && (element[j].type != 4) && (element[k].y == element[j].y) && (element[k].x >= element[j].x) && (element[k].x <= element[j].x + 5))   //Si un tir ami rentre en collision avec autre chose qu'un ennemi
                {
                    element[k].init = 0;
                    element[j].init = 0;
                }

                else if ((element[k].type == 6) && (element[k].y == element[j].y) && (element[k].x >= element[j].x) && (element[k].x <= element[j].x + 5))  //Si un tir ennemi rentre en colision avec le vaisseau
                {
                    *pointe_vie -= 2;
                    element[k].init = 0;
                }
            }


            if ((*pointe_effetJoueur != 21) && (element[j].type == 4) && (element[j].y == element[0].y) && ((element[j].x < element[0].x + 5) && (element[j].x > element[0].x - 5))) //Gestion des collision pour les ennemis
            {
                *pointe_vie = *pointe_vie - 1;
                element[j].init = 0;    //Désinitialisation de l'élément
            }

            else if ((element[j].type == 3) && (element[j].y == element[0].y) && ((element[j].x < element[0].x + 5) && (element[j].x > element[0].x - 5))) //Gestion des collision pour les pilules
            {
                *pointe_vie = *pointe_vie + 1;
                element[j].init = 0;    //Désinitialisation de l'élément
            }

            else if ((*pointe_effetJoueur == 0) && (element[j].type == 1) && (element[j].y == element[0].y) && (element[j].x >= element[0].x) && (element[j].x <= element[0].x + 5)) //Gestion des collisions pour les malus
            {
                *pointe_effetJoueur = (rand()%2) + 11;  //Tirage aléatoire entre les deux malus présentement implanté (acceleration et inversion)
                element[j].init = 0;    //Désinitialisation de l'élément
            }
            else if ((*pointe_effetJoueur == 0) && (element[j].type == 2) && (element[j].y == element[0].y) && (element[j].x >= element[0].x) && (element[j].x <= element[0].x + 5)) //Gestion des collisions pour les bonus
            {
                *pointe_effetJoueur = (rand()%2) + 21;  //Tirage aléatoire entre les deux bonus présentement implanté (invincibilité et canon)
                element[j].init = 0;    //Désinitialisation de l'élément
            }
        }
    }
}



void GestionEffetMalusBonus(int *pointe_effetJoueur, int *pointe_delai, int *pointe_duree, int compteur)
{
        //Debug affichage des booléens des conditions car le délai des effets ne fonctionnent pas
    /*mvprintw(3,3, "%d", (*pointe_duree <= 5));
    mvprintw(4, 4, "%d", ((compteur%100) == 0));*/
    switch (*pointe_effetJoueur)
    {
        case 11:    //Acceleration
            *pointe_delai = *pointe_delai / 2;
            *pointe_effetJoueur = 19;   //Définit à 19 pour éviter de réduire le délai en boucle
            if (((compteur%100) == 0) && (*pointe_duree <= 5))
                *pointe_duree++;
            else if (*pointe_duree > 5)
            {
                *pointe_delai = *pointe_delai * 2;  //Réapplique l'ancienne vitesse
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            }
            break;
        
        case 12:    //Inversion des commandes du vaisseau (voir dans GestionMvElem)
            if (((compteur%100) == 0) && (*pointe_duree <= 15))
                *pointe_duree++;
            else if (*pointe_duree > 15)
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            break;

        case 21:    //Invincibilité aux ennemis (voir dans GestionCollision)
            if (((compteur%100) == 0) && (*pointe_duree <= 10))
                *pointe_duree++;
            else if (*pointe_duree > 10)
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            break;
        
        case 22:    //Canon activé
            if (((compteur%100) == 0) && (*pointe_duree <= 30))
                *pointe_duree++;
            else if (*pointe_duree > 30)
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            break;

        case 0: //Aucun effet n'est appliqué
            *pointe_duree = 0;  //Alors remise à zéro du temps d'application d'un effet
            /*if (compteur%100 == 0)
                mvprintw(1,1, "hello");
            break;*/
    }
}