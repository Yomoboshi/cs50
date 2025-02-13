#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For strncpy

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");
    // Added to control that file was found and opened.
    if (!infile)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // memory allocation
        plates[idx] = malloc(7 * sizeof(char));

        // Save plate number in array
        strcpy(plates[idx], buffer);

        idx++;
    }

    for (int i = 0; i < sizeof(*plates); i++)
        {
            printf("%s\n", plates[i]);
            free(plates[i]);
        }
    fclose(infile);
}
