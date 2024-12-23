#ifndef FICHIER_H
#define FICHIER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "avl.h"

Station* creerStation(int id, int capacite, long consommation);
void lectureFichier(const char *nomFichier, avl *a);

#endif
