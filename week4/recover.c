#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Expect exactly one argument: the input forensic image
    if (argc != 2)
    {
        printf("Usage: ./recover forensic-image-file\n");
        return 1;
    }

    // Open input file
    char *input_name = argv[1];
    FILE *input_file = fopen(input_name, "r");
    if (input_file == NULL)
    {
        printf("Could not open %s\n", input_name);
        return 1;
    }

    // FAT file systems use 512-byte blocks
    const int block_size = 512;
    uint8_t buffer[block_size];

    int jpeg_count = 0;
    FILE *output_file = NULL;

    // Read the card, block by block
    while (fread(buffer, 1, sizeof(buffer), input_file) == block_size)
    {
        // Check for JPEG signature (0xff 0xd8 0xff e0–ef)
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already writing a JPEG, close it
            if (output_file)
            {
                fclose(output_file);
            }

            // Create a new JPEG file
            char output_name[8]; // "000.jpg" + '\0'
            sprintf(output_name, "%03i.jpg", jpeg_count++);
            output_file = fopen(output_name, "w");
            if (output_file == NULL)
            {
                printf("Could not create %s\n", output_name);
                fclose(input_file);
                return 1;
            }
        }

        // If we have an open JPEG, write this block to it
        if (output_file)
        {
            fwrite(buffer, 1, sizeof(buffer), output_file);
        }
    }

    // Close any remaining open files
    if (output_file != NULL)
    {
        fclose(output_file);
    }
    fclose(input_file);

    return 0;
}
