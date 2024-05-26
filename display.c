void print_grid(int length, int width, struct Case T[][width], int robots[][2])
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                printf(red "+----" stop);
            }
            else
            {
                if (j == 0)
                {
                    printf(red "+" stop);
                    if (T[i][0].Up != 0)
                    {
                        printf(red "----" stop);
                    }
                    else
                    {
                        printf(gray "----" stop);
                    }
                }
                else
                {
                    if (T[i][j].Up != 0 || T[i - 1][j].down != 0)
                    {
                        printf(red "+" stop);
                        printf(red "----" stop);
                    }
                    else
                    {
                        printf(gray "+" stop);
                        printf(gray "----" stop);
                    }
                }
            }
        }
        printf(red "+\n" stop);

        for (int j = 0; j < width; j++)
        {
            int robot_present = 0;
            for (int k = 0; k < 4; k++)
            {
                if (robots[k][0] == i && robots[k][1] == j)
                {
                    robot_present = 1;
                    break;
                }
            }
            if (T[i][j].target != 0)
            {
                if (T[i][j].left != 0)
                {
                    printf(red "|%2d  " stop, T[i][j].target);
                }
                else
                {
                    printf(gray "|" stop);
                    printf(red "%2d  " stop, T[i][j].target);
                }
            }
            else if (robot_present)
            {
                printf(gray "| %s  " stop, ROBOT);
            }
            else
            {
                if (j == 0)
                {
                    printf(red "|    " stop);
                }
                else if (T[i][j - 1].right != 0)
                {
                    printf(red "|    " stop);
                }
                else
                {
                    printf(gray "|    " stop);
                }
            }
        }
        printf(red "|\n" stop);
    }
    for (int j = 0; j < width; j++)
    {
        printf(red "+----" stop);
    }
    printf(red "+\n" stop);

    printf("\n");
}
