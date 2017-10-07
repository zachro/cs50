#include <stdio.h>
#include <cs50.h>

int getLength(string cardNumber);
string getCompany(string cardNumber);
int charToInt(char character);
bool isEven(int n);
bool validNumber(string cardNumber);
int sumDoubledDigit(int digit);


int main(void)
{
    printf("Number: ");
    string cardNumber = get_string();
    
    if (validNumber(cardNumber)) {
        printf("%s", getCompany(cardNumber));
    }
   
    
}

int getLength(string cardNumber) {
    int length = 0;
    while (cardNumber[length]) {
        length += 1;
    }
    return length;
}

string getCompany(string cardNumber) {
    switch (cardNumber[0]) {
        case '4':
            return "VISA";
        case '5':
            switch (cardNumber[1]) {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                    return "MASTERCARD";
            }
        case '3':
            if (cardNumber[1] == '4' || cardNumber[1] == '7') {
                return "AMEX";
            }
        default:
            return "INVALID";
    }
}

int charToInt(char character) {
    return character;
}

bool isEven(int n) {
    return n % 2 == 0;
}

bool validNumber(string cardNumber) {
    int sumDoubledDigits = 0;
    int sumOtherDigits = 0;
    int length = getLength(cardNumber);
    //If 16 digits...
    if (isEven(length)) {
        for (int i = 0; i < length; i++) {
            if (isEven(i)) {
                sumDoubledDigits += sumDoubledDigit(charToInt(cardNumber[i]));
            } else {
                sumOtherDigits += charToInt(cardNumber[i]);
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            if (!isEven(i)) {
                sumDoubledDigits += sumDoubledDigit(charToInt(cardNumber[i]));
            } else {
                sumOtherDigits += charToInt(cardNumber[i]);
            }
        }
    }
    
    int finalChecksum = sumDoubledDigits + sumOtherDigits;
    if (finalChecksum % 10 == 0) {
        return true;
    } else {
        return false;
    }
}

int sumDoubledDigit(int digit) {
    int result = digit * 2;
    if (result < 10) {
        return result;
    } else {
        return 1 + (result % 10);
    }
}

bool isInteger(string input) {
    for (int i = 0; i < getLength(input); i++) {
        
    }
}