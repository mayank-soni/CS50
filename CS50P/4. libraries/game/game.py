from random import choice
from sys import exit

def main():
    random_number = choice(range(1, get_positive_integer("Level: ")+1)) #Generate random integer between 1 and the number input by user
    while(True):
        guess = get_positive_integer("Guess: ")
        if guess == random_number:
            exit("Just right!")
        elif guess < random_number:
            print("Too small!")
        else:
            print("Too large!")

def get_positive_integer(prompt): #Gets a positive integer
    while(True):
        try:
            number = int(input(prompt))
            if number <= 0:
                raise ValueError
            break
        except (TypeError, ValueError):
            pass
    return number

main()



