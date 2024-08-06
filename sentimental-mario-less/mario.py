import cs50

while True:
    # Takes input
    height = cs50.get_int("Height: ")
    # Checks if 1-8
    if 1 <= height <= 8:
        break  # Exits loop if input is within the valid range
    else:
        print("Please enter a positive integer between 1 and 8.")

# Prints the pyramid
for i in range(1, height + 1):
    print(' ' * (height - i), end='')  # end='' keeps the cursor on the same line
    print('#' * i)
