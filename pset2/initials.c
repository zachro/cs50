#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int countNames(string inputString);

int main(void) 
{
    string fullName = get_string();
    int nameLength = strlen(fullName);
    int nameCount = countNames(fullName);
    char initials[nameCount];
    //printf("initials starts at: %s\n", initials);
    char prevChar = ' ';
    int initialsIndex = 0;
    for (int i = 0; i < nameLength; i++) 
    {
        //printf("Start of iteration %i: prevChar = %c, fullName[i] = %c, initials = %s\n", i, prevChar, fullName[i], initials);
        if (fullName[i] != ' ' && prevChar == ' ')
        {
            initials[initialsIndex] = toupper(fullName[i]);
            initialsIndex++;
            //printf("initials is now %s\n", initials);
        }
        prevChar = fullName[i];
        //printf("End of iteration %i: prevChar = %c, fullName[i] = %c, initials = %s\n", i, prevChar, fullName[i], initials);
    }
    for (int i = 0; i < nameCount; i++)
    {
        printf("%c", initials[i]);
    }
    printf("\n");
}

int countNames(string inputString)
{
    int counter = 0;
    char prevChar = ' ';
    for (int i = 0, n = strlen(inputString); i < n; i++)
    {
        if (prevChar == ' ' && inputString[i] != ' ')
        {
            counter++;
        }
        prevChar = inputString[i];
    }
    return counter;
}

