// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 17576;

// Hash table
node *table[N];

int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word);
    int i = 0;
    node *cursor;

    cursor = table[hash_value];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
            return true;
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number using the indices of the first three letters
//Hash function
    //hash_index
    //[0]           AAA
    //[1]           AAB
    //[2]           AAC
    //[3]           AAD
    //[26]          ABA
    //[52]          ACA
    //[626]         BAA
    //[1252]        CAA
    //[17575]       ZZZ
unsigned int hash(const char *word)
{
    // Ensure that the word is not empty and contains at least three characters.
    if (word == NULL || word[0] == '\0' || word[1] == '\0' || word[2] == '\0')
    {
        return 0; // Return 0 for invalid input.
    }

    // Get the indices of the first three letters (ignoring case).
    unsigned int index_first = toupper(word[0]) - 'A';
    unsigned int index_second = toupper(word[1]) - 'A';
    unsigned int index_third = toupper(word[2]) - 'A';

    // Ensure that the indices are within the range [0, 25].
    index_first %= 26;
    index_second %= 26;
    index_third %= 26;

    // Combine the three indices into a single hash value.
    unsigned int index = (index_first * 26 * 26) + (index_second * 26) + index_third;

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
        return false;

    // Read strings from file one at a time
    int i = 0;
    char buffer[LENGTH + 1];
    while (fscanf(infile, "%s", buffer) != EOF)
    {
        // printf("%s\n", buffer);
        //  Create a new node for each node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
            return false;
        if (!strcpy(new_node->word, buffer))
            return false;

        // Hash word to obtain a hash value
        int index = hash(new_node->word);

        // Insert node into hash table at that location
        new_node->next = table[index];
        table[index] = new_node;
        dict_size++;
    }
    // Close the dictionary file
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = NULL;
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}