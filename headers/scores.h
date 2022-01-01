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



//Fonctions d'enregistrement et de classement des scores

#endif