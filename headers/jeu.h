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
    int type;   //Determine ce qu'est l'élément (1: malus, 2: bonus, 3: pilule, 4: ennemi, 5: tir ami, 6: tir ennemi)
    int init;   //Etat de l'élément (initialisé ou non)
    //Exeption : pour le boss (case1), 0=non initialisé et 1,2,3 indique quel boss est apparu. En fonction de quoi le score et la vitesse augmentent différemment
};



/*FONCTION Jouer() : Démarre une partie, initialise l'interface et appelle les fonctions de déplacement et d'affichage
Entrées/Sorties : néant*/
void Jouer();


/*Fonction DebutPartie() : setup le début de partie en demandant le nom du joueur et le nombre de vie de départ
Entrées : néant
Sorties : selection_vie (retourne le nombre de vies sélectionnés par l'utilisateur)*/
int DebutPartie();


/*FONCTION Regles() : Affiche les règles du jeu, les contrôles et autres informations (lore, etc)
Entrées/Sorties : néant*/
void Regles();


/* Fonction AffichageCompteur() : affiche le compteur de départ
Entrées/Sorties : néant */
void AffichageCompteur();


/* Fonction MajAffInterface() : met à jour l'interface du jeu
Entrées : vie (vie du joueur), score (score du joueur), effetJoueur (le joueur est affecté par un bonus ou malus), compduree (contient la valeur de compteur depuis laquelle l'effet est actif), avec compteur permet l'affichage de la barre d'effet
Entrées/Sorties : element (tableau contenant les données de chaque élements) 
Sorties : néant */
void MajAffInterface(data element[160], int vie, int score, int effetJoueur, int compduree, int compteur);


/*FONCTION Pause() : Met en pause l'exécution du programme
Entrées : néant
Sorties : si ressort -1 alors quitte la partie */
int Pause();


/*Fonction initElem() : initialise les données (position et type) de chaque élement qui n'est pas initialisé (les éléments sont malus, bonus, pilules et ennemis)
Entrées : i (indice de la case du tableau element)
Entrées/Sorties : element (tableau contenant les données de chaque élements) */
void initElem(data element[160], int i);


/*Fontion Tirage() : Tire un nombre aléatoire qui détermine le prochain élement à apparaitre
Entrées : néant
Sorties : element (désigne l'élément à apparaitre) */
int Tirage();




/*FONCTION GestionMvElem() : Gère les déplacements des élements ; modifie les valeurs d'abscisses et d'ordonnées
Entrées : clavier (récupère la touche pressé par l'utilisateur), *pointe_effetJoueur (pointe effetJoueur pour savoir si le malus d'inversion est actif), *pointe_derniertir (pointe derniertir pour savoir si le délai entre deux tirs est écoulé), compteur (compte le nombre d'itération de la boucle de jeu), i (indice de la case du tableau element)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionMvElem(int clavier, data element[160], int *pointe_effetJoueur, int *pointe_derniertir, int compteur, int delai, int i);


/*FONCTION GestionAff() : Gère l'affichage des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itération de la boucle de jeu), delai (controle les vitesse des éléments)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionAff(WINDOW *jeu, data element[160], int compteur, int delai);


/*FONCTION GestionEff() : Gère l'effacement des élements du jeu
Entrées : jeu (fenêtre ncurses dans laquelle sera affichée les éléments), compteur (compte le nombre d'itérations de la boucle de jeu), delai (controle les vitesse des éléments)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionEff(WINDOW *jeu, data element[160], int compteur, int delai);


/* Fonction GestionCollision() : Gère les différentes collisions vaisseau/éléments
Entrées : *pointe_vie (pointeur sur la variable vie), *pointe_effetJoueur (pointeur, désigne l'état positif ou négatif affecté au vaisseau), *pointe_score (pointe la variable score), compteur (nombre d'itération de la boucle de jeu), delai (controle les vitesse des éléments)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionCollision(int *pointe_vie, int *pointe_effetJoueur, int *pointe_score, data element[160], int compteur, int delai);


/* Fonction GestionEffetMalusBonus() : Gere les effets des malus et des bonus (durées des effets, effet appliqué)
Entrées : *pointe_effetJoueur (pointeur sur la variable effetJoueur, permet de déterminer l'effet à appliquer), *pointe_delai (pointeur sur la variable delai, permet de modifier la vitesse des éléments), *pointe_compduree (pointeur sur la variable compduree), pointe_effetapp (pointeur sur effetapp, permet de savoir si un effet est en cours d'application), compteur (compte le nombre d'itérations de la boucle de jeu)
Sorties : néant */
void GestionEffetMalusBonus(int *pointe_effetJoueur, int *pointe_delai, int *pointe_compduree, int *pointe_effetapp, int compteur);


/* Fonction GestionApparitionBoss() : Gère l'apparition des boss en fonctions du score, s'occupe également des changements de score ou de délai liés
Entrées : jeu (fenêtre ncurses dans laquelle seront affichés les éléments), *pointe_effetJoueur (pointeur, désigne l'état positif ou négatif affecté au vaisseau), *pointe_score (pointe la variable score), *pointe_delai (pointeur sur la variable délai), *pointe_compboss (pointeur sur compboss), compteur (compte le nombre d'itérations de la boucle de jeu)
Entrées/Sorties : element (tableau contenant les données de chaque élements)
Sorties : néant */
void GestionApparitionBoss(WINDOW *jeu, int *pointe_effetJoueur, int  *pointe_score, int *pointe_delai, int *pointe_compboss, int compteur, data element[160]);


/*Fonction GameOver() : Affiche la fenêtre de GameOver et les stats de la partie
Entrées : compteur (compte le nombre d'intération de la boucle de jeu), score (score de la partie)
Sorties : néant */
void GameOver(int compteur, int score);

#endif