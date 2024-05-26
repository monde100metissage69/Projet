void right(int *x, int *y, int width, int length, struct Case T[][width])
{
    if (*y + 1 < width && T[*x][*y + 1].left == 0 && T[*x][*y].right == 0)
    {
        *y = *y + 1;
        return right(x, y, width, length, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
