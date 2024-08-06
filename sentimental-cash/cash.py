import cs50


# Takes input
while True:
    dollars = cs50.get_float("Change owed: ")
    if dollars >= 0:
        break
    print("Please enter a non-negative amount.")

# Converts dollars to cents
cents = round(dollars * 100)

# Calculates the minimum number of coins
coins = 0
coins += cents // 25  # Quarters
cents %= 25

coins += cents // 10  # Dimes
cents %= 10

coins += cents // 5   # Nickels
cents %= 5

coins += cents        # Pennies

# Outputs all coins
print(coins)
