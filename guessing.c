#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    printf("Guessing Game\n\n");

    int guess;
    int win;
    int level;
    int tries;

    double points = 1000;

    srand(time(0));
    int secret = rand() % 100;

    printf("Choose the level?\n");
    printf("(1) Easy (2) Medium (3) Hard\n\n");
    printf("Choose: ");

    scanf("%d", &level);

    switch (level)
    {
    case 1:
        tries = 20;
        break;
    case 2:
        tries = 15;
        break;
    default:
        tries = 6;
        break;
    }

    for (int i = 1; i <= tries; i++)
    {

        printf("-> Try %d of %d\n", i, tries);

        printf("Guess a number: ");
        scanf("%d", &guess);

        if (guess < 0)
        {
            printf("Negative numbers are not allowed\n");
            i--;
            continue;
        }

        win = guess == secret;

        if (win)
        {
            break;
        }
        else if (guess > secret)
        {
            printf("\nYour guess was GREATER than the secret number.!\n\n");
        }
        else
        {
            printf("\nYour guess was LESS than the secret number.!\n\n");
        }

        double penalty = abs(guess - secret) / 2.0;
        points = points - penalty;
    }

    printf("\n");
    if (win)
    {
        printf("\nCongratulations!!\n");
        printf("%.2f points.\n\n", points);
    }
    else
    {
        printf("\nYou lose :(\n\n");
    }
}