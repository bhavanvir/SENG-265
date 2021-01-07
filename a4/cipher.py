#!/usr/bin/env python3
"""
In this file, you need to add your FileDecoder class
See a4 PDF for details

WE WILL EVALUATE YOUR CLASS INDIVIDUAL, SO MAKE SURE YOU READ
THE SPECIFICATIONS CAREFULLY.
"""
class FileDecoder:
    def __init__(self, key, filename, alphabet):
        self.key = key
        self.filename = filename
        self.alphabet = alphabet
        self.row_list = self.decrypt()
        self.index = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.index >= len(self.row_list):
            raise StopIteration
        index = self.index
        self.index += 1
        return self.row_list[index]

    def __repr__(self):
        return "FileDecoder(key=\'{}\', file=\'{}\')".format(self.key, self.filename)

    def __len__(self):
        return len(self.row_list)

    def read_file(self):
        lines = []
        f = open(self.filename, "r")
        lines = f.read()

        f.close()
        return lines

    def decrypt(self):
        orig = ""
        count = 0
        lines = self.read_file()
        for ch in lines:
            k_idx = self.key[count % len(self.key)]
            shift = self.alphabet.index(ch) - self.alphabet.index(k_idx) % len(self.alphabet)
            orig += self.alphabet[shift]
            count += 1

        file_list = list(orig.splitlines())
        row_list = [lines.split(",") for lines in file_list]

        if row_list[0][0] != "departure_terminal":
            raise DecryptException

        return row_list

class DecryptException(Exception):
    """Incorrect key."""
    pass
