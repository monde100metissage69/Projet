void down(int *x, int *y, int width, int height, struct Cell grid[][width]) {
    if (*x + 1 < height && grid[*x + 1][*y].top == 0 && grid[*x][*y].bottom == 0) {
        *x = *x + 1;
        return down(x, y, width, height, grid);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
