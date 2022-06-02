//Implements a Tideman election

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
int candidate_count = 0;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle (int winner, int loser);
string find_winner (void);
bool check_any_wins (int candidate_number);
bool check_any_losses (int candidate_number);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs and list of preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences [i][j]=0;
        }
    }

    int voter_count = get_int("Number of voters: ");

    // Query for votes from each voter i
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[j] is voter's jth preference
        int ranks[candidate_count];

        // Query for each rank j
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            //Update ranks variable & check if invalid vote.
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3; //exits the program. Voting cannot work with invalid votes.
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //check if name matches any candidate
    for (int i=0; i<candidate_count; i++) //loop over all candidates i
    {
        if (strcmp(name,candidates[i])==0) //compare vote to candidate i's name
        {
            //if there's a match
            ranks[rank] = i; // update ranks variable for the rank in question (j in main function) to be candidate i.
            return true; //end the function with no error.
        }
    }
    return false; // if the function hasn't ended yet (i.e. no matches), return an error
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i=0; i<candidate_count-1; i++) //looping over all except last value in ranks
    {
        for (int j=i+1; j<candidate_count; j++) //looping over all values after the value i in ranks (i.e. those ranked lower)
        {
            preferences [ranks[i]][ranks[j]] ++; //adding 1 to the relevant preference count (given by candidate numbers in the relevant ranks i and j)
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other into pairs
void add_pairs(void)
{
    for (int i=0; i<candidate_count-1; i++) //looping over all candidates except last
    {
        for (int j=i+1; j<candidate_count; j++) //looping over all candidates following candidate i. the check below is two-way, so don't need to loop over those preceding candidate i.
        {
            int preference = preferences [i][j] - preferences[j][i];
            if (preference > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preference < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory. Done using a bubble sort since low number of pairs.
void sort_pairs(void)
{
    pair temp; //used as temporary storage to help swap order of pairs during sorting
    bool swaps = false; //used to check if any swaps were made in a pass through

    do //checks if swaps were made in the last pass through. if yes, does another pass through.
    {
        swaps=false;  //swap checker resets at start of pass-through
        for (int i=0; i<pair_count-1; i++) //pass-through all pairs once
        {
            if (preferences[pairs[i].winner][pairs[i].loser]<preferences[pairs[i+1].winner][pairs[i+1].loser]) //check if current pair is in wrong order relative to next one
            {
                //if so, swap the pairs
                temp = pairs[i+1];
                pairs[i+1]=pairs[i];
                pairs[i]=temp;
                //change swaps to true
                swaps=true;
            }
        }
    }
    while (swaps == true);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i=0; i<pair_count; i++) //loop over all pairs (already ordered in strength of victory)
    {
        if(!check_cycle(pairs[i].winner, pairs[i].loser)) //check if locking it creates a cycle
        {
            locked[pairs[i].winner][pairs[i].loser] = true; //if not, lock it.
        }
    }
    return;
}


//checks if there is a cycle created by the current pair being locked. Recursive function.
bool check_cycle (int winner, int loser)
{
    for (int i=0; i<candidate_count; i++) // loop over all candidates
    {
        if (locked[loser][i]==true) // check if the loser beat anyone else
        {
            if (i==winner) // if he beat the winner, we have a cycle. return true; one of the base cases.
            {
                return true;
            }
            else if (check_cycle (winner, i)==true) // if he beat someone else (c), check if there's a cycle between winner and c.
            {
                return true;
            }
        }
    }
    return false; //if the loser didn't beat anyone else, no cycle. the other base case
}

// Print the winner of the election
void print_winner(void)
{
    string winner = find_winner();
    printf ("%s\n",winner);
    return;
}

string find_winner()
{
    string winner = "";
    for (int i=0; i<candidate_count; i++) //check all candidates
    {
        if (check_any_wins(i) && !check_any_losses(i)) //check if the candidate is a source in the Tideman graph i.e. must have won at least 1 locked pair, and not lost any.
        {
            winner = candidates[i];
            break;
        }
    }
    return winner;
}

bool check_any_wins (int candidate_number)
{
    for (int i=0; i<candidate_count; i++)
    {
        if (locked[candidate_number][i]==true)
        {
            return true;
        }
    }
    return false;
}

bool check_any_losses (int candidate_number)
{
    for (int i=0; i<candidate_count; i++)
    {
        if (locked[i][candidate_number]==true)
        {
            return true;
        }
    }
    return false;
}
