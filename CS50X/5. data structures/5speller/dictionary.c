// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int count_words(node *first_node);
bool check_word(node *first_node, const char *checked_word);
bool unload_words(node *first_node);

// TODO: Choose number of buckets in hash table
const unsigned int N = 71546; // went for half the size of the dictionary. seemed to work well.

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int wordhash = 0;
    //hashes the word to know which part of hashtable to check in
    wordhash = hash (word);
    //checks in relevant part of hashtable. See check_word().
    bool check = check_word (table[wordhash], word);
    return check;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    //iterates over every character in the string
    for (int i=0, j=strlen(word); i<j; i++)
    {
        hash = hash * 26 + toupper(word[i]) + 1; //tries to give unique value to each string.
    }
    return hash % N; //modulus by N to ensure the hash fits in the hashtable size.
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //set all hashtable entries to NULL
    for (int i=0; i<N; i++)
    {
        table[i]=NULL;
    }
    //open dictionary
    FILE *dict = fopen(dictionary, "r");

    //check if successfully opened
    if (dict == NULL)
    {
        printf("Could not open dictionary.\n");
        fclose(dict);
        return false;
    }

    //initialise variables to read each word in dictionary
    char dict_entry[LENGTH+1];
    char c;
    unsigned int counter = 0;
    unsigned int wordhash = 0;

    //read one character at a time
    while (fread(&c, sizeof(char), 1, dict))
    {
        //if character is \n (new line), we've reached the end of a word. Otherwise, continue building the word in the dict_entry array.
        if (c!='\n')
        {
            dict_entry[counter] = c;
            counter ++;
        }
        else
        {
            //end the string with a NUL
            dict_entry[counter]='\0';

            //create a new pointer to a node & check if sufficient memory.
            node *new_node = malloc (sizeof(node));
            if (new_node==NULL)
            {
                printf("Not enough memory at %s\n", dict_entry);
                unload ();
                return false;
            }

            //hash the word to know which hash table cell to store it in.
            wordhash = hash (dict_entry);

            //add the new node to the linked list at that hash table cell.
            new_node->next = table[wordhash];
            strcpy (new_node->word, dict_entry);
            table[wordhash] = new_node;

            //reset counter to 0 to use in next word
            counter=0;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    //for every entry in the hash table
    for (int i=0; i<N; i++)
    {
        count += count_words(table[i]);
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool successfulrun;

    //unload each cell of the hash table and check if successful.
    for (int i=0; i<N; i++)
    {
        successfulrun=unload_words(table[i]);
        if (!successfulrun)
        {
            return false;
        }
    }
    return true;
}

unsigned int count_words(node *first_node)
{
    //Recursively defined function to count the number of nodes in a linked list. The address of the first node is in table_cell.
    //Base case 1:      Table_cell is NULL = No linked list exists. Return 0;
    //Base case 2:      Table_cell is non-NULL (links to Node A), but the address in Node A is NULL. There are no more nodes after Node A.
    //                  Return 1 (i.e. count Node A).
    //Recursive case:   Table_cell is non-NULL (links to Node A), and the address in Node A is also non-NULL (links to Node B).
    //                  Return 1 (i.e. the count of Node A) + the return from calling the function again (with address of Node B).

    //Base case 1
    if (first_node==NULL)
    {
        return 0;
    }

    //Base case 2
    if (first_node->next == NULL)
    {
        return 1;
    }
    //Recursive case
    else
    {
        return 1+count_words(first_node->next);
    }
}

bool check_word(node *first_node, const char *checked_word)
{
    //Similar recursive function to count_words(), except this time it checks whether the value is the node is the checked_word, rather than just
    //counting.

    if (first_node==NULL)
    {
        return false;
    }
    if (first_node->next == NULL)
    {
        if (strcasecmp(first_node->word,checked_word)==0)
        {
            return true;
        }
        return false;
    }
    else
    {
        if (strcasecmp(first_node->word,checked_word)==0)
        {
            return true;
        }
        return check_word(first_node->next,checked_word);
    }
}

bool unload_words(node *first_node)
{
    //Similar recursive function to count_words(), except this time it removes the node, rather than counting it.
    bool returnvalue = false;
    if (first_node==NULL)
    {
        returnvalue=true;
    }
    else if (first_node->next == NULL)
    {
        free (first_node);
        returnvalue=true;
    }
    else if(unload_words(first_node->next))
    {
        free (first_node);
        returnvalue=true;
    }
    return returnvalue;
}