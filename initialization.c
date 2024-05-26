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
