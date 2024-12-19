#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Station;
struct avl;
avl *creerAVL(int s, int capacite, long consommation);
avl *rotationGauche(avl* a);
avl *rotationDroite(avl *a);
avl *doubleRotationGauche(avl* a);
avl* doubleRotationDroite(avl* a);
avl* equilibrerAVL(avl* a);
avl* insererAVL(avl* a, int s, int capacite, long consommation, int *h);

#endif
