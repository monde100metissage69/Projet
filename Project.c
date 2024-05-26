#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // for the sleep function
#include <limits.h>
#include <ctype.h>

#define GRAY "\033[1;30m"
#define BLUE "\033[0;34m"
#define RED "\033[1;31m"
#define STOP "\033[0m"

#define ROBOT "\U0001F916"         // Robot emoji
#define OGRE "\U0001F479"          // Ogre emoji
#define ALIEN_MONSTER "\U0001F47E" // Alien monster emoji
#define GHOST "\U0001F47B"         // Ghost emoji

struct Cell
{
    int top;
    int bottom;
    int left;
    int right;
    int target;
};

// Move the robot up if possible
void up(int *x, int *y, int width, struct Cell grid[][width]){
    if (*x - 1 >= 0 && grid[*x - 1][*y].bottom == 0 && grid[*x][*y].top == 0){
        *x = *x - 1;
        return up(x, y, width, grid);
    }
}
// Move the robot down if possible
void down(int *x, int *y, int width, int height, struct Cell grid[][width]){
    if (*x + 1 < height && grid[*x + 1][*y].top == 0 && grid[*x][*y].bottom == 0){
      *x = *x + 1;
        return down(x, y, width, height, grid);
    }
}
// Move the robot left if possible
void left(int *x, int *y, int height, struct Cell grid[][height]){
    if (*y - 1 >= 0 && grid[*x][*y - 1].right == 0 && grid[*x][*y].left == 0){
        *y = *y - 1;
        return left(x, y, height, grid);
    }
}
// Move the robot right if possible
void right(int *x, int *y, int width, int height, struct Cell grid[][width]){
    if (*y + 1 < width && grid[*x][*y + 1].left == 0 && grid[*x][*y].right == 0){
        *y = *y + 1;
        return right(x, y, width, height, grid);
    }
}
// Print the game grid with robots and targets
void print_grid(int height, int width, struct Cell grid[][width], int robots[][2]){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (i == 0){
                printf(RED "+----" STOP);
            }
            else{
                if (j == 0)
                {
                    printf(RED "+" STOP);
                    if (grid[i][0].top != 0){
                        printf(RED "----" STOP);
                    }
                    else{
                        printf(GRAY "----" STOP);
                    }
                }
                else{
                    if (grid[i][j].top != 0 || grid[i - 1][j].bottom != 0){
                        printf(RED "+" STOP);
                        printf(RED "----" STOP);
                    }
                    else{
                        printf(GRAY "+" STOP);
                        printf(GRAY "----" STOP);
                    }
                }
            }
        }
        printf(RED "+\n" STOP);

        for (int j = 0; j < width; j++){
            int robot_present = -1;
            for (int k = 0; k < 4; k++){
                if (robots[k][0] == i && robots[k][1] == j){
                    robot_present = k;
                    break;
                }
            }
            if (grid[i][j].target != 0){
                if (grid[i][j].left != 0){
                printf(RED "|%2d  " STOP, grid[i][j].target);
                }
                else{
                    printf(GRAY "|" STOP);
                    printf(RED "%2d  " STOP, grid[i][j].target);
                }
            }
            else if (robot_present != -1){
                const char *emojis[] = {ROBOT, OGRE, ALIEN_MONSTER, GHOST};
                printf(GRAY "| %s " STOP, emojis[robot_present]);
            }
            else{
                if (j == 0){
                    printf(RED "|    " STOP);
                }
                else if (grid[i][j - 1].right != 0){
                    printf(RED "|    " STOP);
                }
                else{
                    printf(GRAY "|    " STOP);
                }
            }
        }
        printf(RED "|\n" STOP);
    }
    for (int j = 0; j < width; j++){
        printf(RED "+----" STOP);
    }
    printf(RED "+\n" STOP);

    printf("\n");
}

// Initialize the grid with no walls and no targets
void initialize_grid(int height, int width, struct Cell grid[][width]){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++)
        {
            grid[i][j].top = 0;
            grid[i][j].bottom = 0;
            grid[i][j].left = 0;
            grid[i][j].right = 0;
            grid[i][j].target = 0;
        }
    }
}

