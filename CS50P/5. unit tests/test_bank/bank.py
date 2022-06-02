# Prints the amount to pay out ($0, $20, $100) depending on the greeting input by user, a la Seinfeld S07E24

def main():
    greeting = input("Greeting: ")
    amount = value(greeting)
    print(f"${amount}")

def value(greeting):
    greeting = greeting.lower().strip()
    try:
        if greeting[0:5] == "hello":
            return 0
        elif greeting[0] == "h":
            return 20
        else:
            return 100
    except IndexError:
        return 100

if __name__ == "__main__":
    main()