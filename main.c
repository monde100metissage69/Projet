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

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    }
    const char *CHEMINCSV = argv[1];
    const char *TYPESTATION = argv[2];
    const char *TYPECONSOMMATEUR = argv[3];
    const char *IDCENTRALE;
    if (argc > 4) {
        IDCENTRALE = argv[4];
    } 
    else {
        IDCENTRALE = NULL;
    }
    lectureCSV(CHEMINCSV, TYPESTATION, TYPECONSOMMATEUR, IDCENTRALE);
    traitement();
    exporter();

    return 0;
}
   
