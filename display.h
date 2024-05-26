ifndef DISPLAY_H
#define DISPLAY_H

#include <stlib.h>
#include <stdio.h>

void print_grid(int height, int width, struct Cell grid[][width], int robots[][2]);
void initialize_grid(int height, int width, struct Cell grid[][width]);
void place_targets(int height, int width, struct Cell grid[][width], int *valid_targets, int *num_valid_targets);
void print_grid(int height, int width, struct Cell grid[][width], int robots[][2]);
void assign_walls_to_targets(int height, int width, struct Cell grid[][width]);
void place_robots(int height, int width, struct Cell grid[][width], int robots[][2]);
#endif
     
