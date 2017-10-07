#include <stdio.h>
#include <cs50.h>

void placeBlocks(int numBlocks);
void placeBlanks(int numBlanks);
void printRow(bool isLeft, int width, int height);
int getHeight();

int main(void)
{
    int height = getHeight();
    int width = 1;
    for (int i = 0; i < height; i++)
    {
        printRow(true, width, height);
        printf("  ");
        printRow(false, width, height);
        width += 1;
    }
}

void printRow(bool isLeft, int width, int height)
{
    int numBlanks = height - width;
    if (isLeft)
    {
        placeBlanks(numBlanks);
        placeBlocks(width);
    }
    else
    {
        placeBlocks(width);
        printf("\n");
    }
}

void placeBlocks(int numBlocks)
{
    for (int i = 0; i < numBlocks; i++)
    {
        printf("#");
    }
}

void placeBlanks(int numBlanks)
{
    for (int i = 0; i < numBlanks; i++)
    {
        printf(" ");
    }
}

int getHeight()
{
    int n;
    do
    {
        printf("Enter a height for the pyramids: ");
        n = get_int();
    }
    while (n < 0 || n > 23);
    return n;
}