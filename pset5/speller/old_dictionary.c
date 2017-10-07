/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

node *root = {false,{NULL}};
int count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int level;
    int length = strlen(word);
    int index;
    char *searchWord = NULL;
    searchWord = strcpy(searchWord, word);
    // Convert word to lower case
    for(int i = 0; i < length; i++)
    {
        searchWord[i] = tolower(word[i]);
    }
    
    node *pCrawl = root;
    
    for(level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(searchWord[level]);
        if (!pCrawl->children[index])
            return false;
        
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isWord);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    printf("About to load dictionary\n");
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
        return false;
    char word[45];
    // Ensure word is completely empty
    for(int i = 0; i < 45; i++)
    {
        word[i] = '\0';
    }
    printf("Created empty word: %s\n", word);
    // Iterate through dictionary list and add each word to trie
    int index = 0;
    for(int c = fgetc(infile); c != EOF; c = fgetc(infile))
    {
        printf("Starting for loop\n");
        if (c == '\n')
        {
            printf("Found end of a word\n");
            insert(root, word);
            for(int i = 0; i < 45; i++)
            {
                word[i] = '\0';
            }
            printf("Added %s to dictionary\n", word);
            count++;
            index = 0;
        }
        else
        {
            word[index] = c;
            index++;
        }
    }
    printf("loaded dictionary\n");
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

// Returns a new node in trie
node *makeNode(void)
{
    node *pNode = NULL;
    
    pNode = (node *)malloc(sizeof(node));
    
    if (pNode)
    {
        pNode->isWord = false;
        
        for(int i = 0; i < 27; i++)
        {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

void insert(node *root, const char *word)
{
    printf("insert(): About to insert %s\n", word);
    int level;
    int length = strlen(word);
    int index;
    
    node *pCrawl = root;
    printf("insert(): About to enter for loop\n");
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(word[level]);
        printf("insert(): index = %i\n", index);
        if (!pCrawl->children[index])
        {
            printf("About to make new node\n");
            pCrawl->children[index] = makeNode();
        }
        printf("insert(): About to move pointer to child node\n");
        pCrawl = pCrawl->children[index];
    }
    // Change isWord to true on last node
    pCrawl->isWord = true;
}