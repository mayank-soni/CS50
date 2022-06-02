def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
# Checks if a vanity licence plate number meets the requirements
    length = len(s)
    # “… vanity plates may contain a maximum of 6 characters (letters or numbers) and a minimum of 2 characters.”
    # “No periods, spaces, or punctuation marks are allowed.”
    if length < 2 or length > 6 or not s.isalnum():
        return False

    # “All vanity plates must start with at least two letters.”
    if not s[0:2].isalpha():
        return False

    # “Numbers cannot be used in the middle of a plate; they must come at the end. For example, AAA222 would be an acceptable … vanity plate; AAA22A would not be acceptable. The first number used cannot be a ‘0’.”
    for i, char in enumerate(s): 
        # Loop stops (after checking the conditions below and returning appropriately) after the first digit
        if char.isdigit():
            if char == '0' or not s[i+1:].isdigit():
                return False
            return True

    return True # Additional return value here if no digits in plate number


if __name__ == "__main__":
    main()