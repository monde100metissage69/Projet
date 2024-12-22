#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "fichier.h"

int main(int argc, char* argv[]){
    const char *nomduFichier = argv[1];
    printf("%s", argv[1]);

    const char *FINALE = argv[2];
    avl *a = NULL;
    int h = 0;

    lectureFichier(nomduFichier, &a);

    FILE* FICHIER = fopen(FINALE, "w");
    if(FICHIER == NULL){
        printf("Echec de l'ouverture du fichier %s :", FINALE);
        exit(1);
    }
    Remplirlefichier(a, FICHIER);
    fclose(FICHIER);
    return 0;
}


