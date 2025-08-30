#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(char *input, int number);

int main(void)
{
    char *input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input, 0));
}

int convert(char *input, int number)
{
    // iteration version, would just but convert(char *input)
    // int number = 0;

    // for (int i = 0, n = strlen(input); i < n; i++)
    // {
    //     // manually parse a string into an integer with base-10 accumulation
    //     number = number * 10 + (input[i] - '0');
    // }

    // return number;

    // base case
    if (*input == '\0')
    {
        return number;
    }

    // recursive case
    // input + 1 changes pointer, so move to next digit in string, not digit + 1 like an int
    return convert(input + 1, number * 10 + (*input - '0'));
}
