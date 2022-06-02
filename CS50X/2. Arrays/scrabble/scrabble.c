#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Determine and print out the winner.
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

//Computes Scrabble score for a word
int compute_score(string word)
{
    int word_length = strlen(word);
    int score = 0;
    int char_as_int = 0;

    //loop examining each character in the word
    for (int i = 0; i < word_length; i++)
    {
        if (isupper(word[i])) // if uppercase i.e. ASCII 65-90
        {
            char_as_int = (int) word[i] - 65; //converts uppercase letters (A-Z) into an int from 1-26
            score = score + POINTS[char_as_int];
        }
        else if (islower(word[i])) // if lowercase i.e. ASCII 97-122
        {
            char_as_int = (int) word[i] - 97; //converts lowercase letters (a-z) into an int from 1-26
            score = score + POINTS[char_as_int];
        }
    }
    return score;
}