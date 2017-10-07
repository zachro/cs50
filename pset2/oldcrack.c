#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <math.h>
#define _XOPEN_SOURCE

char incrementChar(char inputChar);
string incrementString(string inputString);
int findIndex(char inputChar, char inputArray[]);
int getLength(char inputArray[]);

int main(int argc, string argv[])
{
    // Make sure user has input command-line arguments
    if (argc < 2 || argc > 3) 
    {
        printf("Usage: ./crack hash");
        return 1;
    }

    // Store password hash
    string hashedPassword = argv[1];
    string currentGuess = argv[2];
    //string currentGuess = "A";

    int guesses = 0;
    int maxGuesses = pow(52,strlen(argv[2]));
    while (guesses < maxGuesses)
    {
        string hash = crypt(currentGuess, "50");
        if (strcmp(hash, hashedPassword) == 0)
        {
            printf("%s\n", currentGuess);
            return 0;
        }
        
        currentGuess = incrementString(currentGuess);
        guesses++;
    }

    printf("Password not found\n");
    return 1;
    
}

// Increment an alphabetical character in range 'A' - 'z'
char incrementChar(char inputChar)
{
    char alphaChars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int inputIndex = findIndex(inputChar, alphaChars);
    int outputIndex = inputIndex + 1;
    if (outputIndex == 52)
    {
        outputIndex = 0;
    }
    return alphaChars[outputIndex];
}

// Use incrementChar to numerically increment a string ("AAAA" --> "AAAB"; "sPQz" - "sPRA"; etc.)
string incrementString(string inputString)
{
    int length = strlen(inputString);
    int incIndex = length - 1;
    while (inputString[incIndex] == 'z')
    {
        incIndex--;
    }
    while (incIndex < length)
    {
        inputString[incIndex] = incrementChar(inputString[incIndex]);
        incIndex++;
    }
    return inputString;
}

// Finds the index of a particular char in an array
int findIndex(char inputChar, char inputArray[])
{
    for (int i = 0, n = getLength(inputArray); i < n; i++)
    {
        if (inputArray[i] == inputChar)
        {
            return i;
        }
    }
    return -1;
}

// Gets length of an array of chars
int getLength(char inputArray[])
{
    int counter = 0;
    while (inputArray[counter])
    {
        counter++;
    }
    return counter;
}

string processString(inputString)
{
    length = strlen(inputString);
    string outputString = "";
    outputString = strcat(outputString, inputString);
    return outputString;
}