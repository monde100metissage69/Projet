#include "avl.h"

typedef struct NoeudAVL {
    int id_station;                // Identifiant de la station
    double capacite;               // Capacité en kWh
    double consommation_totale;    // Somme des consommations
    int hauteur;                   // Hauteur du nœud
    struct NoeudAVL *gauche, *droite;
} NoeudAVL;

// Crée un nouveau nœud
NoeudAVL* creerNoeud(int id, double capacite, double consommation) {
    NoeudAVL* noeud = (NoeudAVL*)malloc(sizeof(NoeudAVL));
    noeud->id_station = id;
    noeud->capacite = capacite;
    noeud->consommation_totale = consommation;
    noeud->hauteur = 1;
    noeud->gauche = noeud->droite = NULL;
    return noeud;
}

// Retourne la hauteur d'un nœud
int obtenirHauteur(NoeudAVL* noeud) {
    return noeud ? noeud->hauteur : 0;
}

// Retourne le facteur d'équilibre
int obtenirEquilibre(NoeudAVL* noeud) {
    return noeud ? obtenirHauteur(noeud->gauche) - obtenirHauteur(noeud->droite) : 0;
}

// Effectue une rotation droite
NoeudAVL* rotationDroite(NoeudAVL* y) {
    NoeudAVL* x = y->gauche;
    NoeudAVL* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = 1 + (obtenirHauteur(y->gauche) > obtenirHauteur(y->droite) ? obtenirHauteur(y->gauche) : obtenirHauteur(y->droite));
    x->hauteur = 1 + (obtenirHauteur(x->gauche) > obtenirHauteur(x->droite) ? obtenirHauteur(x->gauche) : obtenirHauteur(x->droite));

    return x;
}

// Effectue une rotation gauche
NoeudAVL* rotationGauche(NoeudAVL* x) {
    NoeudAVL* y = x->droite;
    NoeudAVL* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = 1 + (obtenirHauteur(x->gauche) > obtenirHauteur(x->droite) ? obtenirHauteur(x->gauche) : obtenirHauteur(x->droite));
    y->hauteur = 1 + (obtenirHauteur(y->gauche) > obtenirHauteur(y->droite) ? obtenirHauteur(y->gauche) : obtenirHauteur(y->droite));

    return y;
}

// Insère un nœud dans l'AVL
NoeudAVL* inserer(NoeudAVL* noeud, int id, double capacite, double consommation) {
    if (!noeud) return creerNoeud(id, capacite, consommation);

    if (id < noeud->id_station)
        noeud->gauche = inserer(noeud->gauche, id, capacite, consommation);
    else if (id > noeud->id_station)
        noeud->droite = inserer(noeud->droite, id, capacite, consommation);
    else {
        noeud->consommation_totale += consommation;
        return noeud;
    }

    noeud->hauteur = 1 + (obtenirHauteur(noeud->gauche) > obtenirHauteur(noeud->droite) ? obtenirHauteur(noeud->gauche) : obtenirHauteur(noeud->droite));

    int equilibre = obtenirEquilibre(noeud);

    if (equilibre > 1 && id < noeud->gauche->id_station)
        return rotationDroite(noeud);

    if (equilibre < -1 && id > noeud->droite->id_station)
        return rotationGauche(noeud);

    if (equilibre > 1 && id > noeud->gauche->id_station) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }

    if (equilibre < -1 && id < noeud->droite->id_station) {
        noeud->droite = rotationDroite(noeud->droite);
        return rotationGauche(noeud);
    }

    return noeud;
}

// Parcourt l'AVL et écrit les résultats
void ecrireResultats(NoeudAVL* racine, FILE* sortie) {
    if (!racine) return;
    ecrireResultats(racine->gauche, sortie);
    fprintf(sortie, "%d;%lf;%lf\n", racine->id_station, racine->capacite, racine->consommation_totale);
    ecrireResultats(racine->droite, sortie);
}

// Libère la mémoire de l'AVL
void libererArbre(NoeudAVL* racine) {
    if (!racine) return;
    libererArbre(racine->gauche);
    libererArbre(racine->droite);
    free(racine);
}

