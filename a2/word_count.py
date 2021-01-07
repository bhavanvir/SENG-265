#!/bin/env python3
import sys
import re
import os.path
import statistics

def remove_repetition(i):
    return list(dict.fromkeys(i))

def read_file(filepath, buffer_input):
    buffer_input = []
    with open(filepath, "r") as f:
        buffer_input = f.read()
    buffer_input = re.split('[. |, | |; |( |) |\n|\t]', buffer_input)
    
    f.close()
    return buffer_input

def sift_input(buffer_input):
    sift_buffer = []
    for i in buffer_input:
        if i not in (''):
            sift_buffer.append(i)
    buffer_input = sift_buffer
    
    return buffer_input

def calculate_frequency(enumerate_lines):
    frequency = []
    frequency = [0]*max(enumerate_lines)
    for i in range(len(enumerate_lines)):
        frequency[enumerate_lines[i] - 1] += 1
    frequency = [i for i in frequency if i != 0] 

    return frequency

def print_histogram(sift_enumerate, frequency):
    i = 0
    while i < len(frequency):
        print("Count[%.2d]=%.2d;" % (sift_enumerate[i], frequency[i]))
        i += 1

def index_frequency(lines):
    length = [len(i) for i in lines]
    frequency = [0]*max(length)
    for i in range(len(length)):
        frequency[length[i] - 1] += 1
    return frequency

def print_unique_words(duplicate, length_frequency, duplicate_frequency):
    count = 0
    for i in range(len(duplicate)):
        if len(duplicate[i]) == length_frequency:
            if duplicate_frequency == 1:
                print(" (words: \"" + duplicate[i] + "\")")
            else:
                if duplicate_frequency - count == duplicate_frequency:
                    print(" (words: \"" + duplicate[i] + "\"", end = '')
                    count += 1
                elif duplicate_frequency - count == 1:
                    print(" and \"" + duplicate[i] + "\")")
                    count += 1
                else:
                    print(", \"" + duplicate[i] + "\"", end = '')
                    count += 1
        if count == duplicate_frequency:
            return

def main(): 
    #TODO
    if(len(sys.argv) < 3):
        print("program: missing '--infile <filename> [--sort] [--print-words]'\n")
        return
    i = 0
    filepath = ""  
    for i in range(len(sys.argv)):
        if sys.argv[i] == "--infile":
            filepath = sys.argv[i + 1]
        elif sys.argv[i] == "--sort":
            sort_flag = 1
        elif sys.argv[i] == "--print-words":
            print_words_flag = 1

    if os.path.isfile(filepath) == False:
        print("unable to open '%s' for reading\n" % filepath)
        return
    elif os.path.getsize(filepath) == 0:
        return

    if len(sys.argv) == 3:
        lines = []
        lines = read_file(filepath, lines)
        lines = sift_input(lines)

        if(len(lines) == 0):
            return
    
        enumerate_lines = [len(i) for i in lines]
        sift_enumerate = sorted(remove_repetition(enumerate_lines))

        frequency = []
        frequency = calculate_frequency(enumerate_lines)

        print_histogram(sift_enumerate, frequency)
    elif len(sys.argv) == 4 and sort_flag == 1:
        lines = []
        lines = read_file(filepath, lines)
        lines = sift_input(lines)
        
        if(len(lines) == 0):
            print("Median word length: 0.0")
            return
        
        enumerate_lines = [len(i) for i in lines]
        sift_enumerate = sorted(remove_repetition(enumerate_lines))

        median_length = statistics.median(sift_enumerate)
        
        length_frequency = index_frequency(lines) 
        length_frequency.insert(0,0)

        largest = 0
        for i in range(len(length_frequency)):
            largest = max(length_frequency)
            if largest != 0:
                print("Count[" + str(length_frequency.index(largest)).zfill(2) + "]=" + str(largest).zfill(2) + ";")
            length_frequency.insert(length_frequency.index(largest), 0)
            length_frequency.remove(largest)
        print("Median word length: %.1f" % median_length)
    elif len(sys.argv) == 5 and print_words_flag == 1 and sort_flag == 1:
        lines = [] 
        lines = read_file(filepath, lines)
        lines = sift_input(lines)

        if(len(lines) == 0):
            return

        duplicate = list(set(lines)) 
        duplicate_frequency = index_frequency(duplicate)
        duplicate_frequency.insert(0,0)
        duplicate.sort()

        length_frequency = index_frequency(lines)
        length_frequency.insert(0,0)

        largest = 0
        for i in range(len(length_frequency)):
            largest = max(length_frequency)
            if largest != 0:
                print("Count[" + str(length_frequency.index(largest)).zfill(2) + "]=" + str(largest).zfill(2) + ";", end = '')
            print_unique_words(duplicate, length_frequency.index(largest), duplicate_frequency[length_frequency.index(largest)])
            length_frequency.insert(length_frequency.index(largest), 0)
            length_frequency.remove(largest)   
    elif len(sys.argv) > 5:
        print("program: missing '--infile <filename> [--sort] [--print-words]'\n")    
    
    return     

#Do not change this
if __name__ == "__main__":
    main()
