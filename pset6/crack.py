import sys, crypt

def find_index(input_value, input_list):
    for i in range(len(input_list)):
        if input_list[i] == input_value:
            return i
    exit(3)

def increment_char(input_char):
    char_mapping = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    input_index = find_index(input_char, char_mapping)
    output_index = input_index + 1
    if output_index == 52:
        output_index = 0
    return char_mapping[output_index]
    
def increment_guess(input_guess):
    guess_index = 0
    while input_guess[guess_index] == 'z':
        guess_index += 1
        if guess_index >= len(input_guess):
            guess_index -= 1
            break
            
    while guess_index >= 0:
        input_guess[guess_index] = increment_char(input_guess[guess_index])
        guess_index -= 1
    return input_guess
    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: crack hash")
        exit(2)
        
    hashed_password = sys.argv[1]
    
    starting_guesses = [['A'],['A','A'],['A','A','A'],['A','A','A','A']]
    guess_count = 0
    for i in range(4):
        max_guesses = 52**(i + 1)
        print("Max guesses: {}".format(max_guesses))
        guess = starting_guesses[i]
        print("Attempting {}-character passwords...".format(i + 1))
        
        while guess_count < max_guesses + 1:
            guess_hash = crypt.crypt(''.join(guess), "50")
            if guess_hash == hashed_password:
                print("Found password in {} attempts.".format(guess_count))
                print("Password: {}".format(''.join(guess)))
                exit(0)
            
            guess = increment_guess(guess)
            guess_count += 1
    
    print("Password not found")