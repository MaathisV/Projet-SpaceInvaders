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
extern char design_elem[7][10];

void Jouer()
{
    data element[160] = {0}; //Définition des données d'un élément (coordonnées et type) avec initialisation à zéro
    int vie;    //nb de vie du joueur
    int *pointe_vie = &vie;    //Pointe la variable vie
    int clavier;    //Saisie utilisateur
    int pause;  //détermine l'état de la pause
    int compteur = 0;   //Compte le nombre d'itérations de la boucle de jeu
    int i=2;    //Permet de controler l'itération (fais en sorte que le délai soit respecté)
    int score=0;
    int *pointe_score=&score;    //Pointeur sur la variable score
    //double long_sc = 8 + log(score) + 1;
    int delai=100;  //Controle la vitesse des éléments (100 correspond à une seconde)
    int *pointe_delai=&delai;    //Pointeur sur la variable delai
    int effetJoueur=0; //Désigne le malus ou bonus qui affecte le joueur (0: rien, 11: acceleration des éléments, 12: inversion des commandes du vaisseau, 21: invicibilité, 22: canon activé)
    int *pointe_effetJoueur = &effetJoueur;  //pointe la variable effetJoueur 
    int compduree=0;    //Stocke la valeur de compteur au moment de l'application d'un effet
    int *pointe_compduree=&compduree;   //Pointeur sur la variable compduree
    int effetapp=FALSE;    //Indique si l'effet est appliqué
    int *pointe_effetapp=&effetapp; //Pointeur sur la variable effet app
    int derniertir=0;   //Stocke la valeur de compteur lors du dernier tir joueur
    int *pointe_derniertir=&derniertir; //Pointeur sur la variable derniertir
    int compboss; //Stocke la valeur compteur au moment de l'apparition du boss
    int *pointe_compboss=&compboss;  //Pointeur sur compboss
    int boss=0; //Variable permettant de compter le nombre de boss vaincu depuis le début de la partie



    refresh();
    vie = DebutPartie(joueur);
    if (vie == -1)  //Quitte direction le menu
        return;
    AffichageCompteur();

        //Définition de la fenêtre de jeu
    WINDOW *jeu = newwin(tab_parametres[0] - 4, tab_parametres[1], 2, 0);
    wattron(jeu,COLOR_PAIR(1)); 
    box(jeu, 0, 0);
    nodelay(jeu, TRUE);
    

        //Initialisation de l'emplacement du vaisseau
    element[0].x = 1;
    element[0].y = tab_parametres[0] - 6;
    element[0].init = 1;
 
    element[1].init = 0;    //Boss (non initialisé au départ)


    while (vie > 0)
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

        GestionMvElem(clavier, element, pointe_effetJoueur, pointe_derniertir, compteur, delai, i); //Met à jour la position de tous les éléments visibles à l'écran
        GestionAff(jeu, element, compteur, i);  //Affiche les éléments à leur positions

        wrefresh(jeu);

        GestionCollision(pointe_vie, pointe_effetJoueur, pointe_score, element, compteur, delai);   //Modifie les variables concernés lors de la detection d'une collision entre éléments
        GestionEffetMalusBonus(pointe_effetJoueur, pointe_delai, pointe_compduree, pointe_effetapp, compteur);   //Contrôle et applique les effets des malus et des bonus selon une durée déterminée dans le programme
        MajAffInterface(element, vie, score, effetJoueur, compduree, compteur);   //Actualise les données affichées autour de la fenêtre de jeu

        GestionApparitionBoss(jeu, pointe_effetJoueur, pointe_score, pointe_delai, pointe_compboss, compteur, element);

        if (((compteur%delai) == 0) && (element[1].init == 0))    //Si le délai est respecté et que le boss n'est pas initialisé
        {
            i++;
            score++;    //Augmentation du score si le joueur n'est pas touché par un ennemi => not implmented yet)
            if (i >= 80)
                i = 2;
        }
        
        
        usleep(10000);
    }
}

