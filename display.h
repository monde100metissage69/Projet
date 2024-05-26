void print_grid(int height, int width, struct Cell grid[][width], int robots[][2])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                printf(RED "+----" STOP);
            }
            else
            {
                if (j == 0)
                {
                    printf(RED "+" STOP);
                    if (grid[i][0].top != 0)
                    {
                        printf(RED "----" STOP);
                    }
                    else
                    {
                        printf(GRAY "----" STOP);
                    }
                }
                else
                {
                    if (grid[i][j].top != 0 || grid[i - 1][j].bottom != 0)
                    {
                        printf(RED "+" STOP);
                        printf(RED "----" STOP);
                    }
                    else
                    {
                        printf(GRAY "+" STOP);
                        printf(GRAY "----" STOP);
                    }
                }
            }
        }
        printf(RED "+\n" STOP);

        for (int j = 0; j < width; j++)
        {
            int robot_present = -1;
            for (int k = 0; k < 4; k++)
            {
                if (robots[k][0] == i && robots[k][1] == j)
                {
                    robot_present = k;
                    break;
                }
            }
            if (grid[i][j].target != 0)
            {
                if (grid[i][j].left != 0)
                {
                    printf(RED "|%2d  " STOP, grid[i][j].target);
                }
                else
                {
                    printf(GRAY "|" STOP);
                    printf(RED "%2d  " STOP, grid[i][j].target);
                }
            }
            else if (robot_present != -1)
            {
                const char *emojis[] = {ROBOT, OGRE, ALIEN_MONSTER, GHOST};
                printf(GRAY "| %s " STOP, emojis[robot_present]);
            }
            else
            {
                if (j == 0)
                {
                    printf(RED "|    " STOP);
                }
                else if (grid[i][j - 1].right != 0)
                {
                    printf(RED "|    " STOP);
                }
                else
                {
                    printf(GRAY "|    " STOP);
                }
            }
        }
        printf(RED "|\n" STOP);
    }
    for (int j = 0; j < width; j++)
    {
        printf(RED "+----" STOP);
    }
    printf(RED "+\n" STOP);

    printf("\n");
}

// Initialize the grid with no walls and no targets
void initialize_grid(int height, int width, struct Cell grid[][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grid[i][j].top = 0;
            grid[i][j].bottom = 0;
            grid[i][j].left = 0;
            grid[i][j].right = 0;
            grid[i][j].target = 0;
        }
    }
}

// Place targets randomly on the grid
void place_targets(int height, int width, struct Cell grid[][width], int *valid_targets, int *num_valid_targets)
{
    int p = 1, x, y;
    while (p <= 18)
    {
        x = rand() % (height - 2) + 1;
        y = rand() % (width - 2) + 1;
        if (grid[x - 1][y - 1].target == 0 && grid[x + 1][y + 1].target == 0)
        {
            if (grid[x - 1][y].target == 0 && grid[x + 1][y].target == 0)
            {
                if (grid[x - 1][y + 1].target == 0 && grid[x + 1][y - 1].target == 0)
                {
                    if (grid[x][y - 1].target == 0 && grid[x][y + 1].target == 0)
                    {
                        grid[x][y].target = p;
                        valid_targets[*num_valid_targets] = p;
                        (*num_valid_targets)++;
                        p++;
                    }
                }
            }
        }
    }
}

