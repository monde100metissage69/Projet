void up(int *x, int *y, int width, struct Case T[][width])
{
    if (*x - 1 >= 0 && T[*x - 1][*y].down == 0 && T[*x][*y].Up == 0)
    {
        *x = *x - 1;
        return up(x, y, width, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}

