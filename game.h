void play_round(int num_players, int height, int width, struct Cell grid[][width], int robots[][2], int *scores, int *valid_targets, int num_valid_targets)
{
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
    char input[10];
    for (int i = 0; i < num_players; i++)
    {
        printf("Player %d, enter the number of moves: ", i + 1);
        while (1)
        {
            scanf("%s", input);
            if (is_valid_number(input))
            {
                moves[i] = atoi(input);
                break;
            }
            else
            {
                printf("Invalid input! Please enter a valid number without spaces: ");
            }
        }
    }

    int min_moves = moves[0];
    int min_player = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (moves[i] < min_moves)
        {
            min_moves = moves[i];
            min_player = i;
        }
    }

    printf("Player %d with the smallest moves (%d) will play.\n", min_player + 1, min_moves);

    // Move the robot
    int actual_moves = 0;
    while (grid[x][y].target != target_index && actual_moves < min_moves)
    {
        int direction;
        print_grid(height, width, grid, robots); // Re-display the grid before each move
        printf("The selected robot is %s which must reach target %d\n", emojis[robot_index], target_index);
        printf("Enter direction (1=up, 2=down, 3=left, 4=right): ");
        while (scanf("%d", &direction) != 1 || direction < 1 || direction > 4)
        {
            printf("Invalid input! Please enter a valid direction (1=up, 2=down, 3=left, 4=right): ");
            while (getchar() != '\n')
                ; // Clear the buffer
        }
        if (direction == 1)
        {
            up(&x, &y, width, grid);
        }
        else if (direction == 2)
        {
            down(&x, &y, width, height, grid);
        }
        else if (direction == 3)
        {
            left(&x, &y, height, grid);
        }
        else if (direction == 4)
        {
            right(&x, &y, width, height, grid);
        }
        actual_moves++;
    }

    // Check if the target is reached
    if (grid[x][y].target == target_index)
    {
        if (actual_moves == min_moves)
        {
            scores[min_player] += 2;
            printf("Player %d reached the target in the correct number of moves. +2 points.\n", min_player + 1);
        }
        else
        {
            scores[min_player] -= 1;
            printf("Player %d reached the target but in fewer moves than expected. -1 point.\n", min_player + 1);
        }
    }
    else
    {
        for (int i = 0; i < num_players; i++)
        {
            if (i != min_player)
            {
                scores[i] += 1;
            }
        }
        printf("Player %d failed to reach the target. All other players +1 point.\n", min_player + 1);
    }

    // Print scores after the round
    printf("Scores after this round:\n");
    for (int i = 0; i < num_players; i++)
    {
        printf("Player %d: %d points\n", i + 1, scores[i]);
    }
}

