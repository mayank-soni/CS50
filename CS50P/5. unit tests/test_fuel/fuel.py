# Gets a fractional value between 0 and 1 from user representing the value of a fuel gauge.
# Prints out an equivalent integer percentage. Prints 'E' if <=1% and 'F' if >=99%

def main():
    try:
        print(gauge(convert(input("Fraction: ").strip())))
    except (ValueError, ZeroDivisionError):
        pass


def convert(fraction):
    while True:
        try:
            numerator, denominator = fraction.split("/") #typeerror
            percentage = round(int(numerator)/int(denominator)*100) #valueerror, zerodivision error
        except TypeError:
            pass
        except (ValueError, ZeroDivisionError) as error:
            raise error
        else:
            if 0 <= percentage <= 100:
                return percentage
            else:
                raise ValueError

def gauge(percentage):
    if percentage <= 1:
        return "E"
    elif percentage >= 99:
        return "F"
    else:
        return f"{percentage}%"


if __name__ == "__main__":
    main()