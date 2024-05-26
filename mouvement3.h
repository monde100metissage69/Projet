void left(int *x, int *y, int height, struct Cell grid[][height]) {
    if (*y - 1 >= 0 && grid[*x][*y - 1].right == 0 && grid[*x][*y].left == 0) {
        *y = *y - 1;
        return left(x, y, height, grid);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
