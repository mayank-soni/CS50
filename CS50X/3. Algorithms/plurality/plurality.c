//Implements a plurality voting system

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void identify_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2) // check to ensure at least 1 candidate was input.
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

        candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) // populate candidate list from command line arguments.
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Update vote count & check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i=0; i<candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name)==0) // check all candidates, and if there's a match, add a vote to their total, and break out of the function.
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false; // if not broken out of function yet (i.e. no candidate matched the vote), it was an invalid vote.
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int lowest_winner = candidate_count-1; //used in case of ties.

    identify_winner();

    for (int i = candidate_count-1; i > 0; i--) // in case of ties, determine which is the smallest candidate number tied for top place
    {
        if (candidates[i].votes==candidates[i-1].votes)
        {
            lowest_winner-=1;
        }
        else
        {
            break;
        }
    }

    for (int i=lowest_winner; i<candidate_count; i++) // print all candidates from the smallest candidate number tied for top place
    {
        printf("%s\n",candidates[i].name);
    }

    return;
}

//sorts list of candidates by number of votes (ascending order). Uses bubble sort - since small number of candidates (<=9), this is fastest.
void identify_winner (void)
{
    candidate temp; //used as temporary storage to help swap order of candidates during sorting
    bool swaps = false; //used to check if any swaps were made in a pass through

    do //checks if swaps were made in the last pass through. if yes, does another pass through.
    {
        swaps=false;  //swap checker resets at start of pass-through
        for (int i=0; i<candidate_count-1; i++) //pass-through loop
        {
            if (candidates[i].votes > candidates[i+1].votes) //check if current candidate is in wrong order relative to next one
            {
                //if so, swap the candidates
                temp = candidates[i+1];
                candidates[i+1]=candidates[i];
                candidates[i]=temp;
                //change swaps to true
                swaps=true;
            }
        }
    }
    while (swaps == true);
}