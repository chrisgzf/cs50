// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

char* makeLowercase(const char *in);
bool findNode(node *n, const char *s);
void insert(node **hashTable, int hash, node *i);
unsigned int getSize(node *n);

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        node *i = malloc(sizeof(node));
        strcpy(i->word, word);
        i->next = NULL;
        insert(hashtable, hash(word), i);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int nWords = 0;
    for (int i = 0; i < N; i++)
    {
        nWords += getSize(hashtable[i]);
    }
    return nWords;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int wHash = hash(word);
    char *lowered = makeLowercase(word);
    bool found = findNode(hashtable[wHash], lowered);
    free(lowered);
    return found;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *old = hashtable[i];
        node *new = NULL;
        if (!old)
        {
            continue;
        }
        while ((new = old->next))
        {
            free(old);
            old = new;
        }
        free(old);
    }
    return true;
}


// Sets the new node to point at head, set new node to be new head
void insert(node **hashTable, int hash, node *i)
{
    // Haha, somehow this thing handles NULL as well (i.e. when linkedlist is empty)
    i->next = hashTable[hash];
    hashTable[hash] = i;
    return;
}


unsigned int getSize(node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    if (n->next != NULL)
    {
        return getSize(n->next) + 1;
    }
    else
    {
        return 1;
    }
}

bool findNode(node *n, const char *s)
{
    if (n == NULL)
    {
        return false;
    }
    if (!strcmp(n->word, s)) // if this is true, the two strings are equal
    {
        return true;
    }
    else
    {
        // strings are not equal, check for next == NULL
        // if not NULL, recursive call into the next item in the linkedList
        if (n->next == NULL)
        {
            return false;
        }
        else
        {
            return findNode(n->next, s);
        }
    }
}

char* makeLowercase(const char *in)
{
    int len = strlen(in);
    char *lowered = malloc(len + 1); // allocated 1 more space for null terminator
    for (int i = 0; i < len; i++)
    {
        lowered[i] = tolower(in[i]);
    }
    lowered[len] = '\0';
    return lowered;
}
