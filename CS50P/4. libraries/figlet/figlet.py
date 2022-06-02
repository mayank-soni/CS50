#Prints text in a figlet font
#If no command line arguments provided, uses random font.
#Provide specific font using -f or --font command line argument

from pyfiglet import Figlet, FigletFont
from sys import argv, exit
from random import choice

if len(argv) == 1: # If no command-line arguments entered
    f=Figlet(font=choice(FigletFont.getFonts())) # Set up Figlet with random font
    print(f.renderText(input("Input: ")))
elif len(argv)==3 and (argv[1]=="-f" or argv[1]=="--font"): # If a specific font is chosen
    try:
        f=Figlet(font=argv[2]) # Use the entered font
    except:
        exit("Font not found")
    print(f.renderText(input("Input: ")))
else:
    exit("Invalid usage. Should be: python figlet.py -f fontname")