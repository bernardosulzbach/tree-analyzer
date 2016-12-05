# Run this on the directory with the input files to get a full script.
import os


def key_from_filename(filename):
    digits = ''.join([c for c in filename if c.isdigit()])
    if 'sorted' in filename:
        return 'sorted' + digits
    else:
        return digits


def main():
    files = [f for f in os.listdir('.') if os.path.isfile(f)]
    files = sorted(files, key=key_from_filename)
    for filename in files:
        print('I {0}\nE\nC {0}\nE\nR {0}\nE'.format(filename))


if __name__ == '__main__':
    main()
