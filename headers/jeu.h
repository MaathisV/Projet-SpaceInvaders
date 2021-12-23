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


typedef struct score score;
struct score
{
    char pseudo;
    int score;
};


/*FONCTION Regles() : Affiche les règles du jeu, les contrôles et autres informations (lore, etc)
Entrées/Sorties : néant*/
void Regles();


/*FONCTION Jouer() : Démarre une partie, initialise l'interface et appelle les fonctions de déplacement et d'affichage
Entrées/Sorties : néant*/
void Jouer();


/*Fonction DebutPartie() : setup le début de partie en demandant le nom du joueur et le nombre de vie de départ
Entrées/Sorties : joueur (tableau des scores)
Sorties : selection_vie (retourne le nombre de vies sélectionnés par l'utilisateur)*/
int DebutPartie(score joueur[11]);


/* Fonction AffichageCompteur() : affiche le compteur de départ
Entrées/Sorties : néant */
void AffichageCompteur();


/* Fonction MajAffInterface() : met à jour l'interface du jeu
Entrées : vie (vie du joueur), score (score du joueur), effetJoueur (le joueur est affecté par un bonus ou malus)
Sorties : néant */
void MajAffInterface(int vie, int score, int effetJoueur);


/*FONCTION Pause() : Met en pause l'exécution du programme
Entrées : néant
Sorties : si ressort -1 alors quitte la partie */
int Pause();


/*Fontion Tirage() : Tire un nombre aléatoire qui détermine le prochain élement à apparaitre
Entrées : néant
Sorties : element (désigne l'élément à apparaitre) */
int Tirage();


/*Fonction initElem() : initialise les données (position et type) de chaque élement qui n'est pas initialisé
Entrées : i (indice de la case du tableau element)
Entrées/Sorties : element (tableau contenant les données de chaque élements) */
void initElem(data element[50], int i);


/*FONCTION GestionMvElem() : Gère les déplacements des élements ; modifie les valeurs d'abscisses et d'ordonnées
Entrées : clavier (récupère la touche pressé par l'utilisateur), *pointe_effetJoueur (pointe effetJoueur pour savoir si le malus d'inversion est actif), compteur (compte le nombre d'itération de la boucle de jeu), i (indice de la case du tableau element)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionMvElem(int clavier, data element[50], int *pointe_effetJoueur, int compteur, int i);


/*FONCTION GestionAff() : Gère l'affichage des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itération de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionAff(WINDOW *jeu, data element[50], int compteur, int i);


/*FONCTION GestionEff() : Gère l'effacement des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itérations de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionEff(WINDOW *jeu, data element[50], int compteur);


/* Fonction GestionCollision() : Gère les différentes collisions vaisseau/éléments
Entrées : *pointe_vie (pointeur sur la variable vie), *pointe_effetJoueur (pointeur, désigne l'état positif ou négatif affecté au vaisseau), compteur (nombre d'itération de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionCollision(int *pointe_vie, int *pointe_effetJoueur, data element[], int compteur);


/* Fonction GestionEffetMalusBonus() : Gere les effets des malus et des bonus (durées des effets, effet appliqué)
Entrées : *pointe_effetJoueur (pointeur sur la variable effetJoueur, permet de déterminer l'effet à appliquer), *pointe_delai (pointeur sur la variable delai, permet de modifier la vitesse des éléments), *pointe_duree (pointeur de la variable duree), compteur (compte le nombre d'itérations de la boucle de jeu)
Sorties : néant */
void GestionEffetMalusBonus(int *pointe_effetJoueur, int *pointe_delai, int *pointe_duree, int compteur);


#endif