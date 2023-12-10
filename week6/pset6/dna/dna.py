import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1
    
    # TODO: Read database file into a variable
    people = []
    strTypes = []

    with open(sys.argv[1]) as file:
        file_reader = csv.DictReader(file)
        for human in file_reader:
            people.append(human)

    for human in people[0]:
        strTypes.append(human)

    # TODO: Read DNA sequence file into a variable
    sequence = ""
    with open(sys.argv[2]) as file:
        for line in file:
            sequence += line.strip()

    # TODO: Find longest match of each STR in DNA sequence
    longest_matches = {}
    for sec in strTypes[1:]:
        match = longest_match(sequence, sec)
        longest_matches[sec] = match

    # TODO: Check database for matching profiles
    for human in people:
        equalCount = 0
        for key in longest_matches:
            if int(human[key]) == longest_matches[key]:
                equalCount += 1
        
        if equalCount == len(longest_matches):
            print(human["name"])
            return 0

    print("No match")
    return 1


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
