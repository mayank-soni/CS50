#Takes dates input in month-day-year format and returns it as year-month-day format (ISO-8601)
#Possible input: Type 1: MM/DD/YYYY. Type 2: Month can be spelled out, in which case it should be formatted: Month DD, YYYY
#Output: YYYY-MM-DD

months = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
]

while(True):
    try:
        input_date = input("Date: ").strip()
        if input_date[0].isalpha(): # If the format has the month spelt out (type 2)
            temp = input_date.split(" ")
            month, year = temp[0], temp[2]
            day = temp[1].removesuffix(",")
            for i in range(12): # Convert spelt out month name into a number
                if month == months[i]:
                    month = str(i+1)
                    break
                elif i == 11: # If all the months have been checked and no match found so far
                    raise ValueError
            if int(day)>31 or int(day)<1 or int(year)<0:
                raise ValueError
        else:
            month, day, year = input_date.split("/")
            if int(day)>31 or int(day)<1 or int(year)<0 or int(month)>12 or int(month)<1:
                raise ValueError
    except EOFError: #Exit program on Ctrl-D being pressed
        print()
        break
    except (IndexError, ValueError, TypeError) as error: #Re-prompt for input in case these errors raised
        pass
    else:
        print(f"{year.zfill(4)}-{month.zfill(2)}-{day.zfill(2)}")
        break