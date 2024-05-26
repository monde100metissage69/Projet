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
