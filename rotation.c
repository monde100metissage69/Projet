#include "rotation.h"

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

    a->equilibre = eq_a - min2(eq_p, 0) +1; 
    pivot->equilibre = max2(eq_a+2, eq_a + eq_p+2, eq_p+1);

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
        if(a-> 0){fd->equilibre >=0){
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
