# This removes vowels from a string and prints the new string.

tweet = input("Input: ")
print(f"Output: {tweet.translate(tweet.maketrans('','','aeiouAEIOU'))}")