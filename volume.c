// volume.c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 44

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // Open output file
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        fclose(input);
        fprintf(stderr, "Could not create %s.\n", argv[2]);
        return 1;
    }

    // Parse factor
    float factor = atof(argv[3]);

    // Read header from input
    uint8_t header[HEADER_SIZE];
    if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) != HEADER_SIZE)
    {
        fclose(input);
        fclose(output);
        fprintf(stderr, "Could not read WAV header.\n");
        return 1;
    }

    // Write header to output
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Read samples and write adjusted samples
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input) == 1)
    {
        // Scale sample by factor
        int16_t scaled = (int16_t) (sample * factor);

        // Write to output
        fwrite(&scaled, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
