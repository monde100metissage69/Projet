#include "fichier.h"

 void lectureFichier(const char *CSV, avl **a){
    FILE *fichier = fopen(CSV, "r");
    if (!fichier) {
        exit(1);
    }
    char Donnee[256];
    int h = 0;
    fgets(Donnee, sizeof(Donnee), fichier);
    while (fgets(Donnee, sizeof(Donnee), fichier)){
        char *token = strtok(Donnee, ";");
        int idstation = atoi(token);
        token = strtok(NULL, ";");
        int capacite;
        if (strcmp(token, "-") != 0) {
            capacite = atoi(token); 
        } 
        else {
            capacite = 0;
        }
        long consommation = 0;
        while ((token = strtok(NULL, ";")) != NULL) {
            if (strcmp(token, "-") != 0) {
                consommation += atol(token);
            }
        }
        if (idstation > 0) {
            *a = insererAVL(*a, idstation, capacite, consommation, &h);
        }
    }
    fclose(fichier);
}
void ecrireInOrder(avl* a, FILE *fichier) {
    if (a != NULL) {
        ecrireInOrder(a->fg, fichier);
        fprintf(fichier, "%d;%d;%ld",  "station;capacite;consommation");
        ecrireInOrder(a->fd, fichier);
    }
}
void exporter(avl* a, const char *CSV) {
    FILE *fichier = fopen(CSV, "w");
    if (!fichier) {
        exit(1);
    }
    fprintf(fichier, "%d;%d;%ld\n", a->s.id, a->s.capacite, a->s.consommation);
    ecrireInOrder(a, fichier);
    fclose(fichier);
}
void lectureCSV(const char *chemincsv, const char *typestation, const char *typeconsommateur, const char *idcentrale){
  avl *a = NULL;
    lectureFichier(chemincsv, &a);
    exporter(a, "output.csv");
}
