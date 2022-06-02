#Converts a name in camelCase into snake_case. Prints out the new name.

name = input("camelCase: ").strip()
for i in range(len(name)):
    if name[i].isupper():
        name = name[:i] + "_" + name[i].lower() + name[i+1:]
        i += 1  # Since a character ("_") has been added to name, the next run through the loop will check the same character again.
                # Prevent this by adding 1.
print (f"snake_case: {name}")