// Place targets randomly on the grid
void place_targets(int height, int width, struct Cell grid[][width], int *valid_targets, int *num_valid_targets){
    int p = 1, x, y;
    while (p <= 18){
        x = rand() % (height - 2) + 1;
        y = rand() % (width - 2) + 1;
        if (grid[x - 1][y - 1].target == 0 && grid[x + 1][y + 1].target == 0){
            if (grid[x - 1][y].target == 0 && grid[x + 1][y].target == 0){
                if (grid[x - 1][y + 1].target == 0 && grid[x + 1][y - 1].target == 0){
                    if (grid[x][y - 1].target == 0 && grid[x][y + 1].target == 0){
                        grid[x][y].target = p;
                        valid_targets[*num_valid_targets] = p;
                        (*num_valid_targets)++;
                        p++;
                    }
                }
            }
        }
    }
}

// Assign walls to targets
void assign_walls_to_targets(int height, int width, struct Cell grid[][width]){
    int q;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
        if (grid[i][j].target != 0){
                do{
                    q = rand() % 4 + 1;
                    if (q == 1 && j < width - 1 && i < height - 1){
                        grid[i][j].right = 1;
                        grid[i][j].bottom = 1;
                    }
                    else if (q == 2 && j > 0 && i < height - 1){
                        grid[i][j].bottom = 1;
                        grid[i][j].left = 1;
                    }
                    else if (q == 3 && j > 0 && i > 0){
                        grid[i][j].left = 1;
                        grid[i][j].top = 1;
                    }
                    else if (q == 4 && j < width - 1 && i > 0){
                        grid[i][j].top = 1;
                        grid[i][j].right = 1;
                    }
                    else{
                        continue;
                    }
                    break;
                } while (1);
            }
        }
    }
}

// Assign walls to the edges of the grid
void assign_walls_to_edges(int height, int width, struct Cell grid[][width]){
    int i, x, y;
    for (i = 0; i < 2;){
        x = rand() % (height - 2) + 1;
        if (grid[x - 1][0].bottom == 0 && grid[x + 1][0].bottom == 0){
            grid[x][0].bottom = 1;
            grid[x + 1][0].top = 1;
            i++;
        }
    }
    for (i = 0; i < 2;){
       x = rand() % (height - 2) + 1;
        if (grid[x - 1][width - 1].bottom == 0 && grid[x + 1][width - 1].bottom == 0){
            grid[x][width - 1].bottom = 1;
            grid[x + 1][width - 1].top = 1;
            i++;
        }
    }
    for (i = 0; i < 2;){
        y = rand() % (width - 2) + 1;
        if (grid[0][y - 1].right == 0 && grid[0][y + 1].right == 0){
            grid[0][y].right = 1;
            grid[0][y + 1].left = 1;
            i++;
        }
    }
    for (i = 0; i < 2;){
        y = rand() % (width - 2) + 1;
        if (grid[height - 1][y - 1].right == 0 && grid[height - 1][y + 1].right == 0){
            grid[height - 1][y].right = 1;
            grid[height - 1][y + 1].left = 1;
            i++;
        }
    }
}

// Place robots randomly on the grid
void place_robots(int height, int width, struct Cell grid[][width], int robots[][2]){
    int i, x, y;
    for (i = 0; i < 4; i++){
        do{
            x = rand() % height;
            y = rand() % width;
        } while (grid[x][y].target != 0 || (x == 0 || x == height - 1 || y == 0 || y == width - 1));
        robots[i][0] = x;
        robots[i][1] = y;
    }
}

