def is_valid_input(input):
    try:
        int(input)
        return True
    except:
        return False
        
def get_company(cardNumber):
    if cardNumber.startswith('4'):
        return 'VISA'
    elif int(cardNumber[:2]) in range(50,56):
        return 'MASTERCARD'
    elif cardNumber.startswith('31') or cardNumber.startswith('37'):
        return 'AMEX'
        
def sum_doubled_digit(digit):
    doubled = digit * 2
    if doubled < 10:
        return doubled
    else:
        return 1 + (doubled % 10)
        
def toggle_bool(value):
    if value == True:
        return False
    else:
        return True
        
def is_valid_number(card_number):
    sum_doubled_digits = 0
    sum_other_digits = 0
    reversed_card_number = card_number[::-1]
    to_be_doubled = False
    for digit in reversed_card_number:
        if to_be_doubled:
            sum_doubled_digits += sum_doubled_digit(int(digit))
        else:
            sum_other_digits += int(digit)
        to_be_doubled = toggle_bool(to_be_doubled)
    if (sum_doubled_digits + sum_other_digits) % 10 == 0:
        return True
    else:
        return False
    
if __name__ == "__main__":
    card_number = input("Number: ")
    while not is_valid_input(card_number):
        card_number = input("Number: ")
        
    if is_valid_number(card_number):
        print(get_company(card_number))
    else:
        print("INVALID, but company would be {}".format(get_company(card_number)))