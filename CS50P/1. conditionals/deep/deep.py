# Asks user for answer to life, the universe, and everything a la Douglas Adams and checks if the provided answer is 42.
# Does so insensitively to spelling it out, leading/trailing spaces, and case.
# If so, prints "Yes", otherwise prints "No".

answer = input("What is the Answer to the Great Question of Life, the Universe, and Everything?\n")

if answer.strip().lower() in ["42", "forty-two", "forty two"]:
    print ("Yes")
else:
    print ("No")