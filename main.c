int main()
{
    int i, j, X, p, q, x, y, num_players, rounds, current_round;
    int length, width;
    srand(time(NULL));
    printf("Press 1 to start\n");
    scanf("%d", &X);
    if (X == 1)
    {
        printf("wsh batard t pour le metissage?\n");
    }
    else
    {
        exit(1);
    }
    // Demander le nombre de joueurs et de manches
    printf("Enter the number of players:\n ");
    scanf("%d", &num_players);
    printf("Enter the number of rounds:\n ");
    scanf("%d", &rounds);

    int scores[num_players];
    for (i = 0; i < num_players; i++)
    {
        scores[i] = 0;
    }

    // Créer la carte une fois pour toutes les manches
    length = rand() % 6 + 15;
    width = rand() % 6 + 15;

    struct Case T[length][width];
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            T[i][j].Up = 0;
            T[i][j].down = 0;
            T[i][j].left = 0;
            T[i][j].right = 0;
            T[i][j].target = 0;
        }
    }

    // Placer les targets aléatoirement
    for (p = 1; p <= 18;)
    {
        x = rand() % (length - 2) + 1;
        y = rand() % (width - 2) + 1;
        if (T[x - 1][y - 1].target == 0 && T[x + 1][y + 1].target == 0)
        {
            if (T[x - 1][y].target == 0 && T[x + 1][y].target == 0)
            {
                if (T[x - 1][y + 1].target == 0 && T[x + 1][y - 1].target == 0)
                {
                    if (T[x][y - 1].target == 0 && T[x][y + 1].target == 0)
                    {
                        T[x][y].target = p;
                        p++;
                    }
                }
            }
        }
    }

    // Attribuer des murs aux targets
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (T[i][j].target != 0)
            {
                do
                {
                    q = rand() % 4 + 1;
                    if (q == 1 && j < width - 1 && i < length - 1)
                    {
                        T[i][j].right = 1;
                        T[i][j].down = 1;
                    }
                    else if (q == 2 && j > 0 && i < length - 1)
                    {
                        T[i][j].down = 1;
                        T[i][j].left = 1;
                    }
                    else if (q == 3 && j > 0 && i > 0)
                    {
                        T[i][j].left = 1;
                        T[i][j].Up = 1;
                    }
                    else if (q == 4 && j < width - 1 && i > 0)
                    {
                        T[i][j].Up = 1;
                        T[i][j].right = 1;
                    }
                    else
                    {
                        continue;
                    }
                    break;
                } while (1);
            }
        }
    }

    // Attribuer des murs aux bords
    for (i = 0; i < 2;)
    {
        x = rand() % (length - 2) + 1;
        if (T[x - 1][0].down == 0 && T[x + 1][0].down == 0)
        {
            T[x][0].down = 1;
            T[x + 1][0].Up = 1;
            i++;
        }
    }
    for (i = 0; i < 2;)
    {
        x = rand() % (length - 2) + 1;
        if (T[x - 1][width - 1].down == 0 && T[x + 1][width - 1].down == 0)
        {
            T[x][width - 1].down = 1;
            T[x + 1][width - 1].Up = 1;
            i++;
        }
    }
    for (i = 0; i < 2;)
    {
        y = rand() % (width - 2) + 1;
        if (T[0][y - 1].right == 0 && T[0][y + 1].right == 0)
        {
            T[0][y].right = 1;
            T[0][y + 1].left = 1;
            i++;
        }
    }
    for (i = 0; i < 2;)
    {
        y = rand() % (width - 2) + 1;
        if (T[length - 1][y - 1].right == 0 && T[length - 1][y + 1].right == 0)
        {
            T[length - 1][y].right = 1;
            T[length - 1][y + 1].left = 1;
            i++;
        }
    }

    // Placer les robots
    int robots[4][2];
    for (i = 0; i < 4; i++)
    {
        do
        {
            x = rand() % length;
            y = rand() % width;
        } while (T[x][y].target != 0 || (x == 0 || x == length - 1 || y == 0 || y == width - 1));
        robots[i][0] = x;
        robots[i][1] = y;
    }

    // Début de la boucle des manches
    for (current_round = 1; current_round <= rounds; current_round++)
    {
        printf("Round %d/%d\n", current_round, rounds);
        print_grid(length, width, T, robots);

        // Sélection d'un robot et d'une targetaléatoire
        int robot_index = rand() % 4;
        int target_index;
        do
        {
            target_index = rand() % 18 + 1;
        } while (T[robots[robot_index][0]][robots[robot_index][1]].target == target_index);

        x = robots[robot_index][0];
        y = robots[robot_index][1];

        printf("Robot selected at position (%d, %d)\n", x, y);
        printf("Target: %d\n", target_index);

        // Chronometre
        printf("You have 10 seconds to think...\n");
        sleep(10);

        // Erase the screen after a short duration
        printf("\033[H\033[J");

        // Enter the number of players
        int moves[num_players];
        for (i = 0; i < num_players; i++)
        {
            printf("Player %d, enter the number of moves: ", i + 1);
            scanf("%d", &moves[i]);
        }

        int min_moves = moves[0];
        int min_player = 0;
        for (i = 1; i < num_players; i++)
        {
            if (moves[i] < min_moves)
            {
                min_moves = moves[i];
                min_player = i;
            }
        }

        printf("Player %d with the smallest moves (%d) will play.\n", min_player + 1, min_moves);

        // Mouvement of the robot
        int actual_moves = 0;
        while (T[x][y].target != target_index && actual_moves < min_moves)
        {
            int direction;
            printf("Enter direction (1=up, 2=down, 3=left, 4=right): ");
            scanf("%d", &direction);
            if (direction == 1)
            {
                up(&x, &y, width, T);
            }
            else if (direction == 2)
            {
                down(&x, &y, width, length, T);
            }
            else if (direction == 3)
            {
                left(&x, &y, length, T);
            }
            else if (direction == 4)
            {
                right(&x, &y, width, length, T);
            }
            actual_moves++;
        }

        if (T[x][y].target == target_index)
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
            for (i = 0; i < num_players; i++)
            {
                if (i != min_player)
                {
                    scores[i] += 1;
                }
            }
            printf("Player %d failed to reach the target. All other players +1 point.\n", min_player + 1);
        }

        printf("Scores after round %d:\n", current_round);
        for (i = 0; i < num_players; i++)
        {
            printf("Player %d: %d points\n", i + 1, scores[i]);
        }
    }

    ///////////////////////////  FIN DU JEU - AFFICHAGE DU GAGNANT  /////////////////////////////
    int max_score = scores[0];
    int winner = 0;
    for (i = 1; i < num_players; i++)
    {
        if (scores[i] > max_score)
        {
            max_score = scores[i];
            winner = i;
        }
    }
    printf("The winner is Player %d with %d points!\n", winner + 1, max_score);

    return 0;
}
