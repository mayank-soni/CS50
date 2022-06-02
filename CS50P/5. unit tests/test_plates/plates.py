def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
# Checks if a vanity licence plate number meets the requirements
    length = len(s)
    if length < 2 or length > 6 or not s.isalnum():
        return False

    if not s[0:2].isalpha():
        return False

    for i, char in enumerate(s): # Loop stops (after checking the conditions below and returning appropriately) after the first digit
        if char.isdigit():
            if char == '0' or (i != length-1 and not s[i+1:].isdigit()):
                return False
            return True

    return True # Additional return value here if no digits in plate number

if __name__ == "__main__":
    main()