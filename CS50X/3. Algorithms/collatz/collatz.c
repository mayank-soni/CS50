// Recursively checks Collatz conjecture for given n

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int collatz (int n);
int power (int base, int exponent);

int main (int argc, string argv[])
{
    int n = 0;
    if (argc!=2)
    {
        printf ("Usage: collatz integer\n");
        return 1;
    }

    int length = strlen (argv[1]);

    //converts the argument passed in as a string into an integer. Does not do much error-checking :)
    for (int i = 0; i<length; i++)
    {
        n += ((argv[1][i]-'0')*power(10,length-i-1));
    }

    printf ("%i\n",n);
    printf ("%i\n",collatz (n));

}

//calculates base^exponent recursively.
int power (int base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    if (exponent == 1)
    {
        return base;
    }
    else if (exponent > 1)
    {
        return base * power(base, exponent-1);
    }
    else
    {
        return 0;
    }
}

int collatz (int n)
{
    if (n==0)
    {
        return -1;
    }
    if (n==1)
    {
        return 0;
    }
    else if (n%2==0)
    {
        return (1 + collatz (n/2));
    }
    else
    {
        return (1 + collatz (3*n+1));
    }
}