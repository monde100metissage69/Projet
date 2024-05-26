void up(int *x, int *y, int width, struct Case T[][width])
{
    if (*x - 1 >= 0 && T[*x - 1][*y].down == 0 && T[*x][*y].Up == 0)
    {
        *x = *x - 1;
        return up(x, y, width, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}

void down(int *x, int *y, int length, int width, struct Case T[][width])
{
    if (*x + 1 < length && T[*x + 1][*y].Up == 0 && T[*x][*y].down == 0)
    {
        *x = *x + 1;
        return down(x, y, width, length, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}

void left(int *x, int *y, int length, struct Case T[][length])
{
    if (*y - 1 >= 0 && T[*x][*y - 1].right == 0 && T[*x][*y].left == 0)
    {
        *y = *y - 1;
        return left(x, y, length, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}

void right(int *x, int *y, int width, int length, struct Case T[][width])
{
    if (*y + 1 < width && T[*x][*y + 1].left == 0 && T[*x][*y].right == 0)
    {
        *y = *y + 1;
        return right(x, y, width, length, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
