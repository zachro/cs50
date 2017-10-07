#include <stdio.h>
#include <cs50.h>

bool isValidInput(string input);
string getCompany(string cardNumber);
int sumDoubledDigit(int digit);
bool toggleBool(bool value);
bool isValidNumber(string cardNumber);
string getFirstDigits(string inputString, int numDigits);
int getLength(string inputString);
string reverseString(string inputString);
int charToInt(char character);

int main(void)
{
    printf("Number: ");
    string cardNumber = get_string();
    while (!isValidInput(cardNumber)) {
        printf("Retry: ");
        cardNumber = get_string();
    }
    
    if (isValidNumber(cardNumber)) {
        printf("%s\n", getCompany(cardNumber));
    } else {
        printf("INVALID\n");
    }
}

int getFirstTwoDigits(string inputString) {
    int firstTwo = (10 * charToInt(inputString[0])) + charToInt(inputString[1]);
    return firstTwo;
}

string getCompany(string cardNumber) {
    int firstTwo = getFirstTwoDigits(cardNumber);
    if (firstTwo >= 40 && firstTwo < 50) {
        return "VISA";
    } else if (firstTwo > 50 && firstTwo <= 55) {
        return "MASTERCARD";
    } else if (firstTwo == 31 || firstTwo == 37) {
        return "AMEX";
    } else {
        return "INVALID";
    }
}

int sumDoubledDigit(int digit) {
    int doubled = digit * 2;
    if (doubled < 10) {
        return doubled;
    } else {
        return 1 + (doubled % 10);
    }
}

bool toggleBool(bool value) {
    if (value == true) {
        return false;
    } else {
        return true;
    }
}

bool isValidNumber(string cardNumber) {
    int length = getLength(cardNumber);
    int sumDoubledDigits = 0;
    int sumOtherDigits = 0;
    //Reverse order of Card Number so digits can be easily alternated
    char reversedCardNumber[length];
    int reversedIndex = length - 1;
    for (int i = 0; i < length; i++) {
        reversedCardNumber[i] = cardNumber[reversedIndex];
        reversedIndex -= 1;
    }
    //Calculate checksum
    bool toBeDoubled = false;
    for (int i = 0; i < length; i++) {
        if (toBeDoubled) {
            sumDoubledDigits += sumDoubledDigit(charToInt(reversedCardNumber[i]));
        } else {
            sumOtherDigits += charToInt(reversedCardNumber[i]);
        }
        toBeDoubled = toggleBool(toBeDoubled);
    }
    if ((sumDoubledDigits + sumOtherDigits) % 10 == 0) {
        return true;
    } else {
        return false;
    }
}

int getLength(string inputString) {
    int length = 0;
    while (inputString[length]) {
        length += 1;
    }
    return length;
}

int charToInt(char character) {
    return character - '0';
}

bool isValidInput(string input) {
    int length = getLength(input);
    int digitCount = 0;
    for (int i = 0; i < length; i++) {
        if (input[i] >= 48 && input[i] <= 57) {
            digitCount += 1;
        } else {
            return false;
        }
    }
    if (digitCount > 0) {
        return true;
    } else {
        return false;
    }
}