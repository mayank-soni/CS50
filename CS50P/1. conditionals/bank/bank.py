# Prints the amount to pay out ($0, $20, $100) depending on the greeting input by user, a la Seinfeld S07E24

greeting = input("Greeting: ").lower().strip()

if greeting[0:5] == "hello":
    print ("$0")
elif greeting[0] == "h":
    print ("$20")
else:
    print ("$100")