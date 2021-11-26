/*jeu.h
Prototype des fonctions de jeu*/


/*FONCTION Jouer() : Démarre une partie, initialise l'interface et appelle les fonctions de déplacement et d'affichage
Entrees/Sorties : néant*/
void Jouer();


/*FONCTION Pause() : Met en pause l'execution du programme
Entrees : néant
Sorties : néant */
void Pause();


/*Fontion Tirage() : tire un nombre aléatoire qui détermine le prochain élement à apparaitre
Entrees : néant
Sorties : element (désigne l'élément à apparaitre) */
int Tirage();


typedef struct data data; 
struct data
{
    int x;
    int y;
    int type;
    
};


/*FONCTION GestionMvElem() : Gere les déplacements des élements ; modifie les valeurs d'abscisses et d'ordonnées
Entrees : clavier (récupère la touche pressé par l'utilisateur), element (valeur correspondant à l'élément a apparaitre), compteur (compte le nombre d'itération de la boucle de jeu)
Entrees/Sorties : pos_elem (tableau contenant les coordonnées de tout les éléments du jeu)
Sorties : néant */
void GestionMvElem(int clavier, data element[50], int compteur);


/*FONCTION GestionAff() : Gère l'affichage des elements du jeu
Entrees : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), element (valeur correspondant à l'élément a apparaitre), compteur (compte le nombre d'itération de la boucle de jeu)
Entrees/Sorties : pos_elem (tableau contenant les coordonnées de tout les éléments du jeu)
Sorties : néant */
void GestionAff(WINDOW *jeu, data element[50], int compteur);


/*FONCTION GestionEff() : Gère l'effacement des elements du jeu
Entrees : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itérations de la boucle de jeu), element (valeur correspondant à l'élément a apparaitre)
Entrees/Sorties : pos_elem (tableau contenant les coordonnées de tout les éléments du jeu)
Sorties : néant */
void GestionEff(WINDOW *jeu, data element[50], int compteur);


//int GestionCollision(, int vie);