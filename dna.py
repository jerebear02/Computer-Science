import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # Read database
    database = []
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        strs = reader.fieldnames[1:]  # STR names (skip "name" column)
        for row in reader:
            database.append(row)

    # Read DNA sequence
    with open(sys.argv[2]) as f:
        sequence = f.read().strip()

    # Count longest runs of each STR in the sequence
    counts = {str_name: longest_run(sequence, str_name) for str_name in strs}

    # Match against database
    for person in database:
        if all(int(person[str_name]) == counts[str_name] for str_name in strs):
            print(person["name"])
            return

    print("No match")


def longest_run(sequence, str_name):
    longest = 0
    length = len(str_name)

    for i in range(len(sequence)):
        count = 0
        while sequence[i + count * length: i + (count + 1) * length] == str_name:
            count += 1
        longest = max(longest, count)

    return longest
