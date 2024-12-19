#include "avl.h"
typedef struct Station {
    int id;
    int capacite;
    long consommation;
} Station;

typedef struct avl {
    Station s; 
    struct avl* fg;
    struct avl* fd;
    int equilibre;
} avl;

avl * creerAVL(int s, int capacite, long consommation){
    avl* nouveau = malloc(sizeof(avl));
    if(nouveau == NULL) {
        exit(1);
    }
    nouveau->s.id = s;
    nouveau->s.capacite = capacite;
    nouveau->s.consommation = consommation;
    nouveau->equilibre = 0;
    nouveau->fg = NULL;
    nouveau->fd = NULL;

    return nouveau;
}
avl* insererAVL(avl* a, int s, int capacite, long consommation, int *h) {
    if(a == NULL){
        *h = 1;
        return creerAVL(s, capacite, consommation);
    }
    else if(s < a->s.id){
        a->fg = insererAVL(a->fg, s, capacite, consommation, h);
    }
    else if(s > a->s.id){
        a->fd = insererAVL(a->fd, s, capacite, consommation, h);
    }
    else{
        *h = 0; 
        a->s.consommation += consommation;
        a->s.capacite += capacite;
        return a;
    }
    if(*h != 0){
        a->equilibre += *h;
        a = equilibrerAVL(a); 
        if(a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}
