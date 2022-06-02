# Prints out "Adieu, Adieu, to ...", where ... is an input list of names. 
# Does this grammatically.

import inflect

p = inflect.engine()
list_of_names = []
while(True): #Keep adding to list of names until Ctrl-D (EOFError) pressed, at which point print out the list
    try:
        list_of_names.append(input("Name: "))
    except EOFError:
        print("Adieu, adieu, to", p.join(list_of_names))
        break
