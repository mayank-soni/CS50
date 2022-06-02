#include <cs50.h>
#include <stdio.h>

// Prints a pyramidal shape of desired size between 2 & 8.

int prompt (int min, int max);
void row (int size, int row_number);

int main(void)
{
    int size = prompt(1,8); //Prompt for desired height of pyramid - save in 'size'

    for (int i=0; i<size; i++) // Do this for each row. number of rows given by 'size'
    {
        row(size, i+1); // 1 is added since i=0 for row number 1
        printf ("\n"); // Go to next row
    }
}

// Prompts for a desired integer height within a given range (inclusive). Repeat prompt if height outside range. Returns the height.
int prompt (int min, int max)
{
    int answer;
    do
    {
        answer = get_int ("Height: ");
    }
    while (answer > max || answer < min);
    return answer;
}

//Print a row containing varying numbers of blanks and '#'s depending on row_number, relative to the overall pyramidal size
void row (int size, int row_number)
{
    //Print appropriate number of blanks
    for (int j=0; j<size-row_number; j++)
    {
        printf (" ");
    }

    //Print appropriate number of '#'s
    for (int j=0; j<row_number; j++)
    {
        printf ("#");
    }

    printf ("  "); // Two spaces between the two sides of the pyramid

    //Print appropriate number of '#'s again
    for (int j=0; j<row_number; j++)
    {
        printf ("#");
    }
}