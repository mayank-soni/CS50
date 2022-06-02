def main():
# Takes time input by user
# Prints out whether it is breakfast, lunch, or dinner time
    time = convert(input("What is the time? ").lower().strip())

    if 7 <= time <= 8:
        print("breakfast time")
    elif 12 <= time <= 13:
        print("lunch time")
    elif 18 <= time <= 19:
        print("dinner time")


def convert(time):
# Converts time provided as string in 12h or 24h format into float in 24h format
# Input format: "##:##" or "##:## a.m." or "##:## p.m."
    timelist = time.split(":")
    timelist12h = timelist[1].split()

    hours = int(timelist[0])
    minutes = float(timelist12h[0])/60

    # If time provided in 12h format, convert to 24h format
    if len(timelist12h) == 2:
        if timelist12h[1] == "p.m." and 1 <= hours < 12:
            hours += 12
        elif timelist12h[1] == "a.m." and hours == 12:
            hours -= 12

    return hours + minutes


if __name__ == "__main__":
    main()


