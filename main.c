#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "fichier.h"


int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    }
    const char *CHEMINCSV = argv[1];
    const char *TYPESTATION = argv[2];
    const char *TYPECONSOMMATEUR = argv[3];
    const char *IDCENTRALE;
    if (argc > 4) {
        IDCENTRALE = NULL;
    }
    else {
     IDCENTRALE = argv[4];
    }
    lectureCSV(CHEMINCSV, TYPESTATION, TYPECONSOMMATEUR, IDCENTRALE);
    return 0;
}
