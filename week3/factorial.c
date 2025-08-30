#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get input, ask again if negative number entered
    int number;
    do
    {
        number = get_int("Enter positive number: ");
    }
    while (number < 0);
    {
        int result = factorial(number);
        printf("Factorial of %i is %i", number, result);
    }

}

int factorial(int n)
{
    if (n == 0)
    {
        // Base case
        return 1;
    }
    else 
    {
        // Recursive case
        return n * factorial(n-1);
    }
}