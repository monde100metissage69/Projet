void down(int *x, int *y, int length, int width, struct Case T[][width])
{
    if (*x + 1 < length && T[*x + 1][*y].Up == 0 && T[*x][*y].down == 0)
    {
        *x = *x + 1;
        return down(x, y, width, length, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
