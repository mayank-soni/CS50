# Gets a fractional value between 0 and 1 from user representing the value of a fuel gauge.
# Prints out an equivalent integer percentage. Prints 'E' if <1% and 'F' if >99%

while (True):
    fraction = input("Fraction: ").strip().split("/")
    try:
        percentage = int(fraction[0])/int(fraction[1])
    except (ValueError, ZeroDivisionError, IndexError):
        pass
    else:
        if 0 <= percentage <= 1:
            break

if percentage < 0.01:
    print("E")
elif percentage > 0.99:
    print("F")
else:
    print(f"{round(100*percentage)}%")