from cs50 import get_string

text = get_string ("Text: ")

letters = 0

#Initialise words to 1 to include the last word in the text which doesn't have any spaces after it and so wouldn't be counted otherwise
words = 1
sentences = 0

length = len(text)

# List of ASCII characters
characters = range (33,127)

# ASCII characters for ".", "!", and "?"
punctuation = [33, 46, 63]

#Count number of letters, words, and sentences in text
for i in range(length):
    if text[i].isalpha():
        letters += 1
    elif text[i].isspace() and ord(text[i-1]) in characters and ord(text[i+1]) in characters:
        words += 1
    elif ord(text[i]) in punctuation:
        sentences +=1

#Calculate CL index
index = round(0.0588 * 100 * letters/words - 0.296 * 100 * sentences/words - 15.8)

#Handle output
if index >= 16:
    print ("Grade 16+")
elif index < 1:
    print ("Before Grade 1")
else:
    print (f"Grade {index}")