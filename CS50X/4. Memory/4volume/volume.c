// Modifies the volume of an audio file in .wav format (assumes all samples are 2 bytes)

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
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Error 1: Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Error 2: Could not open output file.\n");
        return 2;
    }

    float factor = atof(argv[3]); //gets desired factor and converts string to a float

    uint8_t *header = malloc (HEADER_SIZE * sizeof (uint8_t)); //allocates temporary space in memory to store the header from the input file.
    fread (header, sizeof(uint8_t), HEADER_SIZE, input); //reads the header
    fwrite (header, sizeof(uint8_t), HEADER_SIZE, output); //writes the header
    free (header); //frees up temporary space

    int16_t *sample = malloc (sizeof(int16_t)); //allocates temporary space in memory to store each sample (2 bytes) from the input file.
    while (fread (sample, sizeof(int16_t), 1, input)) //loops over all samples, until fread returns an error.
    {
        *sample *= factor; //multiplies the sample by factor
        fwrite (sample, sizeof(int16_t), 1, output); //writes new sample to memory
    }
    free (sample); //frees temporary sapce

    // Close files
    fclose(input);
    fclose(output);
}
