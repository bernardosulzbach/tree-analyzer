# Produces two CSV files (one for unsorted input and one for sorted input).
# Each of which has lines with 7 ordered values:
# ID
# BST Insertion Duration
# BST Insertion Comparisons
# BST Query Duration
# BST Query Comparisons
# BST Removal Duration
# BST Removal Comparisons
# AVL Insertion Duration
# AVL Insertion Comparisons
# AVL Query Duration
# AVL Query Comparisons
# AVL Removal Duration
# AVL Removal Comparisons
# AVL Removal Comparisons

import csv
import sys

if len(sys.argv) != 2:
    print('Pass the dump filename to the script.')

filename = sys.argv[1]

data = {}

with open(filename, 'r') as f:
    def expand(data, key, value):
        values = data.get(key, [])
        values.append(value)
        data.update({key: values})


    def derive_group(line):
        name = line.split()[-1].replace('.txt', '')
        name = name[1:]  # Remove the 'n' from the start.
        return name


    lines = f.readlines()
    group = None
    for line in lines:
        if not line.startswith(' '):
            group = derive_group(line)
        elif 'Time' in line:
            ms = int(line.split()[-2])
            expand(data, group, ms)
        elif 'Comparisons' in line:
            comparisons = int(line.split()[-1])
            expand(data, group, comparisons)


def splitter(entries):
    key = entries[0]
    index_of_first_non_digit = 0
    for i, c in enumerate(key):
        if not c.isdigit():
            index_of_first_non_digit = i
            break
    number = key[:index_of_first_non_digit]
    letter = key[-1]
    print(key)
    return (int(number), letter)


def get_header():
    header = ["ID"]
    trees = ["BST", "AVL"]
    operations = ["Insertion", "Query", "Removal"]
    metrics = ["Duration", "Comparisons"]
    for tree in trees:
        for operation in operations:
            for metric in metrics:
                header.append(tree + ' ' + operation + ' ' + metric)
    return header


with open(filename + '.csv', 'w') as f:
    writer = csv.writer(f)
    rows = []
    for key in data:
        if 'sorted' not in key:
            rows.append([key] + data[key])
    writer.writerow(get_header())
    for row in sorted(rows):
        writer.writerow(row)

with open(filename + '.sorted' + '.csv', 'w') as f:
    writer = csv.writer(f)
    rows = []
    for key in data:
        if 'sorted' in key:
            rows.append([key] + data[key])
    writer.writerow(get_header())
    for row in sorted(rows):
        writer.writerow(row)
