/*parametres.h
Prototypes des fonctions de paramètrage de l'application par l'utilisateur (mode de jeu, couleur, etc) */


/*FONCTION Fct_Parametres() : Gère l'aiguillage dû au choix du menu des Paramètres 
Entrées : dimensions y et x du terminal,
Sorties : select (choix de l'utilisateur ; (0:Jouer, 1: Règles, 2:Paramètres, 3:Scores, 4:Quitter))*/
void Fct_Parametres(int option, int tab_parametres[]);