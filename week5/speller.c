// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

bool in_table(node *n, const char *word);
void empty_list(node *n);

// TODO: Choose number of buckets in hash table
// 26 default based on alphabet but need more really
const unsigned int N = 19391;

// Hash table
node *table[N];

// Track size of dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to get hash value
    int hash_value = hash(word);
    // Lookup hash table using nodes
    return in_table(table[hash_value], word);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    unsigned int bucket = 0;
    for (int i = 0; i < 13 && word[i] != '\0'; i++)
    {
        char c = toupper(word[i]);
        bucket += c * (i + 1);
    }
    return bucket % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }
    // Read each word in the file
    char buffer[LENGTH + 1];
    while (fscanf(input, "%s", buffer) == 1)
    {
        // Add each word to the hash table
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, buffer);
        int hash_value = hash(new_node->word);
        new_node->next = table[hash_value];
        table[hash_value] = new_node;
        dict_size++;
    }
    // Close the dictionary file
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Check if dictionary loaded by using counter
    if (dict_size)
    {
        return dict_size;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        empty_list(table[i]);
        table[i] = NULL;
    }

    dict_size = 0;
    return true;
}

// Recursive version
// bool in_table(node *n, const char *word)
// {
//     // Base case node does not exist
//     if (n == NULL)
//     {
//         return false;
//     }

//     // If found return true
//     if (strcasecmp(n->word, word) == 0)
//     {
//         return true;
//     }

//     // Recursive case
//     else
//     {
//         return in_table(n->next, word);
//     }
// }

// Iteration version, no stack overflow issue?
bool in_table(node *n, const char *word)
{
    for (node *c = n; c != NULL; c = c->next)
    {
        if (strcasecmp(c->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Recursive version
// void empty_list(node *n)
// {
//     // Base case at empty list
//     if (n == NULL)
//     {
//         return;
//     }

//     // Save pointer before freeing
//     node *next = n->next;
//     free(n);

//     // Recursive case
//     empty_list(next);
// }

void empty_list(node *n)
{
    while (n != NULL)
    {
        node *next = n->next;
        free(n);
        n = next;
    }
}
