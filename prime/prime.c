#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i)) //ak vrati true, napise cislo
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO
    if (number == 1) return false;
    if (number == 2) return true;
    int i = 2;
    while (i < number)
    {
        if (number % i == 0) return false; //vydel cislom i, ak ho vydeli bezo zvysku, vrat false
        else i++;
    }
    return true;
}