int DebutPartie(score joueur[11])
{
    int clavier;   //Récupère la saisie clavier
    int selection_vie = 5;  //Nombre de vies selectionnées (entre 1 et 5, 5 par défaut)


    mvprintw(tab_parametres[0] / 4, (tab_parametres[1] / 2) - (25 / 2), "Saisissez votre pseudo :");
    mvprintw((tab_parametres[0] / 4) + 1, (tab_parametres[1] / 2) - (36 / 2), "(12 caractères alphanumériques maxi)");
    SaisieChaine(stdscr, (tab_parametres[0] / 4) + 2, (tab_parametres[1] / 2) - (25 / 2), joueur[10].pseudo, 12, TRUE);  //La derniere case du tableau stocke les données du joueur de la partie en cours
        
    curs_set(TRUE);
    keypad(stdscr, TRUE);
    while (1)
    {
        mvprintw((tab_parametres[0] / 4) + 4, (tab_parametres[1] / 2) - (30 / 2), "Nombre de vie selectionnées : %d", selection_vie);
        clavier = getch();

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
            keypad(stdscr, FALSE);
            refresh();
            return -1;
            break;

        case 10:    //Entrée pressée, réglages de partie validés, le jeu démarre
            curs_set(FALSE);
            clear();
            keypad(stdscr, FALSE);
            return selection_vie;
            break;
        }
    refresh();       
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

    char zero[5][7]={"  ___ ", 
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


void MajAffInterface(data element[160], int vie, int score, int effetJoueur, int compduree, int compteur)
{
        //Variables pour le système d'affichage d'une barre de progression pour les effets (non implanté/fonctionnel)
    char barres_prog[6][7] = {"<     >", "<=   >", "<==   >", "<===  >", "<==== >", "<=====>"}; //Différents niveaux de barres de progression pour les effets
    int remplissage = 0;    //Contient la valeur correspondant au niveau de remplissage de la barre de progression

    mvprintw(0,0, "Vie(s) : %d", vie);
    mvprintw(0,tab_parametres[1] - 12, "Score : %d", score);
    //mvprintw(1,tab_parametres[1] - 12, "effet : %d", effetJoueur);    //debug
    switch (effetJoueur)
    {
        case 11:
            attron(COLOR_PAIR(6));
            mvprintw(tab_parametres[0] - 2, (tab_parametres[1]/2) - (12/2), "ACCELERATION");
            attroff(COLOR_PAIR(6));
            //remplissage = ((compteur - compduree) / 500);
            //mvprintw(tab_parametres[0] - 1, (tab_parametres[1]/2) - (7/2), barres_prog[remplissage]);   //Affichage de la barre de progression
            break;
        case 12:
            attron(COLOR_PAIR(6));
            mvprintw(tab_parametres[0] - 2, (tab_parametres[1]/2) - (9/2), "INVERSION");
            attroff(COLOR_PAIR(6));
            //remplissage = ((compteur - compduree) / 1500);
            //mvprintw(tab_parametres[0] - 1, (tab_parametres[1]/2) - (7/2), barres_prog[remplissage]);   //Affichage de la barre de progression
            break;
        case 21:
            attron(COLOR_PAIR(7));
            mvprintw(tab_parametres[0] - 2, (tab_parametres[1]/2) - (9/2), "INVICIBLE");
            attroff(COLOR_PAIR(7));
            //remplissage = ((compteur - compduree) / 1000);
            //mvprintw(tab_parametres[0] - 1, (tab_parametres[1]/2) - (7/2), barres_prog[remplissage]);   //Affichage de la barre de progression
            break;
        case 22:
            attron(COLOR_PAIR(7));
            mvprintw(tab_parametres[0] - 2, (tab_parametres[1]/2) - (12/2), "CANON ACTIVE");
            attroff(COLOR_PAIR(7));
            //remplissage = ((compteur - compduree) / 3000);
            //mvprintw(tab_parametres[0] - 1, (tab_parametres[1]/2) - (7/2), barres_prog[remplissage]);   //Affichage de la barre de progression
            break;
        case 0:
            if (element[1].init == 1)   //Si le boss est présent le joueur ne peut pas avoir d'effet actif
            {
                attron(COLOR_PAIR(3) | A_UNDERLINE);
                mvprintw(tab_parametres[0] - 2, (tab_parametres[1]/2) - (10/2), "BOSS ACTIF");
                attroff(COLOR_PAIR(3) | A_UNDERLINE);
            }
            else
            {
                move(tab_parametres[0] - 2, 0); //Efface le bas de l'écran
                clrtobot();
            }
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



void initElem(data element[160], int i)
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



void GestionMvElem(int clavier, data element[160], int *pointe_effetJoueur, int *pointe_derniertir, int compteur, int delai, int i)
{
    bool boucle_tir;    //Permet de contrôler la sortie de la boucle d'initialisation d'un tir

        // Modification de la position du vaisseau en fonction des entrees clavier
    switch (clavier)
    {
        case 'q':   //Bouge le vaisseau à gauche
            if (*pointe_effetJoueur == 12)   //Sauf si le malus d'inversion est activé
            {
                element[0].x++;
                if (element[0].x > tab_parametres[1] - 2 - 5)   //Retranche 2 à cause des bords de l'écran et retranche 5 à cause de la taille du vaisseau
                    element[0].x = tab_parametres[1] - 2 - 5;    
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
            if (element[0].x > tab_parametres[1] - 2 - 5)
                element[0].x = tab_parametres[1] - 2 - 5;
            }
            break;

        case 32:    //Appuie sur la touche espace, déclenchement du tir de canon
            if ((*pointe_effetJoueur == 22) && ((compteur - *pointe_derniertir) >= 50))  //Seulement si le bonus à été accordé et si le cooldown de 0.5s est passé
            {
                *pointe_derniertir = compteur;
                boucle_tir = TRUE;
                for (int k=80; k<160 && boucle_tir; k++)
                {
                    if (element[k].init == 0)   //balayage des cases pour les tirs, arrêt du balayage à la première case non initialisé trouvée
                    {
                        element[k].init = 1;
                        element[k].type = 5;
                        element[k].x = element[0].x + 2;
                        element[k].y = element[0].y - 1;
                        boucle_tir = FALSE;
                    }
                }
            }
            break;
    }

    if ((element[1].init == 1) && ((compteur%25 == 0)))   //Si le boss est initialisé, il peut bouger (mais moins vite que le joueur)
    {
            //Les mouvements du boss sont calés sur ceux du joueur, le boss va tenter de suivre le joueur
        if (element[1].x > element[0].x)
        {
            element[1].x--;
            if (element[1].x == 0)
                element[1].x = 1;
        }
        else if (element[1].x < element[0].x)
        {
            element[1].x++;
            if (element[1].x > tab_parametres[1] - 2 - 7)
                element[1].x = tab_parametres[1] - 2 - 7;
        }

        if ((compteur%(delai*2)) == 0)  //Il peut tirer deux tirs en fonction du délai
        {
            boucle_tir = TRUE;
            for (int k=80; k<160 && boucle_tir; k++)    //Balayage pour le premier tir
            {
                if (element[k].init == 0)   //balayage des cases pour les tirs, arrêt du balayage à la première case non initialisé trouvée
                {
                    element[k].init = 1;
                    element[k].type = 6;
                    element[k].x = element[1].x + 2;
                    element[k].y = element[1].y + 1;
                    boucle_tir = FALSE;
                }
            }
            boucle_tir = TRUE;
            for (int k=80; k<160 && boucle_tir; k++)    //Balayage pour le second tir
            {
                if (element[k].init == 0)   //balayage des cases pour les tirs, arrêt du balayage à la première case non initialisé trouvée
                {
                    element[k].init = 1;
                    element[k].type = 6;
                    element[k].x = element[1].x + 4;
                    element[k].y = element[1].y + 1;
                    boucle_tir = FALSE;
                }
            }
        }
    }

    if ((compteur%delai) == 0)
    {   if (element[1].init == 0)   //On initialise aucun autre éléments tant que le boss est initialisé
            initElem(element, i);
        for (int j=2; j<80; j++)    //On passe que sur les éléments qui ont un délai à respecter (pilules, ennemis, bonus, malus)
        {
            if (element[j].init == 1)
            {
                if (element[j].y > (tab_parametres[0] - 7)) //Si il atteint le bord inférieur de la fenetre de jeu
                    element[j].init = 0;    //Désinitialisé/Disparait
                else
                    element[j].y++; //Il descends
            }
        }
    }

    if ((compteur%25) == 0) //Contrôle de la vitesse de déplacement des tirs ami et ennemi
    {
        for (int j=80; j<160; j++) 
        {
            if ((element[j].init == 1) && (element[j].type == 6))   //Si l'élément est initialisé et est un tir ennemi
            {
                if (element[j].y > (tab_parametres[0] - 7)) //Si il atteint le bord inférieur de la fenetre de jeu
                    element[j].init = 0;    //Désinitialisé/Disparait
                else
                    element[j].y++; //Il descends
            }
            else if ((element[j].init == 1) && (element[j].type == 5))   //Si l'élément est initialisé et est un tir ami 
            {
                if (element[j].y <= 1) //Si il atteint le bord supérieur de la fenetre de jeu
                    element[j].init = 0;    //Désinitialisé/Disparait
                else
                    element[j].y--; //Il monte
            }
        }
    }
}



void GestionAff(WINDOW *jeu, data element[], int compteur, int delai)
{
    wattron(jeu, COLOR_PAIR(2));
    mvwprintw(jeu, element[0].y, element[0].x, design_elem[1]);  //affichage du vaisseau
    wattroff(jeu, COLOR_PAIR(2));

if (element[1].init == 1)
    {
        wattron(jeu, COLOR_PAIR(3) | A_UNDERLINE);
        mvwprintw(jeu, element[1].y, element[1].x, design_elem[2]); //Affichage du boss
        wattroff(jeu, COLOR_PAIR(3) | A_UNDERLINE);
    }

    if ((compteur%delai) == 0)
    {
        for (int j=2; j<80; j++)
        {
            if (element[j].init == 1)
            {
                switch (element[j].type)    //Affichage des autres element du jeu
                {
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
    for (int j=80; j<160; j++)
    {
        if (element[j].init == 1)   
        {
            //Présentement affiché avec les couleurs d'interface, penser à changer
            mvwaddch(jeu, element[j].y, element[j].x, ACS_BULLET);  //Affichage des tirs initialisés
        }
    }
}



void GestionEff(WINDOW *jeu, data element[160], int compteur, int delai)
{
        //Effacemement "des traces" du vaisseau lors du déplacement, le vaisseau est réécrit sur la même ligne, on ne fait qu'effacer à gauche et à droite du vaisseau
    mvwprintw(jeu, element[0].y, element[0].x, " ");
    mvwprintw(jeu, element[0].y, element[0].x + 5, " ");

    if (element[1].init == 1)
        mvwprintw(jeu, element[1].y, element[1].x, "       ");  //Effacement du boss  

    if ((compteur%delai) == 0)
    {
        for (int j=2; j<80; j++)
        {
            if (element[j].init == 1);
            {
                if ((element[j].type == 1) || (element[j].type == 2))
                    mvwprintw(jeu, element[j].y, element[j].x, " ");    //Effacement malus bonus
                else if ((element[j].type == 3) || (element[j].type == 4))
                    mvwprintw(jeu, element[j].y, element[j].x, "     ");    //Effacement ennemi pilule
            }
        }
    }
    for (int j=80; j<160; j++)
    {
        if (element[j].init == 1);  //Pas besoin de vérifier le type, les éléments de 30 à 50 sont forcément des tirs, on ne les efface que s'ils sont initialisés/affichés
            mvwprintw(jeu, element[j].y, element[j].x, " ");
    }
}



void GestionCollision(int *pointe_vie, int *pointe_effetJoueur, int *pointe_score, data element[160], int compteur, int delai)
{
    for (int j=2; j<80; j++)    //Balayage éléments
    {
        if ((element[j].init == 1) || (element[1].init == 1))
        {
            for (int k=80; k<100; k++)   //Balayage des tirs (uniquements pour les éléments initialisés)
            {
                if (/*((compteur%25) == 0) && */(element[k].init == 1)) //Verification des collisions entre les tirs initialisés
                {
                    if ((element[k].type == 5) && (element[j].type == 4) && (element[k].y == element[j].y) && (element[k].x >= element[j].x) && (element[k].x <= element[j].x + 5))   //Si un tir ami rentre en collision avec un ennemi
                    {
                        *pointe_score += 5;
                        element[k].init = 0;
                        element[j].init = 0; 
                    }

                    else if ((element[k].type == 5) && (element[j].type != 4) && (element[k].y == element[j].y) && (element[k].x >= element[j].x) && (element[k].x <= element[j].x + 5))   //Si un tir ami rentre en collision avec autre chose qu'un ennemi
                    {
                        element[k].init = 0;
                        element[j].init = 0;
                    }

                    else if ((element[k].type == 6) && (element[k].y == element[0].y) && (element[k].x >= element[0].x) && (element[k].x <= element[0].x + 5))  //Si un tir ennemi rentre en colision avec le vaisseau
                    {
                        *pointe_vie -= 1;
                        element[k].init = 0;

                    }
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



void GestionEffetMalusBonus(int *pointe_effetJoueur, int *pointe_delai, int *pointe_compduree, int *pointe_effetapp, int compteur)
{
        //Debug affichage des booléens des conditions car le délai des effets ne fonctionnent pas
    /*mvprintw(3,3, "%d", (*pointe_compduree <= 5));
    mvprintw(4, 4, "%d", ((compteur%delai) == 0));*/
    switch (*pointe_effetJoueur)
    {
        case 11:    //Acceleration
            if (*pointe_effetapp == FALSE)  //Si l'effet n'est pas appliqué
            {
                *pointe_compduree = compteur;    
                *pointe_delai = *pointe_delai - 25;  //Application de l'effet
                *pointe_effetapp = TRUE;
            }
            if ((compteur - *pointe_compduree) > 5*100)
            {
                *pointe_delai = *pointe_delai + 25;  //Réapplique l'ancienne vitesse
                *pointe_effetapp = FALSE;
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            }
            break;
        
        case 12:    //Inversion des commandes du vaisseau (voir dans GestionMvElem)
            if (*pointe_effetapp == FALSE)  //Si l'effet n'est pas appliqué
            {
                *pointe_compduree = compteur;
                *pointe_effetapp = TRUE;
            }
            if ((compteur - *pointe_compduree) > 15*100)
            {
                *pointe_effetapp = FALSE;
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            }
            break;

        case 21:    //Invincibilité aux ennemis (voir dans GestionCollision)
            if (*pointe_effetapp == FALSE)  //Si l'effet n'est pas appliqué
            {
                *pointe_compduree = compteur;
                *pointe_effetapp = TRUE;
            }
            if ((compteur - *pointe_compduree) > 10*100)
            {
                *pointe_effetapp = FALSE;
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            }
            break;
        
        case 22:    //Canon activé
            if (*pointe_effetapp == FALSE)  //Si l'effet n'est pas appliqué
            {
                *pointe_compduree = compteur;
                *pointe_effetapp = TRUE;
            }
            if ((compteur - *pointe_compduree) > 30*100)
            {
                *pointe_effetapp = FALSE;
                *pointe_effetJoueur = 0;    //Plus aucun effet n'est appliqué
            }
            break;

        case 0: //Aucun effet n'est appliqué
            *pointe_compduree = 0;  //Alors remise à zéro du temps d'application d'un effet
            break;
    }
}



void GestionApparitionBoss(WINDOW *jeu, int *pointe_effetJoueur, int  *pointe_score, int *pointe_delai, int *pointe_compboss, int compteur, data element[160])
{
    const int recurrence=750;   //Valeur de score récurrente pour le dernier boss
    bool boucle_boss=TRUE;  //Controle la sortie de la boucle pour le dernier boss

        //Si aucun boss n'est initialisé, plusieurs boss apparaitront en fonction du score, le dernier boss apparaitra tout les 750 point environ (la possibilité d'un tir sur un ennemi est prise en compte)
    if ((element[1].init == 0) && ((*pointe_score >= 45) && (*pointe_score < 55)) || ((*pointe_score >= 245) && (*pointe_score < 250)))
    {
        *pointe_effetJoueur = 0;
        for (int j=2; j<160; j++)   //Désinitialisation de tout les éléments
            element[j].init = 0;
        element[1].init = 1;
        element[1].y = 1;
        element[1].x = rand()%(tab_parametres[1] - 7 - 2) + 1;
        *pointe_compboss = compteur;          
    }
    else if (element[1].init == 0)  //Si les précédent paliers de scores sont passés et qu'un boss n'est pas initialisé
    {
        for (int n=1; n<99999 && boucle_boss; n++)  //Alors test des multiples de 750 plus ou moins 5 (éventualité d'un tir sur un ennemi)  
        {
            if ((*pointe_score >= (recurrence*n) - 5) && (*pointe_score < (recurrence*n) + 5))
            {
                boucle_boss = FALSE;
                *pointe_effetJoueur = 0;
                for (int j=2; j<160; j++)   //Désinitialisation de tout les éléments
                    element[j].init = 0;
                element[1].init = 1;
                element[1].y = 1;
                element[1].x = rand()%(tab_parametres[1] - 7 - 2) + 1;
                *pointe_compboss = compteur;
            }

        }
    } 

        //Condition de disparition des boss en fonction du délai, gère aussi le bonus de score
    if ((*pointe_delai == 200) && ((compteur - *pointe_compboss) > 20*100) && (element[1].init == 1)) //20 en seconde et 100 le nombre de tours de boucle necéssaire pour 1s (uniquement si on a un délai de 200)
    {
        *pointe_score *= 1.1;
        *pointe_delai = 100;    //Mise en place du nouveau délai
        mvwprintw(jeu, element[1].y, element[1].x, "       ");  //Effacement du boss
        element[1].init = 0;    //Le boss disparait au bout de 20s
    }

    if ((*pointe_delai == 100) && ((compteur - *pointe_compboss) > 60*100) && (element[1].init == 1)) //60 en seconde et 100 le nombre de tours de boucle necéssaire pour 1s (uniquement si on a un délai de 100)
    {
        *pointe_score *= 1.2;
        *pointe_delai = 50;    //Mise en place du nouveau délai
        mvwprintw(jeu, element[1].y, element[1].x, "       ");  //Effacement du boss
        element[1].init = 0;    //Le boss disparait au bout de 1min
    }

    if ((*pointe_delai == 50) && ((compteur - *pointe_compboss) > 90*100) && (element[1].init == 1)) //90 en seconde et 100 le nombre de tours de boucle necéssaire pour 1s (uniquement si on a un délai de 100)
    {
        *pointe_score *= 1.4;
        mvwprintw(jeu, element[1].y, element[1].x, "       ");  //Effacement du boss
        mvprintw(1, 1, "boss 3");
        element[1].init = 0;    //Le boss disparait au bout de 1min30
    }
}