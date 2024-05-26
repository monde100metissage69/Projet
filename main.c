#include <stdio.h>
#include "display.h"
#include "mouvement.h"
#include "validation.h"
#include "game.h"


int main()
{
    int i, X, num_players, rounds, current_round;
    srand(time(NULL));
    printf("WELCOME TO CYBER PATH!\n");
    printf("Press 1 to start\n");
    scanf("%d", &X);

    // Ask for the number of players and rounds
    printf("Enter the number of players: ");
    while (scanf("%d", &num_players) != 1 || num_players <= 0)
    {
        printf("Invalid number of players! Please enter a valid number: ");
        while (getchar() != '\n')
            ; // Clear the buffer
    }
    printf("Enter the number of rounds: ");
    while (scanf("%d", &rounds) != 1 || rounds <= 0)
    {
        printf("Invalid number of rounds! Please enter a valid number: ");
        while (getchar() != '\n')
            ; // Clear the buffer
    }

    int scores[num_players];
    for (i = 0; i < num_players; i++)
    {
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
    for (current_round = 1; current_round <= rounds; current_round++)
    {
        printf("Round %d/%d\n", current_round, rounds);
        play_round(num_players, height, width, grid, robots, scores, valid_targets, num_valid_targets);
    }

    // End of the game - announce the winner or a tie
    int max_score = scores[0];
    int winner = 0;
    int tie = 0;
    for (i = 1; i < num_players; i++)
    {
        if (scores[i] > max_score)
        {
            max_score = scores[i];
            winner = i;
            tie = 0;
        }
        else if (scores[i] == max_score)
        {
            tie = 1;
        }
    }
    if (tie)
    {
        printf("The game is a tie with the highest score of %d points!\n", max_score);
    }
    else
    {
        printf("The winner is Player %d with %d points!\n", winner + 1, max_score);
    }

    return 0;
}
