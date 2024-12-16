#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <limits.h>
#include <ctype.h>

struct Station;
struct avl;
parbre creerAVL(int station, int capacite, long consommation);
int max(int a, int b):
int min(int a, int b, int c);
parbre rotationGauche(parbre a);
parbre rotationDroite(parbre a);
parbre doubleRotationGauche(parbre a);
parbre doubleRotationDroite(parbre a);

#endif
