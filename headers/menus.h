/*menu.h
Prototype des fonctions qui gèrent les différents menus du programme*/


#ifndef HEADERS_MENU
#define HEADERS_MENU

/*FONCTION ChoixMenuPrincipal() : Récupère le choix de l'utilisateur 
Entrées : néant
Sorties : select (choix de l'utilisateur ; (0:Jouer, 1: Règles, 2:Paramètres, 3:Scores, 4:Quitter))*/
int ChoixMenuPrincipal();


/*FONCTION ChoixMenuParametres() : Récupère le choix de l'utilisateur 
Entrées : néant
Sorties : select (choix de l'utilisateur ; (Changer les couleurs", "Changer le design des éléments", "Mettre à jour la taille du terminal","Réinitialiser les scores", "Rentrer un mot de passe", "Retour))*/
int ChoixMenuParametres();

#endif