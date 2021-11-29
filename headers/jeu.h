/*jeu.h
Prototype des fonctions de jeu*/


#ifndef HEADERS_JEU
#define HEADERS_JEU

/*Structure définissant les coordonnées et le type de chaque élément (défini par la fonction Tirage) à l'écran. Ces données sont stockées dans le tableau element */
typedef struct data data; 
struct data
{
    int x;  //Abscisse x de l'élement
    int y;  //Ordonnées y de l'élément
    int type;
    int init;   //Etat de l'élément (initialisé ou non)
};


/*FONCTION Jouer() : Démarre une partie, initialise l'interface et appelle les fonctions de déplacement et d'affichage
Entrées/Sorties : néant*/
void Jouer();


/* Fonction MajAffInterface() : met à jour l'interface du jeu
Entrées : vie (vie du joueur), score (score du joueur), etat (le joueur est affecté par un bonus ou malus)
Sorties : néant */
void MajAffInterface(int vie, int score, int etat);


/*FONCTION Pause() : Met en pause l'exécution du programme
Entrées : néant
Sorties : néant */
void Pause();


/*Fontion Tirage() : Tire un nombre aléatoire qui détermine le prochain élement à apparaitre
Entrées : néant
Sorties : element (désigne l'élément à apparaitre) */
int Tirage();


/*Fonction initElem() : initialise les données (position et type) de chaque élement qui n'est pas initialisé
Entrées : i (indice de la case du tableau element)
Entrées/Sorties : element (tableau contenant les données de chaque élements) */
void initElem(data element[50], int i);


/*FONCTION GestionMvElem() : Gère les déplacements des élements ; modifie les valeurs d'abscisses et d'ordonnées
Entrées : clavier (récupère la touche pressé par l'utilisateur), compteur (compte le nombre d'itération de la boucle de jeu), i (indice de la case du tableau element)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionMvElem(int clavier, data element[50], int compteur, int i);


/*FONCTION GestionAff() : Gère l'affichage des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itération de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionAff(WINDOW *jeu, data element[50], int compteur, int i);


/*FONCTION GestionEff() : Gère l'effacement des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itérations de la boucle de jeu), i (indice de la case du tableau element)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionEff(WINDOW *jeu, data element[50], int compteur, int i);


int GestionCollision(int vie);


#endif