//Prints out appropriate reading grade level for a text, based on Coleman-Liau Index

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isletter(char a);
int isendofsentence (char a);
int ischaracter (char a);
float CL (int n_letters, int n_words, int n_sentences);

int main (void)
{
    string text = get_string ("Text:");
    int n_chars = strlen (text);
    int n_letters = 0;
    int n_words = 1; // starts at 1 to include the last word in the text.
    int n_sentences = 0;
    for (int i=0; i<n_chars; i++)
    {
        if (isletter(text[i]))
        {
            n_letters++;
        }
        else if (isendofsentence(text[i]))
        {
            n_sentences++;
        }
        //space with a character on either side = word. n_words starts at 1 to ensure the last word in the text is accounted for.
        else if (text[i] == 32 && ischaracter (text[i-1]) && ischaracter (text[i+1]))
        {
            n_words++;
        }
    }
    float index = CL (n_letters, n_words, n_sentences);
    int grade = (int) (index+0.5); //round to nearest integer grade
    if (grade >=16)
    {
        printf ("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf ("Before Grade 1\n");
    }
    else
    {
        printf ("Grade %i\n", grade);
    }
}

int isletter (char a)
{
    if (isupper(a) || islower(a))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isendofsentence (char a)
{
    if ((a==33 || a==46 || a==63)) //ASCII characters for ".", "!", and "?"
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ischaracter (char a)
{
    if (a>32 && a<127) // all the actual characters that might be used in a sentence.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

float CL (int n_letters, int n_words, int n_sentences)
{
    float L = (float) n_letters/ (float) n_words * 100; //casting to float to ensure the decimal places from the division are captured.
    float S = (float) n_sentences/ (float) n_words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}