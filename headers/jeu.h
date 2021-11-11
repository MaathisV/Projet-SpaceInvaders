/*jeu.h
Prototype des fonctions de jeu*/


/*FONCTION Jouer() : Démarre une partie, initialise l'interface et appelle les fonctions de déplacement et d'affichage
Entrees/Sorties : néant*/
void Jouer();


/*FONCTION GestionMvElem() : Gere les déplacements des élements ; modifie les valeurs d'abscisses et d'ordonnées
Entrees : clavier (récupère la touche pressé par l'utilisateur), compteur (compte le nombre d'itération de la boucle de jeu)
Sorties : néant */
void GestionMvElem(int clavier, int pos_elem[], int compteur);


/*FONCTION Pause() : Met en pause l'execution du programme
Entrees : néant
Sorties : néant */
void Pause();


/*FONCTION GestionAff() : Gère l'affichage des elements du jeu
Entrees : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itération de la boucle de jeu)
Sorties : néant */
void GestionAff(WINDOW *jeu, int pos_elem[], int compteur);


/*FONCTION GestionEff() : Gère l'effacement des elements du jeu
Entrees : jeu (fenêtre ncurses dans laquelle sera affichée les éléments)
Entrees/Sorties : pos_elem (tableau contenant les coordonnées de tout les éléments du jeu)
Sorties : néant */
void GestionEff(WINDOW *jeu, int pos_elem[]);