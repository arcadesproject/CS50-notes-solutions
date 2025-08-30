#include <cs50.h>
#include <stdio.h>
#include <math.h>

int prime(unsigned int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

int prime(unsigned int number)
{
    if (number <= 1) return 0;
    if (number == 2 || number == 3 || number == 5 || number == 7 || number == 11) return 1;
    if (number % 2 == 0) return 0;

    // Only check odd divisors up to sqrt(number)
    unsigned int limit = (int)sqrt((double)number);
    for (unsigned int i = 3; i <= limit; i+=2)
    {
        if (number % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
