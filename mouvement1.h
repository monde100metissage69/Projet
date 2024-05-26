void up(int *x, int *y, int width, struct Cell grid[][width]) {
    if (*x - 1 >= 0 && grid[*x - 1][*y].bottom == 0 && grid[*x][*y].top == 0) {
        *x = *x - 1;
        return up(x, y, width, grid);
    }
    printf("x = %d, y = %d\n", *x, *y);
}
