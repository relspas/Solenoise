# Additions that need to be made: 
# 1) choose track to convert to binary. e.g. only piano, no drums
# 2) Correct the length of each note.
# 3) add in effects besides note on and note off
# 4) catch if conversion is out of bounds

import csv
import sys
import glob

# CSV file to read from
csv_file = 'morse.txt'

# File to write binary to
binary_output_file = 'outputBeet.txt'

# command line arguments optional: 
# [prog name][readfile.txt(CSV)]
if len(sys.argv) > 1:
    # use glob to catch * asterisks
    # paths = glob.glob(sys.argv[1])
    csv_file = sys.argv[1]
    binary_output_file = csv_file + "bin"

# range of notes used 48 = C3, 72 = C5
# Inclusive range
lower_range = 30
upper_range = 90

# time divisor how fast track is printed
divisor = 10


past_note_list = [0] * (upper_range - lower_range + 1)
note_list = [None] * (upper_range - lower_range + 1)

file = open(csv_file, 'r')
csv_f = csv.reader(file)

# DATA STUCTURES
csv_array = []
csv_list_block = []
csv_dict = {}

# SETUP DATA STRUCTURES
for row in csv_f:
    csv_array.append(row)

# song duration in midiclocks
duration = 0
for row in csv_array:
    if int(row[1]) > duration:
        duration = int(row[1])

lower_dict_range = 0
upper_dict_range = duration/100
# raw_input("pausing. press enter to continue")

j = 0
while upper_dict_range <= duration:
    # print "started while"
    i = 0
    csv_list_block = []
    for row in csv_array:
        # print "started for"
        if (int(row[1]) >= lower_dict_range) and (int(row[1]) < upper_dict_range):
            csv_list_block.append(row)
            # print row
        i += 1
        # print i
    lower_dict_range = upper_dict_range
    upper_dict_range += duration/100
    csv_dict[j] = csv_list_block
    j += 1

# COLLECTING AND WRITING
write_file = open(binary_output_file, 'w')

# using blocks of time as opposed to each individual time stamp to 
# loop through unnecessary data. Should be 1000 times faster. exactly.
# no more, no less. any number out of bounds is unnaccetable

timestamp = 0 # keeps track of printed file number
dict_range = duration/100
for data_block_num in range(0, j):
    data_block = csv_dict[data_block_num]
    while timestamp < dict_range:
        for note in range(lower_range, upper_range + 1): 

            for row in data_block:

                # writing new notes
                if (row[2] == " Note_on_c") \
                    and (int(row[1])/divisor == int(timestamp)) \
                    and (int(row[4]) == note):
                    note_list[note - lower_range] = 1
                    break
                # removing old note
                elif (row[2] == " Note_off_c") \
                    and (int(row[1])/divisor == int(timestamp)) \
                    and (int(row[4]) == note):
                    note_list[note - lower_range] = 0
                    break
                # Holding past notes
                elif past_note_list[note - lower_range] == 0:
                    note_list[note - lower_range] = 0
                elif past_note_list[note - lower_range] == 1:
                    note_list[note - lower_range] = 1
                else:
                    print "strange error"


        timestamp += 1
        # raw_input("Press Enter to exit")
        past_note_list = list(note_list)
        # write to screen
        print "".join(map(str, note_list))
        
        # write to file
        # write_file.write(str("".join(map(str, note_list))) + '\n')
        
        # print note_list
        # sys.stdout.write('\n') 
    dict_range += duration/100
file.close()
write_file.close()