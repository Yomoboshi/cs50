text = input("Enter text: ")

# Initialize counters
letters, words, sentences = 0, 0, 0

# Count letters
for character in text:
    if character.isalpha():
        letters += 1

# Count words
words = len(text.split())

# Count sentences
last_char = ""
for character in text:
    if character in ".!?":
        if character != last_char:  # Prevent counting "..." as multiple sentences
            sentences += 1
    last_char = character

# Compute averages per 100 words
L = (letters / words) * 100
S = (sentences / words) * 100

# Compute the Coleman-Liau index
index = 0.0588 * L - 0.296 * S - 15.8
rounded_index = round(index)

# Determine readability grade
if rounded_index >= 16:
    print("Grade 16+")
elif rounded_index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {rounded_index}")
