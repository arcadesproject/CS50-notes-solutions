#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLATE_SIZE 7
#define PLATES_AMOUNT 8

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into, plates have 6 digits and then NUL
    char buffer[PLATE_SIZE];

    // Create array to store plate numbers
    char *plates[PLATES_AMOUNT];

    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        perror("Error opening file");
        return 1;
    }


    int idx = 0;

    while (fread(buffer, 1, PLATE_SIZE, infile) == PLATE_SIZE)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        char *temp = malloc(sizeof(char) * PLATE_SIZE);
        temp = strcpy(temp, buffer);

        if (idx < PLATES_AMOUNT)
        {
            plates[idx] = temp;
            idx++;
        }

    }

    for (int i = 0; i < idx; i++)
    {
        printf("%s\n", plates[i]);
        free(plates[i]);
    }

    fclose(infile);
}
