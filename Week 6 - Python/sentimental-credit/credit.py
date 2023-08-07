from cs50 import get_string
import re


def main():
    card_number = get_string("Number: ")

    # Check if the card number is legitimate
    if is_legit(card_number):
        if is_visa(card_number):
            print("VISA")
        elif is_amex(card_number):
            print("AMEX")
        elif is_mastercard(card_number):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def is_mastercard(card_number):
    if len(card_number) == 16:

        # Check card_number starts with 51, 52, 53, 54, 55
        prefixes = ["51", "52", "53", "54", "55"]
        for prefix in prefixes:
            if card_number.startswith(prefix):
                return True


def is_amex(card_number):
    if len(card_number) == 15 and (
        card_number.startswith("34") or card_number.startswith("37")):
        return True


def is_visa(card_number):
    if (len(card_number) == 13 or len(card_number) == 16) and card_number.startswith("4"):
        return True


# Function to check if the card number is legitimate using the Luhn's algorithm
def is_legit(card_number):
    sum = 0
    every_other_digit = card_number[-2::-2]

    # Iterate through every other digit, starting from the second-to-last digit
    for char in every_other_digit:
        product = int(char) * 2
        if product > 9:
            product %= 10
            product += 1
        sum += product

    not_multiplied_digits = card_number[-1::-2]

    # Iterate through the remaining digits
    for char in not_multiplied_digits:
        sum += int(char)

    # Check if the sum is a multiple of 10 (passes the Luhn's algorithm)
    if sum % 10 == 0:
        return True


main()
