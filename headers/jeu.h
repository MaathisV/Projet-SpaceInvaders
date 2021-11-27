/*jeu.h
Prototype des fonctions de jeu*/


#ifndef HEADERS_JEU
#define HEADERS_JEU

/*FONCTION Jouer() : Démarre une partie, initialise l'interface et appelle les fonctions de déplacement et d'affichage
Entrées/Sorties : néant*/
void Jouer();


/*FONCTION Pause() : Met en pause l'exécution du programme
Entrées : néant
Sorties : néant */
void Pause();


/*Fontion Tirage() : Tire un nombre aléatoire qui détermine le prochain élement à apparaitre
Entrées : néant
Sorties : element (désigne l'élément à apparaitre) */
int Tirage();


/*Structure définissant les coordonnées et le type de chaque élément (défini par la fonction Tirage) à l'écran. Ces données sont stockées dans le tableau element */
typedef struct data data; 
struct data
{
    int x;
    int y;
    int type;
    
};


/*FONCTION GestionMvElem() : Gère les déplacements des élements ; modifie les valeurs d'abscisses et d'ordonnées
Entrées : clavier (récupère la touche pressé par l'utilisateur), compteur (compte le nombre d'itération de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionMvElem(int clavier, data element[50], int compteur);


/*FONCTION GestionAff() : Gère l'affichage des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itération de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionAff(WINDOW *jeu, data element[50], int compteur);


/*FONCTION GestionEff() : Gère l'effacement des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itérations de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionEff(WINDOW *jeu, data element[50], int compteur);


//int GestionCollision(, int vie);

#endif