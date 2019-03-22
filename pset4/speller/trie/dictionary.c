// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Fn Prototypes
void freeNode(node *n);
void insert(node *n, const char *word);
int getIndex(char c);
int countWordsInTrie(node *n);

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        insert(root, word);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return countWordsInTrie(root);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int len = strlen(word);
    node *n = root;
    for (int i = 0; i < len; i++)
    {
        int index = getIndex(word[i]);
        if (index == -1)
        {
            return false;
        }
        if (n->children[index] == NULL)
        {
            return false;
        }
        n = n->children[index];
    }
    return n->is_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    freeNode(root);
    return true;
}

void insert(node *n, const char *word)
{
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        char c = word[i];
        int index = getIndex(c);
        if (n->children[index] == NULL)
        {
            n->children[index] = calloc(1, sizeof(node));
            // n->children[index]->is_word = false;
        }
        n = n->children[index];
    }
    n->is_word = true;
    return;
}

int getIndex(char c)
{
    if (islower(c))
    {
        return c - 'a';
    }
    else if (isupper(c))
    {
        return c - 'A';
    }
    else if (c == '\'')
    {
        return N - 1;
    }
    else
    {
        return -1;
    }
}

int countWordsInTrie(node *n)
{
    int num = 0;
    if (n != NULL)
    {
        if (n->is_word)
        {
            num++;
        }
        for (int i = 0; i < N; i++)
        {
            if (n->children[i] != NULL)
            {
                num += countWordsInTrie(n->children[i]);
            }
        }
    }
    return num;
}

void freeNode(node *n)
{
    if (n != NULL)
    {
        node *next[N];
        memcpy(next, n->children, sizeof(n->children));
        free(n);
        for (int i = 0; i < N; i++)
        {
            freeNode(next[i]);
        }
    }
    return;
}
