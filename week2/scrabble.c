#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string one);

// points for letter in a-z alphabet
const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // get words from 2 players
    int one_total = calculate_score(get_string("Player 1: "));
    int two_total = calculate_score(get_string("Player 2: "));

    if (one_total == two_total)
    {
        printf("Tie!\n");
    }
    else if (one_total > two_total)
    {
        printf("Player 1 wins!\n");
    }
    else {
        printf("Player 2 wins!\n");
    }
}

// calculate score
int calculate_score(string word)
{
    int sum = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (islower(word[i]))
        {
            // Uses ascii numbering to get index
            sum += POINTS[word[i] - 'a'];
        }
        else if (!islower(word[i]))
        {
            // needs to take away higher value for capitals as later in ascii
            sum += POINTS[word[i] - 'A'];
        }
    }

    return sum;
}
