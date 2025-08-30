#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int num = ("Enter int: ");
    int steps = collatz(num);
    prinf("%i steps\n", steps)
}

int collatz(int n)
{
    if (n == 1)
        return 0;
    // return 1 + because it's definitely taking at least one step
    else if ((n % 2) == 0)
        return 1 + collatz(n/2);
    else
        return 1 + collatz(3*n + 1);
}