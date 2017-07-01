# This version includes all necessary additions to become a .h extension

# To Use: 
# python5.py [csv file] [tracks to convert]
# example:
# python5.py furelise.txt 2 3 4

# Additions that need to be made: 
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

# Reading which tracks to compile
tracksArray = []
for trackSwitch in range (2, len(sys.argv)):
    tracksArray.append(int(sys.argv[trackSwitch]))
    
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
numberOfTracks += 1

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
cursors = [0]*numberOfTracks
isFirstRow = True
for timestamp in range (0, duration + 1):
    # print cursors
    # Adding commas to the end of line
    if(isFirstRow == False):
        write_file.write(',\n')
    isFirstRow = False   
    # print cursors
    for track in tracksArray:

        # Reseting cursor
        row = cursors[track]

        # Skip to track
        while (row < len(csv_array)) and \
            int(csv_array[row][0]) != track:
            # print csv_array[row]
            row = row + 1
            if row >= len(csv_array):
                break

        # Skipping unused lines in csv array
        while (row < len(csv_array)) and \
            (int(csv_array[row][0]) == track) and \
            not ((csv_array[row][2] == " Note_on_c") or \
            (csv_array[row][2] == " Note_off_c")):
            # print str(track) + ":"
            # print csv_array[row]
            row = row + 1
        
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
            if (row < len(csv_array)) \
                and (int(csv_array[row][0]) == track) \
                and (csv_array[row][2] == " Note_on_c") \
                and (csv_array[row][5] != " 0") \
                and (int(csv_array[row][4]) == note)\
                and (timestamp == int(csv_array[row][1])):
                note_list[note - lower_range] = 1
                row = row + 1
                print str(note) + ": add"
                # print "GOT HERE"

            # removing old note
            elif (row < len(csv_array)) \
                and (int(csv_array[row][0]) == track) \
                and (csv_array[row][2] == " Note_off_c" or 
                    ((csv_array[row][2] == " Note_on_c") \
                    and (csv_array[row][5] == " 0"))) \
                and (int(csv_array[row][4]) == note) \
                and (timestamp == int(csv_array[row][1])):
                note_list[note - lower_range] = 3
                row = row + 1
                print str(note) + ": sub"
            # else:
                # print "AN UNCAUGHT ERROR HAS OCCURED"

        cursors[track] = row

    # Holding past notes
    # print "past "
    # print past_note_list
    # print "now "
    # print note_list

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