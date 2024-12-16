#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <limits.h>
#include <ctype.h>

void lectureFichier(const char *CSV, parbre *a);
void ecrireInOrder(parbre a, FILE *fichier);
void exporter(parbre a, const char *CSV);

#endif
