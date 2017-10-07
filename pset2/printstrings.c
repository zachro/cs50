#include <stdio.h>
#include <cs50.h>
#include <string.h>

int getLength(char inputArray[]);
void printArray(char inputArray[]);
void changeArray(char inputArrayp[], char newChar, int index);

int main(void)
{
    char charArray[] = {'a','b','c','d','e'};
    char *pCharArray = charArray;
    printf("%s\n", pCharArray);
}

void changeArray(char inputArray[], char newChar, int index)
{
    inputArray[index] = newChar;
}

void printArray(char inputArray[])
{
    for (int i = 0, n = getLength(inputArray); i < n; i++)
    {
        printf("%c", inputArray[i]);
    }
    printf("\n");
}

// Get length of an array (of type 'char')
int getLength(char inputArray[])
{
    int counter = 0;
    while (inputArray[counter])
    {
        counter++;
    }
    return counter;
}