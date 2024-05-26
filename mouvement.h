// Move the robot up if possible
void up(int *x, int *y, int width, struct Cell grid[][width])
{
    if (*x - 1 >= 0 && grid[*x - 1][*y].bottom == 0 && grid[*x][*y].top == 0)
    {
        *x = *x - 1;
        return up(x, y, width, grid);
    }
}

// Move the robot down if possible
void down(int *x, int *y, int width, int height, struct Cell grid[][width])
{
    if (*x + 1 < height && grid[*x + 1][*y].top == 0 && grid[*x][*y].bottom == 0)
    {
        *x = *x + 1;
        return down(x, y, width, height, grid);
    }
}

// Move the robot left if possible
void left(int *x, int *y, int height, struct Cell grid[][height])
{
    if (*y - 1 >= 0 && grid[*x][*y - 1].right == 0 && grid[*x][*y].left == 0)
    {
        *y = *y - 1;
        return left(x, y, height, grid);
    }
}

// Move the robot right if possible
void right(int *x, int *y, int width, int height, struct Cell grid[][width])
{
    if (*y + 1 < width && grid[*x][*y + 1].left == 0 && grid[*x][*y].right == 0)
    {
        *y = *y + 1;
        return right(x, y, width, height, grid);
    }
}
