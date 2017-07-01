# Raphael Elspas
# Project Solenoise

# This converts a csv file to a dot h file that an arduino can read

# To Use: 
# python7.py [csv file] [tracks to convert (-1 converts all tracks)]

# example:
# python7.py furelise.txt 2 3 4
# example:
# python7.py furelise.txt -1


# Additions that need to be made: 
# 1) catch if conversion is out of bounds

# Keep an eye on rounding in line 86 and whether this will propogate an error 
# in timing


import csv
import sys

# CSV file to read from
csv_file = 'morse.txt'

# File to write binary to
dot_h_output_file = 'outputBeet.txt'

# Command line arguments optional
csv_file = sys.argv[1]
dot_h_output_file = csv_file[:-4] + ".h" #removes last 4 chars and appends .h

# Reading which tracks to compile
tracksArray = []
for trackSwitch in range (2, len(sys.argv)):
    tracksArray.append(int(sys.argv[trackSwitch]))
    
# Range of notes used ex: 48 = C3, 72 = C5
# Inclusive range
lower_range = 30
upper_range = 90

# time divisor how fast track is printed
divisor = 10

# temporarily store data during conversion process
past_note_list = [0] * (64)#upper_range - lower_range + 1)
note_list = [0] * (64)#upper_range - lower_range + 1) Change 0 is note list back to None for debugging

file = open(csv_file, 'r')
csv_f = csv.reader(file)

# DATA STUCTURES
csv_array = []

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

# -1 as command line argument
if tracksArray[0] == -1:
    tracksArray = []
    for track_num in range(0, numberOfTracks):
        tracksArray.append(track_num)

# Tempo
tempo = 500000 # Default tempo, if not labeled in song
for row in csv_array:
    if row[2] == ' Tempo':
        tempo = int(row[3])
        break

# Ticks per Beat
ticks_per_beat = int(csv_array[0][5])

# Sampling Rate
sampling_rate = ticks_per_beat/8

# COLLECTING AND WRITING
write_file = open(dot_h_output_file, 'w')

# Writing necessary .h file data
write_file.write('#include "Arduino.h"\n');
write_file.write('const long interval = %d;\n' % int(round(tempo/8000))); # Tempo is rounded to nearest int. Justin thinks it's beautiful
write_file.write('const int nkeys = %d;\n' % 60)# % int(upper_range - lower_range + 1))
write_file.write('byte music[][8] = {\n');

# using blocks of time as opposed to each individual time stamp to 
# loop through unnecessary data. Should be 1000 times faster. exactly.
# no more, no less. any number out of bounds is unnaccetable
cursors = [0]*numberOfTracks
isFirstRow = True
sampling_count = 0
for timestamp in range (0, duration/sampling_rate + 1):
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
        
        # Copying old notes
        for note in range(lower_range, upper_range + 1):
            if past_note_list[note - lower_range] == 0:
                note_list[note - lower_range] = 0
            elif past_note_list[note - lower_range] == 1:
                note_list[note - lower_range] = 1
            else:
                print "strange error"
        
        # Reading array
        while (row < len(csv_array)) \
            and (int(csv_array[row][0]) == track) \
            and (timestamp*sampling_rate <= int(csv_array[row][1])) \
            and (timestamp*sampling_rate + sampling_rate > int(csv_array[row][1])):
            
            # adding new note
            if (csv_array[row][2] == " Note_on_c") \
                and (csv_array[row][5] != " 0"):
                note_list[int(csv_array[row][4]) - lower_range] = 1
                # print csv_array[row][4] + ": add"

            # removing old note
            elif (csv_array[row][2] == " Note_off_c" or 
                    ((csv_array[row][2] == " Note_on_c") \
                    and (csv_array[row][5] == " 0"))):
                note_list[int(csv_array[row][4]) - lower_range] = 0
                # print csv_array[row][4] + ": sub"
            
            row = row + 1
            # else:
                # print "AN UNCAUGHT ERROR HAS OCCURED"

        cursors[track] = row

    # Holding past notes
    # print "past "
    # print past_note_list
    # print "now "
    # print note_list

    past_note_list = list(note_list)

    # Convert to two longs 

    # write to screen
    # print '{' + ",".join(map(str, note_list)) + '},'

    # write to file
    # NEEDS TO BE CHANGED TO 8 bytes
    write_file.write('{B' + ''.join(map(str, note_list[0:8])) + ',B' \
                       + ''.join(map(str, note_list[8:16])) + ',B' \
                       + ''.join(map(str, note_list[16:24])) + ',B' \
                       + ''.join(map(str, note_list[24:32])) + ',B' \
                       + ''.join(map(str, note_list[32:40])) + ',B' \
                       + ''.join(map(str, note_list[40:48])) + ',B' \
                       + ''.join(map(str, note_list[48:56])) + ',B' \
                       + ''.join(map(str, note_list[56:64])) + '}' \
                    )


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