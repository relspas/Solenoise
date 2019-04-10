# Raphael Elspas
# Project Solenoise

#####################################################################
# This converts a csv file to a dot h file that an arduino can read #
#####################################################################

######################################################################
# To Use:                                                            #
# midiToH.py <csv_file> <tracks to convert (-1 converts all tracks)> #
#                                                                    #
# example:                                                           #
# midiToH.py furelise.txt 2 3 4                                      #
# example:                                                           #
# midiToH.py furelise.txt -1                                         #
######################################################################

############################################################################
# Updates: Instead of raising exception when more than 7 notes are played  #
# at once, now will reduce row by selectively removing enough notes from   #
# music row.                                                               #
# Changes Made 11/9/16                                                     #
############################################################################


import csv
import sys
import random

# count the number of 1 in the array argument
def countNotes( noteArray ):
    count = 0
    for note in noteArray:
        if note == 1:
            count = count + 1
    return count

def notePlacement(noteArray):
    arr = []
    for i in range(len(noteArray)):
        if noteArray[i] == 1:
            arr.append(i)
    return arr  

def removeRandom(noteArray, notePlace):
   noteArray[random.choice(notePlace)] = 0
   return noteArray

# Check if command line args are included
if len(sys.argv) < 3:
    print "Usage: midiToH.py <csv_file> <tracks to convert (-1 converts all tracks)>"
    sys.exit()

# Command line arguments optional
csv_file = sys.argv[1]
dot_h_output_file = csv_file[:-4] + ".h" #removes last 4 chars (.mid) and appends .h

# Reading in which tracks to compile
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
past_note_list = [0 for i in range (64)]
note_list = [0 for i in range (64)] #Change 0 is note list back to None for debugging

f = open(csv_file, 'r')
csv_f = csv.reader(f)

# DATA STUCTURES
csv_array = []

# Copy CSV into array because csv.reader only provides generator
for row in csv_f:
    csv_array.append(row)
    # print row

f.close()

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

# Tempo (microseconds per beat)
tempo = 500000 # Default tempo (120 bpm), if not labeled in song
for row in csv_array:
    if row[2] == ' Tempo':
        tempo = int(row[3])
        break

# Ticks per Beat (quarter note)
ticks_per_beat = int(csv_array[0][5])

# Sampling Rate (ticks per 32nd note)
sampling_rate = ticks_per_beat/8

# Music that will be written to the file
music_array_string = ""

# Number of lines in music_array_string
number_of_lines = 0

# Array to hold cursors that follow iteration through each track
cursors = [0]*numberOfTracks

isFirstRow = True
sampling_count = 0
for timestamp in range (0, duration/sampling_rate + 1):
    # print cursors

    # Adding commas to the end of line
    if(isFirstRow == False):
        # write_file.write(',\n')
        music_array_string += ',\n'
    isFirstRow = False   

    # print cursors
    for track in tracksArray:

        # Reseting cursor
        row = cursors[track]

        # Skip to track (only happens once per track)
        while (row < len(csv_array)) and \
            int(csv_array[row][0]) != track:
            print csv_array[row]
            row = row + 1

        # Skipping unused lines in csv array
        while (row < len(csv_array)) and \
            (int(csv_array[row][0]) == track) and \
            not ((csv_array[row][2] == " Note_on_c") or \
            (csv_array[row][2] == " Note_off_c")):
            # print str(track) + ":"
            # print csv_array[row]
            row = row + 1
        
        # Copying old printed notes only if first track
        if track == tracksArray[0]: 
            for note in range(lower_range, upper_range + 1):
                if past_note_list[note - lower_range] == 0:
                    # if note == 90:
                    #     print note_list
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
            
            #checking for boundary notes
            if len(csv_array[row]) > 4 and \
                ((int(csv_array[row][4]) - lower_range) >= 0) and \
                ((int(csv_array[row][4]) - lower_range) < 60):

                # adding new note
                if (csv_array[row][2] == " Note_on_c") \
                    and (csv_array[row][5] != " 0"):
                    # print "length: "+ str(len(note_list))
                    # print "element: " + str(int(csv_array[row][4]) - lower_range)
                    note_list[int(csv_array[row][4]) - lower_range] = 1
                    # print csv_array[row][4] + ": add"

                # removing old note
                elif (csv_array[row][2] == " Note_off_c" or 
                        ((csv_array[row][2] == " Note_on_c") \
                        and (csv_array[row][5] == " 0"))):
                    note_list[int(csv_array[row][4]) - lower_range] = 0
                    # print csv_array[row][4] + ": sub"
            elif len(csv_array[row]) > 4 and (int(csv_array[row][4]) - lower_range) < 0:
                pass
                # print "Note chopped off: too low"
            else:
                pass
                # print "Note chopped off: too high"
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

    # write to screen
    # print '{' + ",".join(map(str, note_list)) + '},'

    # check number of notes per line
    removedNotes = 0
    while countNotes(note_list[0:61]) > 7:
        # raise Exception("More than 7 notes played at once")
        # print notePlacement(note_list)
        removedNotes += 1
        note_list = removeRandom(note_list[0:61], notePlacement(note_list))

    # Terminal message of more than 7 notes at once
    if removedNotes > 0:
        print str(7+removedNotes)+" notes at once: " + str(removedNotes) + " removed"

    music_array_string += '{B' + ''.join(map(str, note_list[0:8]))   + ',B' \
                               + ''.join(map(str, note_list[8:16]))  + ',B' \
                               + ''.join(map(str, note_list[16:24])) + ',B' \
                               + ''.join(map(str, note_list[24:32])) + ',B' \
                               + ''.join(map(str, note_list[32:40])) + ',B' \
                               + ''.join(map(str, note_list[40:48])) + ',B' \
                               + ''.join(map(str, note_list[48:56])) + ',B' \
                               + ''.join(map(str, note_list[56:60])) + '0000}'
    number_of_lines = number_of_lines + 1

music_array_string += '};'
# write to screen
# print '{' + ",".join(map(str, note_list)) + '},'

# write to file
# write_file.write('{'+str(",".join(map(str, note_list))) + '}')



# WRITING
write_file = open(dot_h_output_file, 'w')

write_file.write('#include "Arduino.h"\n')
write_file.write('#include <avr/pgmspace.h>\n')
write_file.write('const long interval = %d;\n' % int(round(tempo/8000))) # Tempo is rounded to nearest int. Justin thinks it's beautiful
write_file.write('const int songlength = %d; //# of lines\n' % number_of_lines)
write_file.write('const PROGMEM byte musicarray[][8] = {\n')
write_file.write(music_array_string)

write_file.close()