// Check if input is a valid number without spaces
int is_valid_number(char *str){
    for (int i = 0; str[i] != '\0'; i++){
        if (!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}

// Play a single round of the game
void play_round(int num_players, int height, int width, struct Cell grid[][width], int robots[][2], int *scores, int *valid_targets, int num_valid_targets){
    printf("New Round!\n");
    print_grid(height, width, grid, robots);

    // Select a random robot and a random target
    int robot_index = rand() % 4;
    int target_index = valid_targets[rand() % num_valid_targets];

    const char *emojis[] = {ROBOT, OGRE, ALIEN_MONSTER, GHOST};
    printf("The selected robot is %s which must reach target %d\n", emojis[robot_index], target_index);

    int x = robots[robot_index][0];
    int y = robots[robot_index][1];

    // Reflection timer
    printf("You have 30 seconds to think...\n");
    sleep(30);

    // Clear the screen after the reflection time
    printf("\033[H\033[J");

    // Enter the number of moves for each player
    int moves[num_players];
    char input[100];
    for (int i = 0; i < num_players; i++){
        printf("Player %d, enter the number of moves: ", i + 1);
        while (1){
            scanf("%s", input);
            if (is_valid_number(input)){
                moves[i] = atoi(input);
                break;
            }
            else{
                printf("Invalid input! Please enter a valid number without spaces: ");
            }
        }
    }

    int min_moves = moves[0];
    int min_player = 0;
    for (int i = 1; i < num_players; i++){
        if (moves[i] < min_moves){
            min_moves = moves[i];
            min_player = i;
        }
    }

    printf("Player %d with the smallest moves (%d) will play.\n", min_player + 1, min_moves);

    // Move the robot
    int actual_moves = 0;
    int correct_moves = 0; // Counter for correct moves

    while (grid[x][y].target != target_index && actual_moves < min_moves){
        int direction;
        printf("Enter direction (1=up, 2=down, 3=left, 4=right): ");
        while (scanf("%d", &direction) != 1 || direction < 1 || direction > 4){
            printf("Invalid input! Please enter a valid direction (1=up, 2=down, 3=left, 4=right): ");
            while (getchar() != '\n')
                ; // Clear the buffer
        }

        int prev_x = x, prev_y = y;

        if (direction == 1){
            up(&x, &y, width, grid);
        }
        else if (direction == 2){
            down(&x, &y, width, height, grid);
        }
        else if (direction == 3){
            left(&x, &y, height, grid);
        }
        else if (direction == 4){
            right(&x, &y, width, height, grid);
        }

        actual_moves++;

        if (grid[x][y].target == target_index){
          correct_moves++;
            break;
        }
        else if (prev_x != x || prev_y != y){
            correct_moves++;
        }
    }

    // Print the results
    if (grid[x][y].target == target_index){
        if (actual_moves == min_moves){
            scores[min_player] += 2;
            printf("Player %d reached the target in the correct number of moves. +2 points.\n", min_player + 1);
        }
        else{
            scores[min_player] -= 1;
            printf("Player %d reached the target but in fewer moves than expected. -1 point.\n", min_player + 1);
        }
    }
    else{
        for (int i = 0; i < num_players; i++){
            if (i != min_player){
                scores[i] += 1;
            }
        }
        printf("Player %d failed to reach the target. All other players +1 point.\n", min_player + 1);
    }

    printf("Player %d used %d moves. Correct moves were: %d\n", min_player + 1, actual_moves, correct_moves);
    printf("Correct directions: The correct direction was towards the target %d.\n", target_index);

    // Print scores after the round
    printf("Scores after this round:\n");
    for (int i = 0; i < num_players; i++){
        printf("Player %d: %d points\n", i + 1, scores[i]);
    }
}

int main(){
    int i, X, num_players, rounds, current_round;
    srand(time(NULL));
    printf("WELCOME TO CYBER PATH!\n");
    printf("Press 1 to start\n");
    scanf("%d", &X);

    // Ask for the number of players and rounds
    printf("Enter the number of players: ");
    while (scanf("%d", &num_players) != 1 || num_players <= 0){
        printf("Invalid number of players! Please enter a valid number: ");
        while (getchar() != '\n')
            ; // Clear the buffer
    }
    printf("Enter the number of rounds: ");
    while (scanf("%d", &rounds) != 1 || rounds <= 0){
        printf("Invalid number of rounds! Please enter a valid number: ");
        while (getchar() != '\n')
            ; // Clear the buffer
    }
    int scores[num_players];
    for (i = 0; i < num_players; i++){
        scores[i] = 0;
    }
    // Create the grid once for all rounds
    int height = rand() % 6 + 15;
    int width = rand() % 6 + 15;
    
    struct Cell grid[height][width];
    initialize_grid(height, width, grid);

    int valid_targets[18];
    int num_valid_targets = 0;
    place_targets(height, width, grid, valid_targets, &num_valid_targets);
    assign_walls_to_targets(height, width, grid);
    assign_walls_to_edges(height, width, grid);
    // Place the robots
    
    int robots[4][2];
    place_robots(height, width, grid, robots);
    
    // Start the rounds
    for (current_round = 1; current_round <= rounds; current_round++){
        printf("Round %d/%d\n", current_round, rounds);
        play_round(num_players, height, width, grid, robots, scores, valid_targets, num_valid_targets);
    }
    // End of the game - announce the winner or a tie
    int max_score = scores[0];
    int winner = 0;
    int tie = 0;
    for (i = 1; i < num_players; i++){
        if (scores[i] > max_score){
            max_score = scores[i];
            winner = i;
            tie = 0;
        }
        else if (scores[i] == max_score){
            tie = 1;
        }
    }
    if (tie){
        printf("The game is a tie with the highest score of %d points!\n", max_score);
    }
    else{
        printf("The winner is Player %d with %d points!\n", winner + 1, max_score);
    }
    return 0;
}
