
void left(int *x, int *y, int length, struct Case T[][length])
{
    if (*y - 1 >= 0 && T[*x][*y - 1].right == 0 && T[*x][*y].left == 0)
    {
        *y = *y - 1;
        return left(x, y, length, T);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
