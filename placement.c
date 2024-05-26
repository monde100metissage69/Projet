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
