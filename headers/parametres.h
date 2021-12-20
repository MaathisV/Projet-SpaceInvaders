/*parametres.h
Prototypes des fonctions de paramètrage de l'application par l'utilisateur (mode de jeu, couleur, etc) */


#ifndef HEADERS_PARAM
#define HEADERS_PARAM

/*FONCTION Fct_Parametres() : Gère l'aiguillage dû au choix du menu des Paramètres 
Entrées : option (choix de l'utilisateur dans le menu des parametres)
Sorties : néant*/
void Fct_Parametres(int option);


/*Fonction ModifCouleurs() : permet de modifier les couleurs de fond et de caractères de tout les éléments du jeu, y compris l'interface
Entrées/Sorties : néant */
void ModifCouleurs();


/*Fonction ModifDesign() : permet de modifier les caractères de chaque éléments du jeu (vaisseau joueur, BOSS, ennemis, pilules, malus, bonus)
Entrées/Sorties : néant */
void ModifDesign();

#endif