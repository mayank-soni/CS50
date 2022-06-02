# Takes in input in format "x operator y" where operator is one of '+', '-', '*', or '/'
# Prints the result of the operation as a float

equation = input("Expression: ").strip().split()
x = float(equation[0])
y = float(equation[2])
operator = equation[1]

if operator == "+":
    print (x + y)
elif operator == "-":
    print (x - y)
elif operator == "*":
    print (x * y)
elif operator == "/":
    print (x / y)