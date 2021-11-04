/*terminal.h
Prototype des fonctions pour la mise en forme du terminal */


/*Choix des couleurs de la police et de la fenêtre CONSOLE
    cT correspond a la couleur du texte
    cF correspond a la couleur de fond
    Codes couleus :
        0: noir
        1: bleu fonce
        2: vert
        3: bleu-gris
        4: marron
        5: pourpre
        6: kaki
        7: gris clair
        8: gris
        9: bleu
        10: vert fluo
        11: turquoise
        12: rouge
        13: rose fluo
        14: jaune fluo
        15: blanc               */
void color(int cT,int cF);


/*Fonction qui récupère la touche pressée sans mettre en pause l'exécution
Entrées : néant
Sorties : néant*/
char nb_getch();


/*Fonction qui récupère la touche pressée en mettant en pause l'exécution
Entrées : néant
Sorties : néant*/
char b_getch();


/*Fonction d'initialisation de l'écran
Entrées : néant
Sorties : néant*/
void startscr();


/*Fonction de récupération des dimensions du terminal
Entrées/Sorties : tab_parametres[] (tableau de parametres du programme) */
int dim_terminal(int tab_parametres[]);