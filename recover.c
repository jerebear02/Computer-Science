#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    FILE *output = NULL;

    int file_count = 0;
    bool writing = false;
    char filename[8];

    // Read blocks of 512 bytes
    while (fread(buffer, BLOCK_SIZE, 1, input) == 1)
    {
        // Check for JPEG header
        bool is_jpeg =
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0;

        if (is_jpeg)
        {
            // Close previous file if open
            if (writing)
            {
                fclose(output);
            }

            // Create new JPEG file
            sprintf(filename, "%03i.jpg", file_count);
            output = fopen(filename, "wb");
            if (output == NULL)
            {
                fclose(input);
                return 1;
            }

            file_count++;
            writing = true;
        }

        // Write to output file if currently recovering a JPEG
        if (writing)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }

    // Clean up
    if (output != NULL)
    {
        fclose(output);
    }

    fclose(input);
    return 0;
}
