#Takes string as input, converts any emoji codes/aliases into the corresponding emoji, and prints the updated string out.
from emoji import emojize

print(f"Output: {emojize(input('Input: '), language='alias')}")