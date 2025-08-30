// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
// Bubble sort n^2
// Compares i to i + 1 and swaps if i + 1 higher temp
// void sort_cities(void)
// {
//     int swaps;
//     do
//     {
//         // set swaps = 0 to reset in the loop
//         swaps = 0;
//         for (int i = 0; i < NUM_CITIES - 1; i++)
//         {
//             if (temps[i].temp < temps[i + 1].temp)
//             {
//                 avg_temp temporary = temps[i];
//                 temps[i] = temps[i + 1];
//                 temps[i + 1] = temporary;
//                 swaps++;
//             }
//         }
//     }
//     while (swaps > 0);
// }

// Selection sort n^2
// Finds highest temp then puts into position i
// void sort_cities(void)
// {
//     for (int i = 0; i < NUM_CITIES - 1; i++)
//     {
//         int max_index = i;
//         for (int j = i + 1; j < NUM_CITIES; j++)
//         {
//             if (temps[j].temp > temps[max_index].temp)
//             {
//                 max_index = j;
//             }
//         }

//         if (max_index != i)
//         {
//             avg_temp temporary = temps[i];
//             temps[i] = temps[max_index];
//             temps[max_index] = temporary;
//         }
//     }
// }

// Insertion sort
// compares next index to all previous indexes to then place it at right spot
// Generally used more than bubble sort, fewer swaps and selection is not stable
void sort_cities(void)
{
    for (int i = 1; i < NUM_CITIES; i++)
    {
        avg_temp key = temps[i];
        int j = i - 1;

        // Move elements that are less than key.temp to the right
        while (j >= 0 && temps[j].temp < key.temp)
        {
            temps[j + 1] = temps[j];
            j--;
        }
        temps[j + 1] = key;
    }
}

// Quicksort is often the default in C/C++ standard libraries because of its speed and simplicity.

// Timsort is used in Python and Java because it adapts to partially sorted data and guarantees stability.

// Merge sort is preferred when stability is critical or when working with linked lists.

// Radix and Counting sort shine when sorting integers or strings with fixed formats — especially in performance-critical systems.
