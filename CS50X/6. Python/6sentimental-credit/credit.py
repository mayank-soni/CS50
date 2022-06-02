from cs50 import get_string
import re


def main():
    card_number = get_string("Number: ")
    length = len(card_number)
    checksum = luhn(card_number)

    # Set up regular expressions for each of the 3 card number formats, and check if they match the card number given.
    # Also check the checksum

    if checksum != 0:
        print("INVALID")
    elif re.match('3[4,7]\d{13}$', card_number):
        print("AMEX")
    elif re.match('5[1-5]\d{14}$', card_number):
        print("MASTERCARD")
    elif re.match('4(\d{12}|\d{15})$', card_number):
        print("VISA")
    else:
        print("INVALID")


def luhn(number):
    """Calculates checksum based on Luhn's algorithm for a credit card number"""
    even_sum = 0
    length = len(number)

    # Counts backward every 2 digits starting from the 2nd last digit of the card number
    for i in range(length-2, -1, -2):
        even_digit = 2 * int(number[i])
        # Replace even_digit with the sum of its digits if it is > 1 digit long
        if even_digit >= 10:
            even_digit = 1 + even_digit % 10
        even_sum += even_digit

    odd_sum = 0
    for i in range(length-1, -1, -2):
        odd_digit = int(number[i])
        odd_sum += odd_digit

    # Return the last digit of the number
    return (even_sum + odd_sum) % 10


main()