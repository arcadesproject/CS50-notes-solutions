import csv
import sys

"""
program that will take a sequence of DNA and a CSV file
containing STR counts for a list of individuals
then output to whom the DNA (most likely) belongs.
"""


def main():

    # Check for command-line usage
    # arg 0 csv, arg 1 txt
    if (len(sys.argv) != 3):
        print("PLease provide one csv file and one txt file in cli arguments")
        sys.exit(1)

    # Read database file into a variable
    db_content = None
    with open(sys.argv[1]) as db_file:
        db_content = list(csv.DictReader(db_file))

    # Read DNA sequence file into a variable
    dna_content = None
    with open(sys.argv[2]) as dna_file:
        dna_content = dna_file.read().strip()

    # Find longest match of each STR in DNA sequence
    matches = {}
    for key in db_content[0]:
        if (key != 'name'):
            matches[key] = longest_match(dna_content, key)

    # Check database for matching profiles
    for person in db_content:
        if all(matches[key] == int(person[key]) for key in person if key != 'name'):
            print(person['name'])
            return

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
