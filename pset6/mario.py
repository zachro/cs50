
def print_row(is_left, width, height):
    num_blanks = height - width
    if is_left:
        place_blanks(num_blanks)
        place_blocks(width)
    else:
        place_blocks(width)
        print()
        
def place_blocks(num_blocks):
    for i in range(num_blocks):
        print("#", end='')
        
def place_blanks(num_blanks):
    for i in range(num_blanks):
        print(" ", end='')
        
def get_height():
    while True:
        n = int(input("Enter a height for the pyramids: "))
        if n > 0 and n < 23:
            break
    return n

if __name__ == "__main__":
    height = get_height()
    width = 1
    for i in range(height):
        print_row(True, width, height)
        print(" ", end='')
        print_row(False, width, height)
        width += 1