#include "avl.h"


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
int max(int a, int b){
    if(a >= b){
        return a;
    }
    else {
        return b;
    }
}cwire_exec;
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
avl* rotationGauche(avl* a){
    avl *pivot;
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
avl* rotationDroite(avl *a){
    avl *pivot;
    int eq_a, eq_p;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;

    eq_a = a->equilibre;
    eq_p = pivot->equilibre;

    a->equilibre = eq_a - max(eq_p, 0) +1; 
    pivot->equilibre = min(eq_a+2, eq_a + eq_p+2, eq_p+1);

    a = pivot;
    return a;
}
avl* doubleRotationGauche(avl* a){
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}
avl* doubleRotationDroite(avl* a){
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}
avl* equilibrerAVL(avl* a){
    if(a->equilibre >= 2){
            if(a->fd->equilibre >= 0){
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

