void right(int *x, int *y, int width, int height, struct Cell grid[][width]) {
    if (*y + 1 < width && grid[*x][*y + 1].left == 0 && grid[*x][*y].right == 0) {
        *y = *y + 1;
        return right(x, y, width, height, grid);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
