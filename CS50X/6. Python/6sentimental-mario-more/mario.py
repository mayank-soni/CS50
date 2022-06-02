from cs50 import get_int

#keep prompting for height until an integer between 1 to 8 provided.
while True:
    height = get_int ("Height: ")
    if height>=1 and height <=8:
        break

# prints each required line with enough spaces at start to get bottom left of pyramid to align with bottom left of window

for i in range (height):
    print (" " * (height-1-i) + "#"*(i+1) + "  " + "#" * (i+1))
