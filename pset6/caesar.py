import sys

def encrypt_char(input_char, k):
    """Encrypts single character using Caesar's cipher. Assumes k is a positive int"""
    if len(input_char) > 1:
        print('encrypt_char expects single-character argument')
        exit(3)
    
    upper_chars = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    lower_chars = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    
    # encrypt upper-case character
    if input_char in upper_chars:
        input_index = upper_chars.index(input_char)
        cipher_index = input_index + format_key(k)
        while cipher_index >= 26:
            cipher_index -= 26
        return upper_chars[cipher_index]
    # encrypt lower-case character
    elif input_char in lower_chars:
        input_index = lower_chars.index(input_char)
        cipher_index = input_index + format_key(k)
        while cipher_index >= 26:
            cipher_index -= 26
        return lower_chars[cipher_index]
    # leave non-alphabetical characters unencrypted
    else:
        return input_char
            
def format_key(k):
    if k < 26:
        return k
    else:
        return k % 26

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print('Usage: caesar <positive integer>')
        exit(2)
        
    key = int(sys.argv[1])
    original_message = input('Plaintext: ')
    
    ciphertext = []
    
    # iterate through message and encrypt each character
    index = 0
    for c in original_message:
        ciphertext.append(encrypt_char(original_message[index], key))
        index += 1
    
    ciphertext_output = ''.join(ciphertext)
    
    print("Ciphertext: {}".format(ciphertext_output))