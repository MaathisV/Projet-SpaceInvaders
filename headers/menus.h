/*menu.h
Prototype des fonctions qui gèrent les différents menus du programme*/

/*FONCTION ChoixMenuPrincipal() : Récupère le choix de l'utilisateur 
Entrées/Sorties : tab_parametres (tableau de parametres du programme)
Sorties : select (choix de l'utilisateur ; (0:Jouer, 1: Règles, 2:Paramètres, 3:Scores, 4:Quitter))*/
int ChoixMenuPrincipal(int tab_parametres[]);


/*FONCTION ChoixMenuParametres() : Récupère le choix de l'utilisateur 
Entrées/Sorties : tab_parametres (tableau de parametres du programme)
Sorties : select (choix de l'utilisateur ; (0:Jouer, 1: Règles, 2:Paramètres, 3:Scores, 4:Quitter))*/
int ChoixMenuParametres(int tab_parametres[]);
