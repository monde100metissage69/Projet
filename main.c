#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <limits.h>
#include <ctype.h>
#include "display.h"
#include "avl.h"
#include "fichier.h"
#include "game.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s <fichier_entree> <fichier_sortie>\n", argv[0]);
        return 1;
    }

    FILE* entree = fopen(argv[1], "r");
    if (!entree) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        return 1;
    }

    FILE* sortie = fopen(argv[2], "w");
    if (!sortie) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        fclose(entree);
        return 1;
    }

    NoeudAVL* racine = NULL;
    char ligne[1024];

    fgets(ligne, sizeof(ligne), entree);

    while (fgets(ligne, sizeof(ligne), entree)) {
        int id;
        double capacite, consommation;
        char* token = strtok(ligne, ";");
        token = strtok(NULL, ";");
        id = atoi(token);
        token = strtok(NULL, ";");
        capacite = atof(token ? token : "0");
        token = strtok(NULL, ";");
        consommation = atof(token ? token : "0");
        racine = inserer(racine, id, capacite, consommation);
    }

    fprintf(sortie, "ID Station;Capacité;Consommation Totale\n");
    ecrireResultats(racine, sortie);

    libererArbre(racine);
    fclose(entree);
    fclose(sortie);

    return 0;
}
