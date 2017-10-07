#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <math.h>
#define _XOPEN_SOURCE

char incrementChar(char inputChar);
void incrementGuess(char inputGuess[]);
int findIndex(char inputChar, char inputArray[]);
int getLength(char inputArray[]);

int main(int argc, string argv[])
{
    // Make sure user has input command-line arguments
    if (argc != 2) 
    {
        printf("Usage: ./crack hash");
        return 1;
    }
    
    // Store password hash
    string hashedPassword = argv[1];
    //char guess[] = {'A','A','A','A'};
    char guessDigits[4][5] = {"A","AA","AAA","AAAA"};
    //char guess[] = "AAAA";
    // string guess = "AAAA";
    
    // Test Code
    // for (int i = 0; i < 120; i++)
    // {
    //     printf("%s\n", incTest);
    //     incrementGuess(incTest);
    // }
    
    int guesses = 0;
    for (int i = 0; i < 4; i++)
    {
        int maxGuesses = pow(53,i + 1);
        string guess = guessDigits[i];
        printf("Attempting %i-character passwords...\n", i + 1);
        while(guesses < maxGuesses + 1)
        {
            string hash = crypt(guess, "50");
            if (strcmp(hash, hashedPassword) == 0)
            {
                printf("Found password in %i attempts.\n", guesses);
                printf("Password: %s\n", guess);
                return 0;
            }
            incrementGuess(guess);
            guesses++;
        }
    }
    printf("Password not found");
}

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

void incrementGuess(char inputGuess[])
{
    int guessIndex = 0;
    while (inputGuess[guessIndex] == 'z')
    {
        guessIndex++;
    }
    while (guessIndex >= 0)
    {
        inputGuess[guessIndex] = incrementChar(inputGuess[guessIndex]);
        guessIndex--;
    }
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