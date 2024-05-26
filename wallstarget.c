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

