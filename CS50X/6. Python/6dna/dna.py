import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Error, incorrect usage. Correct usage: python dna.py database.csv sequence.txt")

    # Read a database from CSV file containing each person's DNA fingerprint.
    # Database structured as a list of dictionaries, each dictionary represent one person (one row in the CSV)
    # Dictionary keys are 'name' and the names of the STRs. Values for the number of repeats of each STR are cast to integers.
    DNAdatabase = []
    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            person = {}
            for header in reader.fieldnames:
                if header != "name":
                    person[header] = int(row[header])
                else:
                    person[header] = row[header]
            DNAdatabase.append(person)

    # Read a text file containing a DNA sequence and save it as a string
    sequence = ""
    with open(sys.argv[2], "r") as txtfile:
        DNAsequence = txtfile.read()

    # Use pre-defined function to find the longest number of repeats for each STR sequence
    # Save this to a dictionary with STR names as keys and number of repeats as values
    sequenceSTRs = {}
    for STR in DNAdatabase[0]:
        if STR != "name":  # excluding "name" as we don't want to search for it in the sequence
            sequenceSTRs[STR] = longest_match(DNAsequence, STR)

    # Check database for matching profiles
    # Do so by creating a copy of each person's dictionary in the database, but removing the name variable i.e. only leaving the STR counts
    # If this copied dictionary is equal to the sequenceSTRs dictionary, there is a match
    found=False
    for person in DNAdatabase:
        checker = person.copy()
        del checker["name"]
        if checker == sequenceSTRs:
            print(person["name"])
            found = True
            break
    if not found:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
