#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Station {
    int id;
    int capacite;
    long consommation;
} Station;
typedef struct avl {
    struct Station s;
    struct avl *fg;
    struct avl *fd;
    int equilibre;
} avl;
avl *creerAVL(Station s, int capacite, long consommation);
int max(int a, int b);
int min(int a, int b, int c);
int min2(int a, int b);
int max2(int a, int b, int c);
avl *rotationGauche(avl *a);
avl *rotationDroite(avl *a);
avl *doubleRotationGauche(avl *a);
avl *doubleRotationDroite(avl *a);
avl *equilibrerAVL(avl *a);
avl *rechercherAVL(avl *a, int idstation);
avl *insererAVL(avl *a, Station s, int capacite, long consommation, int *h);
void traiter(avl *a, FILE *fichier);
void parcoursPrefixe(avl *a, FILE* fichier);
void Remplirlefichier(avl *a, FILE *fichier);

#endif
