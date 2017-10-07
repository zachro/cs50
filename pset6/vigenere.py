import sys

def get_key_digit(key_char):
    
    if key_char in UPPER_CHARS:
        return UPPER_CHARS.index(key_char)
    elif key_char in LOWER_CHARS:
        return LOWER_CHARS.index(key_char)
    else:
        exit(4)
        
def encrypt_char(input_char, key):
    # if upper case
    if input_char in UPPER_CHARS:
        input_index = UPPER_CHARS.index(input_char)
        cipher_index = input_index + key
        while cipher_index >= 26:
            cipher_index -= 26
        return UPPER_CHARS[cipher_index]
    # if lower case
    elif input_char in LOWER_CHARS:
        input_index = LOWER_CHARS.index(input_char)
        cipher_index = input_index + key
        while cipher_index >= 26:
            cipher_index -= 26
        return LOWER_CHARS[cipher_index]
    # if not alphabetical character
    else:
        return input_char
        
def is_valid_input(string):
    for c in string:
        if c not in UPPER_CHARS and c not in LOWER_CHARS:
            return False
    return True
        
# STATIC VARIABLES
UPPER_CHARS = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
LOWER_CHARS = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: vigenere <keyword>")
        exit(2)
    
    # get keyword, validate, and convert to digits
    keyword = sys.argv[1]
    if not is_valid_input(keyword):
        print("Keyword must consist of only alphabetical characters")
        exit(3)
    key = []
    for c in keyword:
        key.append(get_key_digit(c))
    
    # get message to be encrypted
    original_message = input("Plaintext: ")
    
    # iterate through message and encrypt each character
    ciphertext = []
    key_index = 0
    for c in original_message:
        if key_index == len(key):
            key_index = 0
        ciphertext.append(encrypt_char(c, key[key_index]))
        if ciphertext[-1] != c or key[key_index] == 0:
            key_index += 1
            
    # print out ciphertext
    print("Ciphertext: " + ''.join(ciphertext))