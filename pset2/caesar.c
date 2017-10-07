#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int getLength(char inputArray[]);
int findIndex(char inputChar, char inputArray[]);
int formatKey(int k);
char encryptChar(char inputChar, int k);
int stringToInt(string inputString);

int main(int argc, string argv[])
{
    if (argc > 3 || argc < 2)
    {
        printf("Usage: ./caesar [positive integer]\n");
        return 1;
    }
    int key = stringToInt(argv[1]);
    printf("plaintext: ");
    string originalMessage = get_string();
    int messageLength = strlen(originalMessage);
    char ciphertext[messageLength];
    // iterate through message and encrypt each character
    for (int i = 0; i < messageLength; i++)
    {
        ciphertext[i] = encryptChar(originalMessage[i], key);
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

int formatKey(int k)
{
    if (k < 26)
    {
        return k;
    }
    else
    {
        return k % 26;
    }
}

// take in plaintext char and return ciphertext char
char encryptChar(char inputChar, int k)
{
    char upperChars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char lowerChars[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
    // if upper case
    if ((int) inputChar >= 65 && (int) inputChar <= 90)
    {
        int inputIndex = findIndex(inputChar, upperChars);
        int cipherIndex = inputIndex + formatKey(k);
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
        int cipherIndex = inputIndex + formatKey(k);
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

int stringToInt(string inputString)
{
    int length = strlen(inputString);
    int result = 0;
    int power = length - 1;
    for (int i = 0; i < length; i++)
    {
        result += (inputString[i] - '0') * pow(10,power);
        power -= 1;
    }
    return result;
}