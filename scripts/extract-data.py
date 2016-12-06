# Produces two CSV files (one for unsorted input and one for sorted input).

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
            # The last token is 'ms', we must get the one before it.
            ms = int(line.split()[-2])
            expand(data, group, ms)
        elif 'Height' in line:
            expand(data, group, int(line.split()[-1]))
        elif 'Factor' in line:
            expand(data, group, int(line.split()[-1]))
        elif 'Comparisons' in line:
            expand(data, group, int(line.split()[-1]))


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
    header = ["Elements"]
    operations = ["Insertion", "Query", "Removal"]
    trees = ["BST", "AVL"]
    metrics = ["Duration", "Height", "Factor", "Comparisons"]
    for operation in operations:
        for tree in trees:
            for metric in metrics:
                header.append(tree + ' ' + operation + ' ' + metric)
    return header


def integer_from_key(key):
    x = 0
    for c in key:
        if c.isdigit():
            x *= 10
            x += int(c)
        else:
            break
    return x


with open(filename + '.csv', 'w') as f:
    writer = csv.writer(f, quotechar='"')
    rows = []
    for key in data:
        if 'sorted' not in key:
            rows.append([integer_from_key(key)] + data[key])
    writer.writerow(get_header())
    for row in sorted(rows):
        writer.writerow(row)

with open(filename + '.sorted' + '.csv', 'w') as f:
    writer = csv.writer(f, quotechar='"')
    rows = []
    for key in data:
        if 'sorted' in key:
            rows.append([integer_from_key(key)] + data[key])
    writer.writerow(get_header())
    for row in sorted(rows):
        writer.writerow(row)
