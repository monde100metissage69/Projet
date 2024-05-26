#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <stlib.h>
void play_round(int num_players, int height, int width, struct Cell grid[][width], int robots[][2], int *scores, int *valid_targets, int num_valid_targets);
#endif
 

