#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int p = 0;
    while (start < end)
    {
        int borns = start / 3;
        int dies = start / 4;
        start = (start + borns - dies); // the same would be start += start/12;
        p++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", p);
}
