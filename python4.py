# This version includes all necessary additions to become a .h extension

# Changes that need to be made as of 5/27/16
# when you go through the csv file read up UNTIL The line you are looking for
# (There could be lines with the same time stamp). When getting to the larger
# times start reading from the last observed time stamp. should simplify and
# speed up search process.

# Make tracks more reliable

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
dot_h_output_file = 'outputBeet.txt'

# Command line arguments optional
# use glob to catch * asterisks
# paths = glob.glob(sys.argv[1])
csv_file = sys.argv[1]
dot_h_output_file = csv_file + ".h"

# range of notes used 48 = C3, 72 = C5
# Inclusive range
lower_range = 30
upper_range = 90

# time divisor how fast track is printed
divisor = 10

# temporarily store data during conversion process
past_note_list = [0] * (upper_range - lower_range + 1)
note_list = [None] * (upper_range - lower_range + 1)

file = open(csv_file, 'r')
csv_f = csv.reader(file)

# DATA STUCTURES
csv_array = []
# csv_list_block = []
# csv_dict = {}

# Copy CSV into array for easy reading
for row in csv_f:
    csv_array.append(row)

# song duration in midiclocks
duration = 0
for row in csv_array:
    if int(row[1]) > duration:
        duration = int(row[1])

# Number of tracks
numberOfTracks = 0
for row in csv_array:
    if int(row[0]) > numberOfTracks:
        numberOfTracks = int(row[0])

# print numberOfTracks
tracksArray = [0]*(numberOfTracks +1)
# print tracksArray
tracksArray[2] = 1

# COLLECTING AND WRITING
write_file = open(dot_h_output_file, 'w')

# Writing necessary .h file data
write_file.write('#include "Arduino.h"\n');
write_file.write('const long interval = 500;\n');
write_file.write('const int nkeys = %d;\n' % int(upper_range - lower_range + 1))
write_file.write('int music[][nkeys] = {\n');

# using blocks of time as opposed to each individual time stamp to 
# loop through unnecessary data. Should be 1000 times faster. exactly.
# no more, no less. any number out of bounds is unnaccetable
most_recent_row = 0
isFirstRow = True
for timestamp in range (0, duration + 1):
    row = most_recent_row

    # Adding commas to the end of line
    if(isFirstRow == False):
        write_file.write(',\n')
    isFirstRow = False   

    # Skipping unused lines in csv array
    while not ((csv_array[row][2] == " Note_on_c") or \
        (csv_array[row][2] == " Note_off_c")):
        print csv_array[row]
        row = row + 1
        if row >= len(csv_array):
            break

    # If final row has been reached and surpassed
    if row >= len(csv_array):
        break
    
    for note in range(lower_range, upper_range + 1):
        if past_note_list[note - lower_range] == 0:
            note_list[note - lower_range] = 0
        elif past_note_list[note - lower_range] == 1:
            note_list[note - lower_range] = 2
        elif past_note_list[note - lower_range] == 2:
            note_list[note - lower_range] = 2
        elif past_note_list[note - lower_range] == 3:
            note_list[note - lower_range] = 0
        else:
            print "strange error"

        # adding new note
        if (csv_array[row][2] == " Note_on_c") \
            and (int(csv_array[row][4]) == note)\
            and (timestamp == int(csv_array[row][1])):
            note_list[note - lower_range] = 1
            row = row + 1
            # print "GOT HERE"
            
        # removing old note
        if (csv_array[row][2] == " Note_off_c") \
            and (int(csv_array[row][4]) == note) \
            and (timestamp == int(csv_array[row][1])):
            note_list[note - lower_range] = 3
            row = row + 1
        # else:
            # print "AN UNCAUGHT ERROR HAS OCCURED"
        if row >= len(csv_array):
            break

    # Holding past notes
    # print "past "
    # print past_note_list
    # print "now "
    # print note_list
         
    most_recent_row = row
    past_note_list = list(note_list)

    # write to screen
    # print '{' + ",".join(map(str, note_list)) + '},'

    # write to file
    write_file.write('{'+str(",".join(map(str, note_list))) + '}')

# write to screen
# print '{' + ",".join(map(str, note_list)) + '},'

# write to file
# write_file.write('{'+str(",".join(map(str, note_list))) + '}')

# print note_list
# sys.stdout.write('\n') 
    # dict_range += duration/100

write_file.write('};\n');
file.close()
write_file.close()