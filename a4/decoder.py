#!/usr/bin/env python3
"""
Provided for you is the encryption alphabet used to encrypt the provided files.
This inclues: a-z, A-Z, 0-9, punctuation like .(); (not the same as in a1-a3), space and newline
"""
import string
import re
from cipher import FileDecoder, DecryptException

def calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, index):
    month_count[index] += 1
    delay_count[index] += (int(decoded_csv_row[11]) - int(decoded_csv_row[6])) * 60 + (int(decoded_csv_row[12]) - int(decoded_csv_row[7]))
    avg_delay[index] = delay_count[index] / month_count[index]

def print_info(avg_delay, months, file_decoder):
    print()
    print("RESULTS")
    print("FileDecoder: ", end = "")
    print(file_decoder)
    print("Entries: {}".format(len(file_decoder)))
    for delay in avg_delay:
        for month in months:
            if delay != 0 and avg_delay.index(delay) == months.index(month):
                print("    ", end = "")
                print("Average delay for {}: {avg:.2f}".format(month, avg = delay))
    print("END")

def main():
    alphabet = string.ascii_lowercase + string.ascii_uppercase + string.digits + string.punctuation + " \n"
    filename = ""
    key = ""
    while True:
        try:
            filename = input("Enter name of file: ")
            if filename == "q":
                exit(0)

            f = open(filename)
            f.close()
        except FileNotFoundError:
            print("File not found: enter a valid file or press 'q' to quit")
            continue
        else:
            break

    while True:
        try:
            key = input("Enter password: ")
            match = re.findall(r"^(?=.*[A-Z])(?=(.*\d){2})(?=.*[!@#\$&\*\-_\.]){2}.{6,8}$", key)
            if not match:
                if key == "q":
                    exit(0)
                else:
                    print("Invalid password: enter a valid password or press 'q' to quit")
                    continue
            elif match:
                file_decoder = FileDecoder(key, filename, alphabet)
                file_decoder.decrypt()
        except DecryptException:
            print("Decryption failed: enter the correct password or press 'q' to quit")
            continue
        else:
            break

    month_count = [0] * 12
    delay_count = [0.0] * 12
    avg_delay = [0.0] * 12
    months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
    for decoded_csv_row in file_decoder:
        if decoded_csv_row[4] == "01" or decoded_csv_row[4] == "1":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 0)
        if decoded_csv_row[4] == "02" or decoded_csv_row[4] == "2":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 1)
        if decoded_csv_row[4] == "03" or decoded_csv_row[4] == "3":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 2)
        if decoded_csv_row[4] == "04" or decoded_csv_row[4] == "4":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 3)
        if decoded_csv_row[4] == "05" or decoded_csv_row[4] == "5":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 4)
        if decoded_csv_row[4] == "06" or decoded_csv_row[4] == "6":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 5)
        if decoded_csv_row[4] == "07" or decoded_csv_row[4] == "7":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 6)
        if decoded_csv_row[4] == "08" or decoded_csv_row[4] == "8":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 7)
        if decoded_csv_row[4] == "09" or decoded_csv_row[4] == "9":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 8)
        if decoded_csv_row[4] == "10":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 9)
        if decoded_csv_row[4] == "11":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 10)
        if decoded_csv_row[4] == "12":
            calc_delay(avg_delay, delay_count, month_count, decoded_csv_row, 11)
    print_info(avg_delay, months, file_decoder)

if __name__ == "__main__":
    main()
