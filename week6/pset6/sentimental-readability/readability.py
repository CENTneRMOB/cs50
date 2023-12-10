from cs50 import get_string

text = get_string("Text: ")

letters_count = 0
words_count = 1
sentences_count = 0

for char in text:
    lowered = char.lower()
    if (lowered >= "a" and lowered <= "z"):
        letters_count += 1
    elif lowered == " ":
        words_count += 1
    elif lowered == "." or lowered == "!" or lowered == "?":
        sentences_count += 1
    
letters_avg = (letters_count / words_count) * 100
sentences_avg = (sentences_count / words_count) * 100

grade = round((0.0588 * letters_avg) - (0.296 * sentences_avg) - 15.8)

if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before grade 1")
else:
    print(f"Grade {grade}")