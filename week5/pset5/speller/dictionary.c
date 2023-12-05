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

// TODO: Choose number of buckets in hash table
const unsigned int N = 1150;

// Hash table
node *table[N];

// Count of words in dictionary
int WORDS_COUNT = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int h = hash(word);
    node *cursor = table[h];

    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            cursor = NULL;
            free(cursor);
            return true;
        }

        cursor = cursor->next;
    }

    cursor = NULL;
    free(cursor);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        sum += toupper(word[i]) - 'A';
    }

    return abs(sum);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open the file");
        return false;
    }

    char str[LENGTH + 1];

    while (fscanf(dict, "%s", str) != EOF)
    {
        node *w = malloc(sizeof(node));
        if (w == NULL)
        {
            unload();
            free(w);
            return false;
        }

        strcpy(w->word, str);
        w->next = NULL;
        // hash a word and get index
        int ind = hash(w->word);

        w->next = table[ind];
        table[ind] = w;

        WORDS_COUNT += 1;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return WORDS_COUNT;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO    
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        free(cursor);
    }

    return true;
}
