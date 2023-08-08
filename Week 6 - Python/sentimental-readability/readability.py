from cs50 import get_string
import re


def main():
    # Ask the user to type in some text
    input = get_string("Text: ")

    # Calculate grade according to the Coleman-Liau formula
    grade = calculate_grade(input)

    # Output the grade level for the text
    if grade >= 16:
        print(f"Grade: 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade: {grade}")


def calculate_grade(input):
    nb_letters = count_letters(input)
    nb_words = count_words(input)
    nb_sentences = count_sentences(input)

    # L is the average number of letters per 100 words in the text
    L = (nb_letters * 100) / float(nb_words)

    # S is the average number of sentences per 100 words in the text
    S = (nb_sentences * 100) / float(nb_words)

    # Coleman-Liau index is 0.0588 * L - 0.296 * S - 15.8
    index = 0.0588 * L - 0.296 * S - 15.8

    # Return grade level computed by the Coleman-Liau formula, rounded to the nearest integer
    return round(index)


# Count the number of letters in the text
# A letter is any lowercase character from a to z or any uppercase character from A to Z
def count_letters(text):
    return len(re.findall(r"[a-zA-Z]", text))


# Count the number of words in the text
# Any sequence of characters separated by spaces should count as a word
def count_words(text):
    return len(text.split())


# Count the number of sentences in the text
# Any occurrence of a period, exclamation point, or question mark indicates the end of a sentence
def count_sentences(text):
    return len(re.split(r"[.!?]", text)) - 1


if __name__ == "__main__":
    main()
