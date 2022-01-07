/*scores.h
Prototypes des fonction de gestion des scores
*/


#ifndef HEADERS_SCORES
#define HEADERS_SCORES

/*Structure stockant pseudo et score des 10 meilleurs scores. Le score et le pseudo de la partie en cours sont stockés dans la dernière case du tableau */
typedef struct score score;
struct score
{
    char pseudo[14];
    int score;
};



/* Fonction SauvScore() : sauvegarde le tableau global joueur dans le fichier classement
Entrées/Sorties : néant */
void SauvScore();


/* Fonction AffScore() : Affiche le tableau des scores, c'est à dire les 10 meilleurs scores
Entrées/Sorties : néant */
void AffScore();


/* Fonction InitScore() : initialise le tableau global joueur à partir du fichier classement
Entrées/Sorties : néant */
void InitScore();


/* Fonction TriScore() : tri le tableau global joueur de manière croissante en fonction du score
Entrées/Sorties : néant */
void TriScore();

#endif