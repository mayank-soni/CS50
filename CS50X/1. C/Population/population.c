#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int initial_population = 0;
    int desired_population = 0;
    int years = 0;

    do
    {
        initial_population = get_int ("Initial Population (more than or equal to 9): ");
    }
    while (initial_population < 9);

    // TODO: Prompt for end size
    do
    {
        desired_population = get_int ("Desired Population (more than or equal to initial): ");
    }
    while (desired_population < initial_population);

    // TODO: Calculate number of years until we reach threshold
    while (initial_population < desired_population)
    {
        years ++;
        initial_population = initial_population + (initial_population / 3) - (initial_population / 4 );
    }

    // TODO: Print number of years
    printf ("Years required to reach: %i\n", years);
}
