#ifndef FICHIER_H
#define FICHIER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void lectureFichier(const char *CSV, parbre *a);
void ecrireInOrder(parbre a, FILE *fichier);
void exporter(parbre a, const char *CSV);

#endif
