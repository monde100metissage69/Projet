#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <stlib.h>

void up(int *x, int *y, int width, struct Cell grid[][width]);
void down(int *x, int *y, int width, int height, struct Cell grid[][width]);
void left(int *x, int *y, int height, struct Cell grid[][height]);
void right(int *x, int *y, int width, int height, struct Cell grid[][width]);

#endif