// Assign walls to targets
void print_grid(int height, int width, struct Cell grid[][width], int robots[][2])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                printf(RED "+----" STOP);
            }
            else
            {
                if (j == 0)
                {
                    printf(RED "+" STOP);
                    if (grid[i][0].top != 0)
                    {
                        printf(RED "----" STOP);
                    }
                    else
                    {
                        printf(GRAY "----" STOP);
                    }
                }
                else
                {
                    if (grid[i][j].top != 0 || grid[i - 1][j].bottom != 0)
                    {
                        printf(RED "+" STOP);
                        printf(RED "----" STOP);
                    }
                    else
                    {
                        printf(GRAY "+" STOP);
                        printf(GRAY "----" STOP);
                    }
                }
            }
        }
        printf(RED "+\n" STOP);

        for (int j = 0; j < width; j++)
        {
            int robot_present = -1;
            for (int k = 0; k < 4; k++)
            {
                if (robots[k][0] == i && robots[k][1] == j)
                {
                    robot_present = k;
                    break;
                }
            }
            if (grid[i][j].target != 0)
            {
                if (grid[i][j].left != 0)
                {
                    printf(RED "|%2d  " STOP, grid[i][j].target);
                }
                else
                {
                    printf(GRAY "|" STOP);
                    printf(RED "%2d  " STOP, grid[i][j].target);
                }
            }
            else if (robot_present != -1)
            {
                const char *emojis[] = {ROBOT, OGRE, ALIEN_MONSTER, GHOST};
                printf(GRAY "| %s " STOP, emojis[robot_present]);
            }
            else
            {
                if (j == 0)
                {
                    printf(RED "|    " STOP);
                }
                else if (grid[i][j - 1].right != 0)
                {
                    printf(RED "|    " STOP);
                }
                else
                {
                    printf(GRAY "|    " STOP);
                }
            }
        }
        printf(RED "|\n" STOP);
    }
    for (int j = 0; j < width; j++)
    {
        printf(RED "+----" STOP);
    }
    printf(RED "+\n" STOP);

    printf("\n");
}
void assign_walls_to_targets(int height, int width, struct Cell grid[][width])
{
    int q;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (grid[i][j].target != 0)
            {
                do
                {
                    q = rand() % 4 + 1;
                    if (q == 1 && j < width - 1 && i < height - 1)
                    {
                        grid[i][j].right = 1;
                        grid[i][j].bottom = 1;
                    }
                    else if (q == 2 && j > 0 && i < height - 1)
                    {
                        grid[i][j].bottom = 1;
                        grid[i][j].left = 1;
                    }
                    else if (q == 3 && j > 0 && i > 0)
                    {
                        grid[i][j].left = 1;
                        grid[i][j].top = 1;
                    }
                    else if (q == 4 && j < width - 1 && i > 0)
                    {
                        grid[i][j].top = 1;
                        grid[i][j].right = 1;
                    }
                    else
                    {
                        continue;
                    }
                    break;
                } while (1);
            }
        }
    }
}

// Assign walls to the edges of the grid
void assign_walls_to_edges(int height, int width, struct Cell grid[][width])
{
    int i, x, y;
    for (i = 0; i < 2;)
    {
        x = rand() % (height - 2) + 1;
        if (grid[x - 1][0].bottom == 0 && grid[x + 1][0].bottom == 0)
        {
            grid[x][0].bottom = 1;
            grid[x + 1][0].top = 1;
            i++;
        }
    }
    for (i = 0; i < 2;)
    {
        x = rand() % (height - 2) + 1;
        if (grid[x - 1][width - 1].bottom == 0 && grid[x + 1][width - 1].bottom == 0)
        {
            grid[x][width - 1].bottom = 1;
            grid[x + 1][width - 1].top = 1;
            i++;
        }
    }
    for (i = 0; i < 2;)
    {
        y = rand() % (width - 2) + 1;
        if (grid[0][y - 1].right == 0 && grid[0][y + 1].right == 0)
        {
            grid[0][y].right = 1;
            grid[0][y + 1].left = 1;
            i++;
        }
    }
    for (i = 0; i < 2;)
    {
        y = rand() % (width - 2) + 1;
        if (grid[height - 1][y - 1].right == 0 && grid[height - 1][y + 1].right == 0)
        {
            grid[height - 1][y].right = 1;
            grid[height - 1][y + 1].left = 1;
            i++;
        }
    }
}

// Place robots randomly on the grid
void place_robots(int height, int width, struct Cell grid[][width], int robots[][2])
{
    int i, x, y;
    for (i = 0; i < 4; i++)
    {
        do
        {
            x = rand() % height;
            y = rand() % width;
        } while (grid[x][y].target != 0 || (x == 0 || x == height - 1 || y == 0 || y == width - 1));
        robots[i][0] = x;
        robots[i][1] = y;
    }
}
               
