# This removes vowels from a string and prints the new string.

def main():
    tweet = input("Input: ")
    print("Output:" + shorten(tweet))

def shorten(input):
    return(f"{input.translate(input.maketrans('','','aeiouAEIOU'))}")

if __name__ == "__main__":
    main()