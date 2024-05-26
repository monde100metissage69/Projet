void print_grid(int height, int width, struct Cell grid[][width], int robots[][2]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0) {
                printf(RED "+----" STOP);
            } else {
                if (j == 0) {
                    printf(RED "+" STOP);
                    if (grid[i][0].top != 0) {
                        printf(RED "----" STOP);
                    } else {
                        printf(GRAY "----" STOP);
                    }
                } else {
                    if (grid[i][j].top != 0 || grid[i - 1][j].bottom != 0) {
                        printf(RED "+" STOP);
                        printf(RED "----" STOP);
                    } else {
                        printf(GRAY "+" STOP);
                        printf(GRAY "----" STOP);
                    }
                }
            }
        }
        printf(RED "+\n" STOP);

        for (int j = 0; j < width; j++) {
            int robot_present = -1;
            for (int k = 0; k < 4; k++) {
                if (robots[k][0] == i && robots[k][1] == j) {
                    robot_present = k;
                    break;
                }
            }
            if (grid[i][j].target != 0) {
                if (grid[i][j].left != 0) {
                    printf(RED "|%2d  " STOP, grid[i][j].target);
                } else {
                    printf(GRAY "|" STOP);
                    printf(RED "%2d  " STOP, grid[i][j].target);
                }
            } else if (robot_present != -1) {
                const char *emojis[] = {ROBOT, OGRE, ALIEN_MONSTER, GHOST};
                printf(GRAY "| %s  " STOP, emojis[robot_present]);
            } else {
                if (j == 0) {
                    printf(RED "|    " STOP);
                } else if (grid[i][j - 1].right != 0) {
                    printf(RED "|    " STOP);
                } else {
                    printf(GRAY "|    " STOP);
                }
            }
        }
        printf(RED "|\n" STOP);
    }
    for (int j = 0; j < width; j++) {
        printf(RED "+----" STOP);
    }
    printf(RED "+\n" STOP);

    printf("\n");
}
