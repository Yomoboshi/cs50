#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in JPEG block
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Open file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE]; // Buffer for a block of data
    FILE *img = NULL;           // Pointer for the output JPEG files
    int counter = 0;            // File counter for naming
    char filename[8];           // Filename for output JPEGs

    // cycle through all data by 512B at a time, looking for signatures
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // Check if the block has a JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if not first JPEG
            if (img != NULL)
            {
                fclose(img);
            }

            // Create new filename and open new JPEG file, could be also written as
            // "sprintf(filename, "%03i.jpg", counter++);"
            sprintf(filename, "%03i.jpg", counter);
            counter++;
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create file %s.\n", filename);
                fclose(input);
                return 1; // Error creating output file
            }
        }

        // If a JPEG file is open, write the buffer into it
        if (img != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }

    // Close any remaining open files
    if (input != NULL)
    {
        fclose(input);
    }
    if (img != NULL)
    {
        fclose(img);
    }

    return 0;
}
