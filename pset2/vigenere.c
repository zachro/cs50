#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int getLength(char inputArray[]);
int findIndex(char inputChar, char inputArray[]);
char getKeyDigit(char keyChar);
char encryptChar(char inputChar, int key);
bool isValidInput(string inputString);


int main(int argc, string argv[])
{
    // make sure right amount of arguments
    if (argc > 3 || argc < 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    //get keyword, validate, and convert to digits
    string keyword = argv[1];
    if (!isValidInput(keyword))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    int keyLength = strlen(keyword);
    int key[keyLength];
    for (int i = 0; i < keyLength; i++)
    {
        key[i] = getKeyDigit(keyword[i]);
    }
    
    // Get message to be encrypted
    printf("plaintext: ");
    string originalMessage = get_string();
    int messageLength = strlen(originalMessage);
    
    char ciphertext[messageLength];
    // iterate through message and encrypt each character
    int keyIndex = 0;
    for (int i = 0; i < messageLength; i++)
    {
        if (keyIndex == keyLength) {
            keyIndex = 0;
        }
        ciphertext[i] = encryptChar(originalMessage[i], key[keyIndex]);
        if (ciphertext[i] != originalMessage[i] || key[keyIndex] == 0)
        {
            keyIndex++;
        }
    }
    
    // print out ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < messageLength; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    return 0;
}

int getLength(char inputArray[])
{
    int counter = 0;
    while (inputArray[counter])
    {
        counter++;
    }
    return counter;
}

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

char getKeyDigit(char keyChar)
{
    char upperChars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char lowerChars[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    // if upper case
    if (keyChar >= 65 && keyChar <= 90)
    {
        return findIndex(keyChar, upperChars);
    }
    // if lower case
    else if (keyChar >= 97 && keyChar <= 122)
    {
        return findIndex(keyChar, lowerChars);
    }
    else
    {
        return '1';
    }
}

// take in plaintext char and return ciphertext char
char encryptChar(char inputChar, int key)
{
    char upperChars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char lowerChars[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
    // if upper case
    if ((int) inputChar >= 65 && (int) inputChar <= 90)
    {
        int inputIndex = findIndex(inputChar, upperChars);
        int cipherIndex = inputIndex + key;
        while (cipherIndex >= 26)
        {
            cipherIndex -= 26;
        }
        return upperChars[cipherIndex];
    }
    // if lower case
    else if ((int) inputChar >= 97 && (int) inputChar <= 122)
    {
        int inputIndex = findIndex(inputChar, lowerChars);
        int cipherIndex = inputIndex + key;
        while (cipherIndex >= 26)
        {
            cipherIndex -= 26;
        }
        return lowerChars[cipherIndex];
    }
    else
    // if not alphabetical character
    {
        return inputChar;
    }
}

bool isValidInput(string inputString)
{
    for (int i = 0, n = strlen(inputString); i < n; i++)
    {
        if ((inputString[i] < 65 || inputString[i] > 122) || (inputString[i] > 90 && inputString[i] < 97))
        {
            return false;
        }
    }
    return true;
}