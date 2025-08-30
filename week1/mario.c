#include <cs50.h>
#include <stdio.h>

void print_row(int n);
void print_space(int n);

int main(void)
{
    int height;
    do
    {
        height = get_int("Enter height: ");
    }
    while (height < 1);

    // print n rows
    for (int col = 1; col <= height; col++)
    {
        print_space(height - col);
        print_row(col);
        printf("  ");
        print_row(col);
        printf("\n");
    }
}

void print_row(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

void print_space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}
