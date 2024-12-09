#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <limits.h>
#include <ctype.h>
void play_round(int num_players, int height, int width, struct Cell grid[][width], int robots[][2], int *scores, int *valid_targets, int num_valid_targets);
#endif
 

