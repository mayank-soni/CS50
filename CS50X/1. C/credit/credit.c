// Given a credit card number, checks if it is valid and returns which company issued it

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int number_of_digits (long number);
int luhn (long card_number);
int first_two_digits (long number);
int get_xth_digit_from_last (long number, int x);

int main(void)
{
    long card_number = get_long ("Number: ");
    int n_digits = number_of_digits (card_number);
    int first_two = first_two_digits (card_number);
    int checksum = luhn (card_number);

    //AMEX
    if (checksum == 0 && n_digits == 15 && (first_two == 34 || first_two == 37))
    {
        printf ("AMEX\n");
    }

    //MASTERCARD
    else if (checksum == 0 && n_digits == 16 && first_two <=55 && first_two >=51)
    {
        printf ("MASTERCARD\n");
    }

    //VISA
    else if (checksum == 0 && (n_digits == 13 || n_digits == 16) && first_two >=40 && first_two <=49)
    {
        printf ("VISA\n");
    }

    else
    {
        printf ("INVALID\n");
    }
}

int luhn (long card_number) //calculates the checksum for a card number
{
    int n_digits = number_of_digits (card_number);
    int even = 0;
    int odd = 0;
    for (int i=2; i<=n_digits; i+=2) //goes to every even numbered digit (counting from the right)
    {
        int x = 2 * get_xth_digit_from_last (card_number, i);
        switch (x) // Since there are only a few cases, I do this manually.
            {
            case 10:
                x = 1;
                break;
            case 12:
                x = 3;
                break;
            case 14:
                x = 5;
                break;
            case 16:
                x = 7;
                break;
            case 18:
                x = 9;
                break;
            default:
                break;
        }
        even = even + x; //adds the latest digit in the for loop to a rolling sum.
    }

    for (int i=1; i<=n_digits; i+=2) //does the logic for the odd-numbered digits (counting from the right)
    {
        int x = get_xth_digit_from_last (card_number, i);
        odd = odd + x;
    }

    return (odd+even) % 10; //this takes the last digit of the sum, which is the only thing that's relevant.
}

//Counts number of digits in a long integer.
int number_of_digits (long number)
{
    int n_digits=0;
    while (number>=1)
    {
        n_digits++;
        number/=10; //effectively removes the right-most digit  - since fractions aren't supported (just truncated)
    }
    return n_digits;
}

//returns the first 2 digits of a long integer
int first_two_digits (long number)
{
    while (number >=100)
    {
        number = number/10; //effectively removes the right-most digit
    }
    return number;
}

//Gets the xth digit from the right
int get_xth_digit_from_last (long number, int x)
{
    for (int i=0; i<x-1; i++)
    {
        number = number/10; //removes the last digit.
    }
    number = number % 10; //removes all the preceding digits.
    return number;
}