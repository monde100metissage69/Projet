#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier.h"
#include "avl.h"

Station* creerStation(int id, int capacite, long consommation){
       Station *s;
       s->id = idstation;
       s->capacite = capacite;
       s->consommation = consommation;
       a = insererAVL(a, *s, capacite, consommation, &h);
       return s;
}
void lectureFichier(const char *nomFichier, avl *a) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        exit(1);
    }
    char ligne[150];
    int idstation;
    int capacite;
    long consommation;
    if (fgets(ligne, 150, fichier) == NULL){
        fclose(fichier);
        printf("Erreur le fichier est vide :");
        exit(1);
    }
    while (fgets(ligne, 150, fichier) != NULL) {
        if (sscanf(ligne, "%d;%d;%ld", &idstation, &capacite, &consommation) == 3) {
            if (capacite < 0){ 
                capacite = 0;
            }
            if (consommation < 0){
                consommation = 0;
            }
            avl *noeud = rechercherAVL(a, idstation);
            if (noeud != NULL){
                noeud->s.capacite = capacite;
                noeud->s.consommation += consommation;
            } 
            else{
                Station *s = creerStation(idstation, capacite, consommation);
            }
        } 
        else {
            printf("Erreur la ligne est invalide : %s", ligne);
        }
    }
    fclose(fichier);
}
