/*terminal.h
Prototype des fonctions pour la mise en forme du terminal */


#ifndef HEADERS_TERMINAL
#define HEADERS_TERMINAL

/*Choix et initialisation des couleurs des différents élements à afficher
Entrées/Sorties : néant */ 
void color();


/*Fonction qui récupère la touche pressée sans mettre en pause l'exécution
Entrées : néant
Sorties : néant*/
char nb_getch();
char nb_wgetch(WINDOW* fenetre);   //Dans le cas où l'on veut récupérer une saisie dans une fenêtre, on ajoute aussi le parametre fenetre


/*Fonction qui récupère la touche pressée en mettant en pause l'exécution
Entrées : néant
Sorties : néant*/
char b_getch();
char b_wgetch(WINDOW* fenetre);   //Dans le cas où l'on veut récupérer une saisie dans une fenêtre, on ajoute aussi le parametre fenetre


/*Fonction d'initialisation de l'écran
Entrées : néant
Sorties : néant*/
void startscr();


/*Fonction de récupération des dimensions du terminal
Entrées : néant
Sorties : néant */
void dim_terminal();

/*Fonction qui définit les couleurs du jeu à une certaine valeur
Entrées/Sorties : néant*/ 
void DefautCouleurs();


/* Fonction d'initialisation du tableau des paramètres et du tableau des scores
Entrées/Sorties : néant*/
void InitTabs();


/*Fonction permettant la saisie validée d'un chaine de caractères alphanumériques
Entrées : *fenetre (fenetre ncurses dans laquelle sera effectuée la saisie), y (ordonnées de la saisie), x (abscisse de la saisie), longueur (précise la longeur de la chaine), validation (indique si on attends une validation de la saisie par la touche entrée)
Entrées/Sorties : chaine (tableau de char dans lequel la saisie sera effectuée)
Sorties : néant */
void SaisieChaine(WINDOW *fenetre, int y, int x, char chaine[], int longueur, bool validation);

#endif