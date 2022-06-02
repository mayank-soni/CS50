def main():
# Obtains input from user, runs convert() on it, and prints it out
    message = input("What is the message? ")
    print(convert(message))


def convert(message):
# Takes a string as input and converts ":)" and ":(" emoticons into the corresponding emoji
    return message\
            .replace(":)","\N{slightly smiling face}")\
            .replace(":(","\N{slightly frowning face}")

if __name__ == "__main__":
    main()