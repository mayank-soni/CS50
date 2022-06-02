// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a trie
typedef struct node
{
    bool endshere[27];
    struct node *next[27];
}
node;

void add_to_trie(char *word, node *trie_element);
unsigned int size_of_trie (node *trie_head);
bool unload_trie (node *trie_head);
bool check_trie (node *trie_element, char *word);

node *trie_head;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char checked_word[LENGTH+1];
    strcpy (checked_word, word);
    bool check = check_trie (trie_head, checked_word);

    return check;
}

bool check_trie (node *trie_element, char *word)
{
    int letter = 0;
    if (isalpha(word[0]))
    {
        letter = toupper(word[0])-'A';
    }
    else
    {
        letter = 26;
    }
    if (strlen(word)==1)
    {
        if (trie_element->endshere[letter]==true )
        {
            return true;
        }
        return false;
    }
    if (trie_element->next[letter]!=NULL)
    {
        word = &word[1];
        return check_trie (trie_element->next[letter], word);
    }
    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    trie_head = malloc (sizeof(node));
    //reset the trie_head
    for (int i=0; i<27; i++)
    {
        trie_head->endshere[i]=false;
        trie_head->next[i]=NULL;
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
            add_to_trie(dict_entry,trie_head);
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

    count = size_of_trie (trie_head);

    return count;
}

unsigned int size_of_trie (node *trie_element)
{
    unsigned int count = 0;

    for (int i=0; i<27; i++)
    {
        if (trie_element->endshere[i] == true)
        {
            count ++;
        }
        if (trie_element->next[i] != NULL)
        {
            count += size_of_trie (trie_element->next[i]);
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    unload_trie (trie_head);

    return true;
}

bool unload_trie (node *trie_element)
{
    for (int i=0; i<27; i++)
    {
        if (trie_element->next[i] != NULL)
        {
            unload_trie (trie_element->next[i]);
        }
    }
    free (trie_element);
    return true;
}

void add_to_trie(char *word, node* trie_element)
{
    int letter = 0;
    if (isalpha (word[0]))
    {
        letter = toupper(word[0])-'A';
    }
    else
    {
        letter=26;
    }
    int length = strlen(word);
    if (length==1)
    {
        trie_element->endshere[letter] = true;
    }
    else if (trie_element->next[letter] == NULL)
    {
        trie_element->next[letter] = malloc (sizeof(node));
        if (trie_element->next[letter] == NULL)
        {
            printf("Not enough memory at %s", word);
            unload();
        }
        word = &word[1];
        add_to_trie (word, trie_element->next[letter]);
    }
    else
    {
        word = &word[1];
        add_to_trie (word, trie_element->next[letter]);
    }
}
