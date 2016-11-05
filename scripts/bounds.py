# This is a Python 3 program to print height bounds of an AVL tree.
#
# Written by Bernardo Sulzbach in 2016-11-04, released under the ISC license.

import math


def main(n):
    log2 = math.log2
    ceil = math.ceil
    sqrt = math.sqrt
    phi = (1 + sqrt(5)) / 2
    c = 1 / log2(phi)
    b = c / 2 * log2(5) - 2
    minimum = log2(n + 1)
    maximum = c * log2(n + 2) + b
    print("Height limits: {} ≤ h < {}".format(ceil(minimum), ceil(maximum)))

if __name__ == '__main__':
    main(int(input("Node count: ").strip()))
