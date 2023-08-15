import csv
import sys
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    file1 = open(argv[1], "r")
    keylist = file1.readline()
    keylist = list(keylist[:len(keylist) - 1].split(","))
    peopleBuffer = csv.DictReader(file1, keylist)

    # TODO: Read DNA sequence file into a variable
    file2 = open(argv[2], "r")
    sequenceBuffer = file2.read()

    # TODO: Find longest match of each STR in DNA sequence
    STRs = {}
    for key in keylist:
        if key == "name":
            continue
        STRs.update({key : longest_match(sequenceBuffer, key)})
    # for key in STRs:
    #     print(STRs[key])

    # TODO: Check database for matching profiles
    earlyBreak = 0
    for row in peopleBuffer:
        # print("row", row)
        if compare_dna(row, STRs):
            print(row["name"])
            return
    print("No match")
    return

def compare_dna(row, STRs):
    for STR in STRs:
        # print("STRs", STRs)
        # print(row[STR], STRs[STR])
        if int(row[STR]) != int(STRs[STR]):
            return False
    return True


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
