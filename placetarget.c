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
