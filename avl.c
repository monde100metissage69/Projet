#include "avl.h"

struct Station {
    int* station;
    int *capacite;
    long *consommation;
};

struct avl {
    struct Station *station; 
    struct avl* fg;
    struct avl* fd;
    int equilibre;
};

typedef avl* parbre;

parbre creerAVL(int station, int capacite, long consommation){
    parbre nouveau = malloc(sizeof(parbre));
    if(nouveau == NULL){
        exit(1);
    }
    nouveau->station = station;
    nouveau->equilibre = 0;
    nouveau->consommation = consommation;
    nouveau->capacite = capacite; 
    nouveau->fg = NULL;
    nouveau->fd = NULL;

    return nouveau;
}
int max(int a, int b){
    if(a >= b){
        return a;
    else  {
        return b;
    }
int min(int a, int b, int c){
    int min = a;

    if(b < min){
        min = b;
    }
    if(c < min){
        min = c;
    }
    return min;
}

parbre rotationGauche(parbre a){
    parbre pivot;
    int eq_a, eq_p;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;

    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - max(eq_p, 0) -1;
    pivot->equilibre = min(eq_a-2, eq_a + eq_p-2, eq_p-1);

    a = pivot;
    return a;

}

parbre rotationDroite(parbre a){
    parbre pivot;
    int eq_a, eq_p;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;

    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - min(eq_p, 0) +1; 
    pivot->equilibre = max(eq_a+2, eq_a + eq_p+2, eq_p+1);

    a = pivot;
    return a;
}

parbre doubleRotationGauche(parbre a){
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

parbre doubleRotationDroite(parbre a){
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

parbre equilibrerAVL(parbre a){
    if(a->equilibre >= 2){
        if(a->fd->equilibre >=0){
            return rotationGauche(a);
        }
        else{
            return doubleRotationGauche(a);
        }
    }
    else if(a->equilibre <= -2){
        if(a->fg->equilibre <= 0){
            return rotationDroite(a);
        }
        else{
            return doubleRotationDroite(a);
        }
    }
    return a;
}
    
parbre insererAVL(parbre a, int station, int capacite, long consommation, int *h){
    if(a == NULL){
        *h = 0;
        return creerAVL(station, capacite, consommation);
    }
    else if(station < a->station){
        a->fg = insererAVL(a->fg, station, capacite, consommation h);
        *h = -*h;
    }
    else if(station > a->station){
        a->fd = insererAVL(a->fd, station, capacite, consommation, h);
    }
    else{
        *h = 0;
        a->consommation += consommation;
        a->capacite += capacite;
        return a;
    }
    if {
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

