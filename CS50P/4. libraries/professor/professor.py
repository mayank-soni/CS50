# Simulates little professor toy. 

import random


def main():
    level = get_level()

    n_correct = 0 # Counter for total score
    for _ in range (10): # 10 problems in total
        int1 = generate_integer(level) # Generate the problem
        int2 = generate_integer(level)
        n_guesses = 0
        for n_guesses in range(3):
            try:
                answer = int(input(f"{int1} + {int2} = "))
            except TypeError: # if answer entered is not an integer
                print("EEE")
                n_guesses += 1
            else:
                if answer != int1 + int2:
                    print("EEE")
                    n_guesses += 1
                else:
                    n_correct += 1
                    break # Stop asking for guesses once correct answer entered.
                if n_guesses == 3: #
                    print (f"{int1} + {int2} = {int1+int2}") # Provide correct answer once 3 guesses used.
    print (f"Score: {n_correct}")


def get_level():
    while(True):
        try:
            level = int(input("Level: "))
            if level not in [1, 2, 3]:
                raise ValueError
        except (TypeError, ValueError):
            pass
        else:
            return level


def generate_integer(level):
    if level == 1:
        start = 0
    else:
        start = 10**(level-1)
    end = 10**level
    return random.randrange(start, end)


if __name__ == "__main__":
    main()