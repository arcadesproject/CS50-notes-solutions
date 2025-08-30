// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    // input represents name of audio file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // output represents name of new generated audio file
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // factor is amount the volume of original file should be scaled
    // e.g. 2.0 doubles volume
    // atof is string to double
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(header), 1, input);
    fwrite(header, sizeof(header), 1, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
