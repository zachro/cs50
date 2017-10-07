#include <stdio.h>
#include <string.h>
#include <cs50.h>

typedef struct node
{
    bool isWord;
    struct node *children[27];
}
node;

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

void insert(node *root, const char *word);
node *makeNode(void);

int main(void)
{
    node *root = makeNode();
    

    char *filename = "dictionaries/small";
    FILE *infile = fopen(filename, "r");
    char word[45];
    for(int i = 0; i < 45; i++)
    {
        word[i] = '\0';
    }
    int index = 0;
    for(int c = fgetc(infile); c != EOF; c = fgetc(infile))
    {
        if (c == '\n')
        {
            printf("Inserting %s into dictionary\n", word);
            insert(root, word);
            for(int i = 0; i < 45; i++)
            {
                word[i] = '\0';
            }
            index = 0;
        }
        else
        {
            word[index] = c;
            printf("Word = %s\n", word);
            index++;
        }
    }
    
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
    int level;
    int length = strlen(word);
    int index;
    
    node *pCrawl = root;
    
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(word[level]);
        
        if (!pCrawl->children[index])
            pCrawl->children[index] = makeNode();
            
        pCrawl = pCrawl->children[index];
    }
    // Change isWord to true on last node
    pCrawl->isWord = true;
}