# Takes in items (e.g. for a grocery list) as input (separated by Enter).
# Once Ctrl-D is pressed, prints out the items as an alphabetical list together with the number of times each was input

grocery_list = {}

while (True):
    try:
        item = input().strip().upper()
    except EOFError: # Stops if user enters Ctrl-D. Goes to next line before exiting
        for item in sorted(grocery_list): # Alphabetical sorting
            print(f"{grocery_list[item]} {item}") # Printing out together with counts
        break
    else: #Counting number of times each item is input
        if item in grocery_list:
            grocery_list[item] += 1
        else:
            grocery_list[item] = 1