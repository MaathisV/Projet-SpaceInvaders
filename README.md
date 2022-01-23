# Projet-SpaceInvaders

Le projet Space Invaders est un projet réalisé en language C durant le premier semestre d'étude en GEII.
Il fallait concevoir un jeu de type Space Invaders jouable dans le terminal.
On utilise donc la bibliothèque *ncurses.h* pour gérer les positionnements et les couleurs de ce qui s'affiche sur le terminal. La bibliothèque utilisé est exclusive Linux, le programme ne fonctionne pas sous Windows ou Mac OS.

L'utilisateur peut donc déplacer un vaisseau latératement sur l'écran dans le but d'éviter ou de ramasser les différents éléments qui descendent vers lui.
Le joueur doit éviter les ennemis et ramasser les pilules. Il peut être affecté par différents malus et bonus si il rentre en collisions avec eux.



## Compilation du projet
Le projet est compilable avec GCC.
On utilise la commande qui suit : ``gcc - o projet main.c -lncurses``
Le fichier compilé peut être exécuté avec : ``./projet``